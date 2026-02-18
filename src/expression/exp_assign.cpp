#include "exp_assign.h"

namespace ntt {

AssignmentExpression::AssignmentExpression(const std::string& identifier, Ref<Expression> value)
	: Expression(EXPRESSION_TYPE_VARIABLE_DECLARATION)
	, m_identifier(identifier)
	, m_value(value)
{
}

AssignmentExpression::~AssignmentExpression()
{
}

nlohmann::json AssignmentExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]		  = "Assignment";
	jsonObj["identifier"] = m_identifier;
	jsonObj["value"]	  = m_value->toJson();
	return jsonObj;
}

} // namespace ntt