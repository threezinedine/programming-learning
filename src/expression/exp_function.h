#pragma once

#include "exp_base.h"
#include "exp_identifier.h"
#include <string>
#include <vector>

namespace ntt {

class FunctionExpression : public Expression
{
public:
	FunctionExpression(const std::string&							 functionName,
					   const std::vector<Ref<IdentifierExpression>>& parameters,
					   std::vector<Ref<Expression>>					 statements);
	~FunctionExpression();

	nlohmann::json toJson() const override;

private:
	std::string							   m_functionName;
	std::vector<Ref<IdentifierExpression>> m_parameters;
	std::vector<Ref<Expression>>		   m_statements;
};

} // namespace ntt