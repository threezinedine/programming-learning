#pragma once

#include "exp_base.h"
#include <vector>

namespace ntt {

class FunctionCallExpression : public Expression
{
public:
	FunctionCallExpression(const std::string& functionName, std::vector<Ref<Expression>>& arguments);
	~FunctionCallExpression();

	inline void addArgument(Ref<Expression> argument)
	{
		m_arguments.push_back(argument);
	}

	nlohmann::json toJson() const override;

private:
	std::string					 m_functionName;
	std::vector<Ref<Expression>> m_arguments;
};

} // namespace ntt