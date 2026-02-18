#include "exp_function.h"

namespace ntt {

FunctionExpression::FunctionExpression(const std::string&							 functionName,
									   const std::vector<Ref<IdentifierExpression>>& parameters,
									   std::vector<Ref<Expression>>					 statements)
	: Expression(EXPRESSION_TYPE_FUNCTION) // You can set this to a specific type if needed
	, m_functionName(functionName)
	, m_parameters(parameters)
	, m_statements(statements)
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
		jsonObj["parameters"].push_back(param->toJson());
	}
	jsonObj["body"] = nlohmann::json::array();
	for (const auto& statement : m_statements)
	{
		jsonObj["body"].push_back(statement->toJson());
	}
	return jsonObj;
}

} // namespace ntt