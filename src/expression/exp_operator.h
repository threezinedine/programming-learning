#pragma once

#include "exp_base.h"

namespace ntt {

class OperatorExpression : public Expression
{
public:
	OperatorExpression(ExpressionType type, Expression* left, Expression* right);
	~OperatorExpression();

	void print() const override;

private:
	Expression* m_left;
	Expression* m_right;
};

} // namespace ntt
