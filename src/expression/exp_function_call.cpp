#include "exp_function_call.h"

namespace ntt {

FunctionCallExpression::FunctionCallExpression(const std::string&			 functionName,
											   std::vector<Ref<Expression>>& arguments)
	: Expression(EXPRESSION_TYPE_FUNCTION_CALL) // You can set this to a specific type if needed
	, m_functionName(functionName)
	, m_arguments(arguments)
{
}

FunctionCallExpression::~FunctionCallExpression()
{
}

nlohmann::json FunctionCallExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]			= "FunctionCall";
	jsonObj["functionName"] = m_functionName;
	jsonObj["arguments"]	= nlohmann::json::array();
	for (const auto& argument : m_arguments)
	{
		jsonObj["arguments"].push_back(argument->toJson());
	}
	return jsonObj;
}

} // namespace ntt