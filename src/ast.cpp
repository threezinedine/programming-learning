#include "ast.h"

namespace ntt {

/*

Grammar:

Exp: AddExp;

AddExp: LeftAddExp RightAddExp;

RightAddExp: + LeftAddExp RightAddExp
		   | - LeftAddExp RightAddExp
		   | ε
		   ;

LeftAddExp: LeftMulExp RightMulExp;

RightMulExp: * LeftMulExp RightMulExp
			 | / LeftMulExp RightMulExp
			 | ε
			 ;

LeftMulExp: PrimaryExp;

PrimaryExp: ( AddExp )
			| Literal
			;

Literal: Integer
		| Float
		;

 */

using ParseFunc = std::function<bool(ParseNode* pNode)>;

#define AST_BINDING(func) std::bind(&AST::func, this, std::placeholders::_1)

#define PARSE_NODE_AND(parentNode, handlerPtr, ...)                                                                    \
	do                                                                                                                 \
	{                                                                                                                  \
		i32		  pivot			= m_tokenCursor;                                                                       \
		ParseFunc handleFuncs[] = {__VA_ARGS__};                                                                       \
		i32		  funcCount		= sizeof(handleFuncs) / sizeof(ParseFunc);                                             \
		for (i32 i = 0; i < funcCount; i++)                                                                            \
		{                                                                                                              \
			ParseNode* _pTempNode								   = newNode();                                        \
			parentNode->pParseNodes[parentNode->parseNodesCount++] = _pTempNode;                                       \
			if (!handleFuncs[i](_pTempNode))                                                                           \
			{                                                                                                          \
				m_tokenCursor = pivot;                                                                                 \
				return false;                                                                                          \
			}                                                                                                          \
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
			ParseNode* _pTempNode = newNode();                                                                         \
			if (handleFuncs[i](_pTempNode))                                                                            \
			{                                                                                                          \
				parentNode->pParseNodes[parentNode->parseNodesCount++] = _pTempNode;                                   \
				parentNode->handler									   = handleOrNode;                                 \
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

#define PARSE_TOKEN(expectedType) [&](ParseNode* pNode) { return parseToken(pNode, expectedType); }

static Expression* handleLiteralNode(ParseNode* pNode)
{
	return new LiteralExpression(*pNode->pToken);
}

static Expression* handleEpsilonNode(ParseNode* pNode)
{
	return new EpsilonExpression();
}

static Expression* handleOrNode(ParseNode* pNode)
{
	return pNode->pParseNodes[0]->handler(pNode->pParseNodes[0]);
}

AST::AST(const std::string& sourceCode, TokenParser tokenParser)
{
	memset(m_nodesHub, 0, sizeof(m_nodesHub));
	m_nodesHubCursor = 0;

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
	m_pRootExpNode = newNode();
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

ParseNode* AST::newNode()
{
	if (m_nodesHubCursor >= MAX_NODES)
	{
		return nullptr;
	}

	return &m_nodesHub[m_nodesHubCursor++];
}

AST::~AST()
{
	if (m_pRootExpression != nullptr)
	{
		delete m_pRootExpression;
		m_pRootExpression = nullptr;
	}
}

bool AST::parseExp(ParseNode* pNode)
{
	return parseAddExp(pNode);
}

static Expression* handleAddExpNode(ParseNode* pNode);

bool AST::parseAddExp(ParseNode* pNode)
{
#if 0
	// clang-format off
	PARSE_NODE_AND(
		pNode, handleAddExpNode, 
		AST_BINDING(parseLiteral), 
		PARSE_TOKEN(TOKEN_TYPE_OPERATOR), 
		AST_BINDING(parseLiteral));
	// clang-format on
#else
	PARSE_NODE_AND(pNode,
				   handleAddExpNode,
				   AST_BINDING(parseLiteral),
				   PARSE_TOKEN(TOKEN_TYPE_OPERATOR),
				   AST_BINDING(parseLiteral));
#endif
}

static Expression* handleAddExpNode(ParseNode* pNode)
{
	Expression* leftExp	  = GET_EXP(pNode, 0);
	Expression* operation = GET_EXP(pNode, 1);
	Expression* rightExp  = GET_EXP(pNode, 2);

	VERIFY_EXP(leftExp, operation, rightExp);

	if (operation->getType() != EXPRESSION_TYPE_LITERAL)
	{
		return nullptr;
	}

	const Token& opToken = ((LiteralExpression*)operation)->getToken();

	if (opToken.type != TOKEN_TYPE_OPERATOR)
	{
		return nullptr;
	}

	switch (opToken.value.stringValue[0])
	{
	case '+':
		return new OperatorExpression(EXPRESSION_TYPE_ADD, leftExp, rightExp);
	case '-':
		return new OperatorExpression(EXPRESSION_TYPE_SUBTRACT, leftExp, rightExp);
	default:
		return nullptr;
	};
}

bool AST::parseLiteral(ParseNode* pNode)
{
	PARSE_NODE_OR(pNode, PARSE_TOKEN(TOKEN_TYPE_INTEGER), PARSE_TOKEN(TOKEN_TYPE_FLOAT));
}

bool AST::parseToken(ParseNode* pNode, TokenType expectedType)
{
	if (m_tokenCursor >= static_cast<i32>(m_tokens.size()))
	{
		return false;
	}

	Token& token = m_tokens[m_tokenCursor];
	if (token.type == expectedType)
	{
		pNode->pToken  = &token;
		pNode->type	   = PARSE_ATOMIC_LITERAL;
		pNode->handler = handleLiteralNode;
		m_tokenCursor++;
		return true;
	}

	return false;
}

bool AST::parseEpsilon(ParseNode* pNode)
{
	pNode->type	   = PARSE_ATOMIC_EPSILON;
	pNode->handler = handleEpsilonNode;
	return true;
}

} // namespace ntt
