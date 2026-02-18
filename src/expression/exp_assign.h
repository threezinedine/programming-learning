#pragma once

#include "exp_base.h"

namespace ntt {

class AssignmentExpression : public Expression
{
public:
	AssignmentExpression(const std::string& identifier, Ref<Expression> value);
	~AssignmentExpression();

	nlohmann::json toJson() const override;

private:
	std::string		m_identifier;
	Ref<Expression> m_value;
};

} // namespace ntt