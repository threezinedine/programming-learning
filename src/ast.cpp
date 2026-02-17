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
	if (m_pRootExpression != nullptr)
	{
		delete m_pRootExpression;
		m_pRootExpression = nullptr;
	}
}

Expression* AST::parseExp()
{
	return parseAddExp();
}

Expression* AST::parseAddExp()
{
	SETUP();
	SAVE_CHECKPOINT();

	OperatorExpression* pAddExp = new OperatorExpression(EXPRESSION_TYPE_ADD);

	Expression* pLeftAddExp = parseLeftAddExp();

	if (pLeftAddExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	pAddExp->setLeft(pLeftAddExp);

	SAVE_CHECKPOINT();

	if (parseRightAddExp(&pAddExp))
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

Expression* AST::parseLeftAddExp()
{
	SETUP();
	SAVE_CHECKPOINT();

	Expression* pLeftMulExp = parseLeftMulExp();

	if (pLeftMulExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	SAVE_CHECKPOINT();
	OperatorExpression* pMulExp = new OperatorExpression(EXPRESSION_TYPE_MULTIPLY);
	pMulExp->setLeft(pLeftMulExp);

	if (parseRightMulExp(&pMulExp))
	{
		return pMulExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
		return pLeftMulExp;
	}
}

bool AST::parseRightAddExp(OperatorExpression** ppAddExp)
{
	SETUP();
	SAVE_CHECKPOINT();

	Expression* opAdd = parseToken(TOKEN_TYPE_OPERATOR_ADD);
	Expression* opSub = parseToken(TOKEN_TYPE_OPERATOR_SUB);

	if (opAdd == nullptr && opSub == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	if (opAdd != nullptr)
	{
		(*ppAddExp)->toAddOperator();
	}
	else if (opSub != nullptr)
	{
		(*ppAddExp)->toSubtractOperator();
	}

	Expression* pLeftAddExp = parseLeftAddExp();

	if (pLeftAddExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	(*ppAddExp)->setRight(pLeftAddExp);

	SAVE_CHECKPOINT();

	OperatorExpression* pNewAddExp = new OperatorExpression(EXPRESSION_TYPE_ADD);
	pNewAddExp->setLeft(*ppAddExp);

	if (parseRightAddExp(&pNewAddExp))
	{
		*ppAddExp = pNewAddExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
	}

	return true;
}

Expression* AST::parseLeftMulExp()
{
	return parsePrimaryExp();
}

bool AST::parseRightMulExp(OperatorExpression** ppMulExp)
{
	SETUP();
	SAVE_CHECKPOINT();

	Expression* opMul = parseToken(TOKEN_TYPE_OPERATOR_MUL);
	Expression* opDiv = parseToken(TOKEN_TYPE_OPERATOR_DIV);

	if (opMul == nullptr && opDiv == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	if (opMul != nullptr)
	{
		(*ppMulExp)->toMultiplyOperator();
	}
	else if (opDiv != nullptr)
	{
		(*ppMulExp)->toDivideOperator();
	}

	Expression* pLeftMulExp = parseLeftMulExp();

	if (pLeftMulExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return false;
	}

	(*ppMulExp)->setRight(pLeftMulExp);

	SAVE_CHECKPOINT();

	OperatorExpression* pNewMulExp = new OperatorExpression(EXPRESSION_TYPE_MULTIPLY);
	pNewMulExp->setLeft(*ppMulExp);

	if (parseRightMulExp(&pNewMulExp))
	{
		*ppMulExp = pNewMulExp;
	}
	else
	{
		RESTORE_CHECKPOINT();
	}

	return true;
}

Expression* AST::parsePrimaryExp()
{
	SETUP();
	SAVE_CHECKPOINT();

	Expression* pLiteral = parseLiteral();
	if (pLiteral != nullptr)
	{
		return pLiteral;
	}

	RESTORE_CHECKPOINT();

	Expression* pLiteral_1 = parseLiteral_1();

	if (pLiteral_1 != nullptr)
	{
		return pLiteral_1;
	}

	RESTORE_CHECKPOINT();
	return nullptr;
}

Expression* AST::parseLiteral()
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
		m_tokenCursor++;
		return new LiteralExpression(token);
	default:
		return nullptr;
	}
}

Expression* AST::parseLiteral_1()
{
	SETUP();
	SAVE_CHECKPOINT();

	Expression* pOpen = parseToken(TOKEN_TYPE_OPEN_PARENTHESIS);

	if (pOpen == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	Expression* pExp = parseExp();

	if (pExp == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	Expression* pClose = parseToken(TOKEN_TYPE_CLOSE_PARENTHESIS);
	if (pClose == nullptr)
	{
		RESTORE_CHECKPOINT();
		return nullptr;
	}

	return pExp;
}

Expression* AST::parseToken(TokenType expectedType)
{
	if (m_tokenCursor >= static_cast<i32>(m_tokens.size()))
	{
		return nullptr;
	}

	Token& token = m_tokens[m_tokenCursor];
	if (token.type == expectedType)
	{
		m_tokenCursor++;
		return new LiteralExpression(token);
	}

	return nullptr;
}

Expression* AST::parseEpsilon()
{
	return new EpsilonExpression();
}

} // namespace ntt
