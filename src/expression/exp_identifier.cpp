#include "exp_identifier.h"

namespace ntt {

IdentifierExpression::IdentifierExpression(const std::string& name)
	: Expression(EXPRESSION_TYPE_IDENTIFIER)
	, m_name(name)
{
}

IdentifierExpression::~IdentifierExpression()
{
}

nlohmann::json IdentifierExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"] = "Identifier";
	jsonObj["name"] = m_name;
	return jsonObj;
}

} // namespace ntt