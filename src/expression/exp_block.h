#pragma once

#include "exp_base.h"
#include <vector>

namespace ntt {

class BlockExpression : public Expression
{
public:
	BlockExpression(std::vector<Ref<Expression>>& statements);
	~BlockExpression();

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