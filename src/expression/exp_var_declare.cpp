#include "exp_var_declare.h"

namespace ntt {

VariableDeclarationExpression::VariableDeclarationExpression(const std::string& identifier)
	: Expression(EXPRESSION_TYPE_VARIABLE_DECLARATION)
	, m_identifier(identifier)
{
}

VariableDeclarationExpression::~VariableDeclarationExpression()
{
}

nlohmann::json VariableDeclarationExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]		  = "VariableDeclaration";
	jsonObj["identifier"] = m_identifier;
	return jsonObj;
}

} // namespace ntt
