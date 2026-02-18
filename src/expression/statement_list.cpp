#include "statement_list.h"

namespace ntt {

StatementListExpression::StatementListExpression()
	: Expression(EXPRESSION_TYPE_STATEMENTS_LIST)
{
}

StatementListExpression::~StatementListExpression()
{
}

nlohmann::json StatementListExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]		  = "StatementsList";
	jsonObj["statements"] = nlohmann::json::array();
	for (const auto& statement : m_statements)
	{
		jsonObj["statements"].push_back(statement->toJson());
	}
	return jsonObj;
}

} // namespace ntt