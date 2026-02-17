#include "ast.h"

namespace ntt {

#define SETUP()                                                                                                        \
	i32 pivot = m_tokenCursor;                                                                                         \
	(void)pivot
#define SAVE_CHECKPOINT()	 pivot = m_tokenCursor
#define RESTORE_CHECKPOINT() m_tokenCursor = pivot

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

	m_tokenCursor	  = 0;
	i32 nodeIndex	  = 0;
	m_pRootExpression = parseExp();
	m_isValid		  = (m_pRootExpression != nullptr);
}

AST::~AST()
{
}

Ref<Expression> AST::parseExp()
{
	return parseAddExp();
}

Ref<Expression> AST::parseAddExp()
{
	SETUP();
	SAVE_CHECKPOINT();

	Ref<OperatorExpression> pAddExp = CreateRef<OperatorExpression>(EXPRESSION_TYPE_ADD);

	Ref<Expression> pLeftAddExp = parseLeftAddExp();

	if (pLeftAddExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	pAddExp->setLeft(pLeftAddExp);

	SAVE_CHECKPOINT();

	if (parseRightAddExp(pAddExp))
	{
		return pAddExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
		return pLeftAddExp;
	}

	RESTORE_CHECKPOINT();
	return pLeftAddExp;
}

Ref<Expression> AST::parseLeftAddExp()
{
	SETUP();
	SAVE_CHECKPOINT();

	Ref<Expression> pLeftMulExp = parseLeftMulExp();

	if (pLeftMulExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	SAVE_CHECKPOINT();
	Ref<OperatorExpression> pMulExp = CreateRef<OperatorExpression>(EXPRESSION_TYPE_MULTIPLY);
	pMulExp->setLeft(pLeftMulExp);

	if (parseRightMulExp(pMulExp))
	{
		return pMulExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
		return pLeftMulExp;
	}
}

bool AST::parseRightAddExp(Ref<OperatorExpression>& pAddExp)
{
	SETUP();
	SAVE_CHECKPOINT();

	Token* opAdd = parseToken(TOKEN_TYPE_OPERATOR_ADD);
	Token* opSub = parseToken(TOKEN_TYPE_OPERATOR_SUB);

	if (opAdd == nullptr && opSub == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	if (opAdd != nullptr)
	{
		pAddExp->toAddOperator();
	}
	else if (opSub != nullptr)
	{
		pAddExp->toSubtractOperator();
	}

	Ref<Expression> pLeftAddExp = parseLeftAddExp();

	if (pLeftAddExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	pAddExp->setRight(pLeftAddExp);

	SAVE_CHECKPOINT();

	Ref<OperatorExpression> pNewAddExp = CreateRef<OperatorExpression>(EXPRESSION_TYPE_ADD);
	pNewAddExp->setLeft(pAddExp);

	if (parseRightAddExp(pNewAddExp))
	{
		pAddExp = pNewAddExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
	}

	return true;
}

Ref<Expression> AST::parseLeftMulExp()
{
	return parsePrimaryExp();
}

bool AST::parseRightMulExp(Ref<OperatorExpression>& pMulExp)
{
	SETUP();
	SAVE_CHECKPOINT();

	Token* opMul = parseToken(TOKEN_TYPE_OPERATOR_MUL);
	Token* opDiv = parseToken(TOKEN_TYPE_OPERATOR_DIV);

	if (opMul == nullptr && opDiv == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	if (opMul != nullptr)
	{
		pMulExp->toMultiplyOperator();
	}
	else if (opDiv != nullptr)
	{
		pMulExp->toDivideOperator();
	}

	Ref<Expression> pLeftMulExp = parseLeftMulExp();

	if (pLeftMulExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	pMulExp->setRight(pLeftMulExp);

	SAVE_CHECKPOINT();

	Ref<OperatorExpression> pNewMulExp = CreateRef<OperatorExpression>(EXPRESSION_TYPE_MULTIPLY);
	pNewMulExp->setLeft(pMulExp);

	if (parseRightMulExp(pNewMulExp))
	{
		pMulExp = pNewMulExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
	}

	return true;
}

Ref<Expression> AST::parsePrimaryExp()
{
	SETUP();
	SAVE_CHECKPOINT();

	Ref<Expression> pLiteral = parseLiteral();
	if (pLiteral != nullptr)
	{
		return pLiteral;
	}

	RESTORE_CHECKPOINT();

	Ref<Expression> pExpBlock = parseExpBlock();

	if (pExpBlock != nullptr)
	{
		return pExpBlock;
	}

	RESTORE_CHECKPOINT();
	return nullptr;
}

Ref<Expression> AST::parseLiteral()
{
	if (m_tokenCursor >= static_cast<i32>(m_tokens.size()))
	{
		return nullptr;
	}

	Token& token = m_tokens[m_tokenCursor];
	switch (token.type)
	{
	case TOKEN_TYPE_INTEGER:
	case TOKEN_TYPE_FLOAT:
	case TOKEN_TYPE_BOOLEAN:
	case TOKEN_TYPE_STRING:
		m_tokenCursor++;
		return CreateRef<LiteralExpression>(token);
	default:
		return nullptr;
	}
}

Ref<Expression> AST::parseExpBlock()
{
	SETUP();
	SAVE_CHECKPOINT();

	Token* pOpen = parseToken(TOKEN_TYPE_OPEN_PARENTHESIS);

	if (pOpen == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	Ref<Expression> pExp = parseExp();

	if (pExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	Token* pClose = parseToken(TOKEN_TYPE_CLOSE_PARENTHESIS);
	if (pClose == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	return pExp;
}

Token* AST::parseToken(TokenType expectedType)
{
	if (m_tokenCursor >= static_cast<i32>(m_tokens.size()))
	{
		return nullptr;
	}

	Token& token = m_tokens[m_tokenCursor];
	if (token.type == expectedType)
	{
		m_tokenCursor++;
		return &token;
	}

	return nullptr;
}

Ref<Expression> AST::parseEpsilon()
{
	return CreateRef<EpsilonExpression>();
}

} // namespace ntt
