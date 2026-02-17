#include "ast.h"

namespace ntt {

using ParseFunc = std::function<bool(Ref<ParseNode> pNode)>;

#define AST_BINDING(func) [&](Ref<ParseNode> pNode) { return this->func(pNode); }

#define PARSE_NODE_AND(parentNode, handlerPtr, ...)                                                                    \
	do                                                                                                                 \
	{                                                                                                                  \
		i32		  pivot			= m_tokenCursor;                                                                       \
		ParseFunc handleFuncs[] = {__VA_ARGS__};                                                                       \
		i32		  funcCount		= sizeof(handleFuncs) / sizeof(ParseFunc);                                             \
		for (i32 i = 0; i < funcCount; i++)                                                                            \
		{                                                                                                              \
			Ref<ParseNode> _pTempNode = CreateRef<ParseNode>();                                                        \
			parentNode->pParseNodes.push_back(_pTempNode);                                                             \
                                                                                                                       \
			if (!handleFuncs[i](_pTempNode))                                                                           \
			{                                                                                                          \
				m_tokenCursor = pivot;                                                                                 \
				return false;                                                                                          \
			}                                                                                                          \
			_pTempNode->pParentNode = parentNode;                                                                      \
		}                                                                                                              \
		parentNode->handler = handlerPtr;                                                                              \
		return true;                                                                                                   \
	} while (0)

#define PARSE_NODE_OR(parentNode, ...)                                                                                 \
	do                                                                                                                 \
	{                                                                                                                  \
		i32		  pivot			= m_tokenCursor;                                                                       \
		ParseFunc handleFuncs[] = {__VA_ARGS__};                                                                       \
		i32		  funcCount		= sizeof(handleFuncs) / sizeof(ParseFunc);                                             \
		for (i32 i = 0; i < funcCount; i++)                                                                            \
		{                                                                                                              \
			parentNode->pParseNodes.clear();                                                                           \
			parentNode->handler = nullptr;                                                                             \
			parentNode->pToken	= nullptr;                                                                             \
                                                                                                                       \
			if (handleFuncs[i](parentNode))                                                                            \
			{                                                                                                          \
				return true;                                                                                           \
			}                                                                                                          \
			else                                                                                                       \
			{                                                                                                          \
				m_tokenCursor = pivot;                                                                                 \
			}                                                                                                          \
		}                                                                                                              \
		return false;                                                                                                  \
	} while (0)

#define GET_EXP(node, index) ((Expression*)(node->pParseNodes[index]->handler(node->pParseNodes[index])))

#define IS_ESP_NODE(node) (node->pToken == nullptr && node->pParseNodes.empty())

#define VERIFY_EXP(...)                                                                                                \
	do                                                                                                                 \
	{                                                                                                                  \
		Expression* exps[]	 = {__VA_ARGS__};                                                                          \
		i32			expCount = sizeof(exps) / sizeof(Expression*);                                                     \
		for (i32 i = 0; i < expCount; i++)                                                                             \
		{                                                                                                              \
			if (exps[i] == nullptr)                                                                                    \
			{                                                                                                          \
				return nullptr;                                                                                        \
			}                                                                                                          \
		}                                                                                                              \
	} while (0)

#define PARSE_TOKEN(expectedType) [&](Ref<ParseNode> pNode) { return parseToken(pNode, expectedType); }

static Expression* handleLiteralNode(Ref<ParseNode> pNode)
{
	return new LiteralExpression(*pNode->pToken);
}

static Expression* handleEpsilonNode(Ref<ParseNode> pNode)
{
	return new EpsilonExpression();
}

static Expression* handleOrNode(Ref<ParseNode> pNode)
{
	return pNode->pParseNodes[0]->handler(pNode->pParseNodes[0]);
}

AST::AST(const std::string& sourceCode, TokenParser tokenParser)
{
	if (tokenParser == nullptr)
	{
		tokenParser = parseTokens;
	}

	if (!tokenParser(sourceCode, m_tokens))
	{
		m_pRootExpression = nullptr;
		return;
	}

	m_tokenCursor  = 0;
	i32 nodeIndex  = 0;
	m_pRootExpNode = CreateRef<ParseNode>();
	m_isValid	   = parseExp(m_pRootExpNode);

	if (m_isValid)
	{
		if (m_pRootExpNode->handler == nullptr)
		{
			m_pRootExpression = nullptr;
			return;
		}
		else
		{
			m_pRootExpression = m_pRootExpNode->handler(m_pRootExpNode);
		}
	}
	else
	{
		m_pRootExpression = nullptr;
	}
}

AST::~AST()
{
	if (m_pRootExpression != nullptr)
	{
		delete m_pRootExpression;
		m_pRootExpression = nullptr;
	}
}

bool AST::parseExp(Ref<ParseNode> pNode)
{
	return parseAddExp(pNode);
}

static Expression* handleAddExpNode(Ref<ParseNode> pNode);
static Expression* handleRightAddExp_1(Expression* left, Ref<ParseNode> pNode);

bool AST::parseAddExp(Ref<ParseNode> pNode)
{
	PARSE_NODE_AND(pNode, handleAddExpNode, AST_BINDING(parseLeftAddExp), AST_BINDING(parseRightAddExp));
}

static Expression* handleAddExpNode(Ref<ParseNode> pNode)
{
	i32 parseNodesCount = i32(pNode->pParseNodes.size());
	if (parseNodesCount != 2)
	{
		return nullptr;
	}

	if (IS_ESP_NODE(pNode->pParseNodes[1]))
	{
		return GET_EXP(pNode, 0);
	}
	else
	{
		return handleRightAddExp_1(GET_EXP(pNode, 0), pNode->pParseNodes[1]);
	}
}

static Expression* handleRightAddExp_1(Expression* left, Ref<ParseNode> pNode)
{
	Expression* op	  = GET_EXP(pNode, 0);
	Expression* right = GET_EXP(pNode, 1);

	Expression* pNextExp = nullptr;

	const Token& opToken = ((LiteralExpression*)op)->getToken();
	switch (opToken.value.stringValue[0])
	{
	case '+':
		pNextExp = new OperatorExpression(EXPRESSION_TYPE_ADD, left, right);
		break;
	case '-':
		pNextExp = new OperatorExpression(EXPRESSION_TYPE_SUBTRACT, left, right);
		break;
	default:
		return nullptr;
	}

	if (IS_ESP_NODE(pNode->pParseNodes[2]))
	{
		return pNextExp;
	}
	else
	{
		return handleRightAddExp_1(pNextExp, pNode->pParseNodes[2]);
	}
}

bool AST::parseLeftAddExp(Ref<ParseNode> pNode)
{
	return parseLiteral(pNode);
}

bool AST::parseRightAddExp_1(Ref<ParseNode> pNode)
{
	PARSE_NODE_AND(
		pNode, nullptr, PARSE_TOKEN(TOKEN_TYPE_OPERATOR), AST_BINDING(parseLeftAddExp), AST_BINDING(parseRightAddExp));
}

bool AST::parseRightAddExp(Ref<ParseNode> pNode)
{
	PARSE_NODE_OR(pNode, AST_BINDING(parseRightAddExp_1), AST_BINDING(parseEpsilon));
}

bool AST::parseLiteral(Ref<ParseNode> pNode)
{
	PARSE_NODE_OR(pNode, PARSE_TOKEN(TOKEN_TYPE_INTEGER), PARSE_TOKEN(TOKEN_TYPE_FLOAT), AST_BINDING(parseLiteral_1));
}

bool AST::parseLiteral_1(Ref<ParseNode> pNode)
{
	PARSE_NODE_AND(
		pNode,
		[&](Ref<ParseNode> pNode) { return GET_EXP(pNode, 1); },
		PARSE_TOKEN(TOKEN_TYPE_OPEN_PARENTHESIS),
		AST_BINDING(parseAddExp),
		PARSE_TOKEN(TOKEN_TYPE_CLOSE_PARENTHESIS));
}

bool AST::parseToken(Ref<ParseNode> pNode, TokenType expectedType)
{
	if (m_tokenCursor >= static_cast<i32>(m_tokens.size()))
	{
		return false;
	}

	Token& token = m_tokens[m_tokenCursor];
	if (token.type == expectedType)
	{
		pNode->pToken  = &token;
		pNode->handler = handleLiteralNode;
		m_tokenCursor++;
		return true;
	}

	return false;
}

bool AST::parseEpsilon(Ref<ParseNode> pNode)
{
	pNode->handler = handleEpsilonNode;
	return true;
}

} // namespace ntt
