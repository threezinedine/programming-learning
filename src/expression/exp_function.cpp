#include "exp_function.h"

namespace ntt {

FunctionExpression::FunctionExpression(const std::string&			   functionName,
									   const std::vector<std::string>& parameters,
									   Ref<Expression>				   body)
	: Expression(EXPRESSION_TYPE_FUNCTION) // You can set this to a specific type if needed
	, m_functionName(functionName)
	, m_parameters(parameters)
	, m_body(body)
{
}

FunctionExpression::~FunctionExpression()
{
}

nlohmann::json FunctionExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]			= "Function";
	jsonObj["functionName"] = m_functionName;
	jsonObj["parameters"]	= nlohmann::json::array();
	for (const auto& param : m_parameters)
	{
		jsonObj["parameters"].push_back(param);
	}
	jsonObj["body"] = m_body->toJson();
	return jsonObj;
}

} // namespace ntt