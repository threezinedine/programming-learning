#pragma once
#include "exp_base.h"

namespace ntt {

class VariableDeclarationExpression : public Expression
{
public:
	VariableDeclarationExpression(const std::string& identifier);
	~VariableDeclarationExpression();

	nlohmann::json toJson() const override;

private:
	std::string m_identifier;
};

} // namespace ntt