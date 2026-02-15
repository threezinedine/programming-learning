#include "exp_literal.h"

namespace ntt {

LiteralExpression::LiteralExpression(Token token)
	: Expression(EXPRESSION_TYPE_LITERAL)
	, m_token(token)
{
}

LiteralExpression::~LiteralExpression()
{
}

void LiteralExpression::print() const
{
	if (m_token.type == TOKEN_TYPE_INTEGER)
	{
		printf("%d", m_token.value.integerValue);
	}
	else if (m_token.type == TOKEN_TYPE_FLOAT)
	{
		printf("%f", m_token.value.floatValue);
	}
	else
	{
		printf("0");
	}
}

} // namespace ntt