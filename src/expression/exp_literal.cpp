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

nlohmann::json LiteralExpression::toJson() const
{
	nlohmann::json jsonObj = nlohmann::json::parse("{}");

	switch (m_token.type)
	{
	case TOKEN_TYPE_INTEGER:
		jsonObj["type"]	 = "Integer";
		jsonObj["value"] = m_token.value.integerValue;
		break;
	case TOKEN_TYPE_FLOAT:
		jsonObj["type"]	 = "Float";
		jsonObj["value"] = m_token.value.floatValue;
		break;
	default:
		jsonObj["type"] = "Unknown";
		break;
	}

	return jsonObj;
}

} // namespace ntt