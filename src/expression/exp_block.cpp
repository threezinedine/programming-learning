#include "exp_block.h"

namespace ntt {

BlockExpression::BlockExpression(std::vector<Ref<Expression>>& statements)
	: Expression(EXPRESSION_TYPE_BLOCK)
	, m_statements(statements)
{
}

BlockExpression::~BlockExpression()
{
}

nlohmann::json BlockExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]		  = "Block";
	jsonObj["statements"] = nlohmann::json::array();
	for (const auto& statement : m_statements)
	{
		jsonObj["statements"].push_back(statement->toJson());
	}
	return jsonObj;
}

} // namespace ntt