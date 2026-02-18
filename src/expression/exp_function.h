#pragma once

#include "exp_base.h"

namespace ntt {

class FunctionExpression : public Expression
{
public:
	FunctionExpression(const std::string&			   functionName,
					   const std::vector<std::string>& parameters,
					   Ref<Expression>				   body);
	~FunctionExpression();

	nlohmann::json toJson() const override;

private:
	std::string				 m_functionName;
	std::vector<std::string> m_parameters;
	Ref<Expression>			 m_body;
};

} // namespace ntt