#pragma once

#include "exp_base.h"

namespace ntt {

class IdentifierExpression : public Expression
{
public:
	IdentifierExpression(const std::string& name);
	~IdentifierExpression();

	nlohmann::json toJson() const override;

private:
	std::string m_name;
};

} // namespace ntt
