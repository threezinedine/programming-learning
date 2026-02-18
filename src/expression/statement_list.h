#pragma once

#include "exp_base.h"
#include <vector>

namespace ntt {

class StatementListExpression : public Expression
{
public:
	StatementListExpression();
	~StatementListExpression();

	nlohmann::json toJson() const override;

public:
	inline void addStatement(Ref<Expression>& statement)
	{
		m_statements.push_back(statement);
	}

private:
	std::vector<Ref<Expression>> m_statements;
};

} // namespace ntt