#pragma once
#include "exp_base.h"

namespace ntt {

class ReturnExpression : public Expression
{
public:
	ReturnExpression(Ref<Expression>& returnValue);
	~ReturnExpression();

	nlohmann::json toJson() const override;

private:
	Ref<Expression> m_returnValue;
};

} // namespace ntt
