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

std::string LiteralExpression::toString() const
{
	char buffer[256] = {0};

	if (m_token.type == TOKEN_TYPE_INTEGER)
	{
		snprintf(buffer, sizeof(buffer), "%d", m_token.value.integerValue);
		return std::string(buffer);
	}
	else if (m_token.type == TOKEN_TYPE_FLOAT)
	{
		snprintf(buffer, sizeof(buffer), "%f", m_token.value.floatValue);
		return std::string(buffer);
	}
	else
	{
		return "0";
	}
}

} // namespace ntt