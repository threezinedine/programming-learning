#include "exp_literal.h"

namespace ntt {

LiteralExpression::LiteralExpression(Token token)
	: Expression(EXPRESSION_TYPE_LITERAL)
	, m_token(token)
{
	if (m_token.type == TOKEN_TYPE_STRING)
	{
		// Remove the surrounding quotes from the string value
		size_t len = strlen(m_token.value.stringValue);
		if (len >= 2 && m_token.value.stringValue[0] == '"' && m_token.value.stringValue[len - 1] == '"')
		{
			memmove(m_token.value.stringValue, m_token.value.stringValue + 1, len - 2);
			m_token.value.stringValue[len - 2] = '\0';
		}
	}
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
	case TOKEN_TYPE_BOOLEAN:
		jsonObj["type"]	 = "Boolean";
		jsonObj["value"] = (m_token.value.stringValue[0] == 't'); // true if starts with 't', false otherwise
		break;
	case TOKEN_TYPE_STRING:
		jsonObj["type"]	 = "String";
		jsonObj["value"] = std::string(m_token.value.stringValue);
		break;
	default:
		jsonObj["type"] = "Unknown";
		break;
	}

	return jsonObj;
}

} // namespace ntt