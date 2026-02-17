#pragma once

#include "exp_base.h"

namespace ntt {

class OperatorExpression : public Expression
{
public:
	OperatorExpression(ExpressionType type, Expression* left = nullptr, Expression* right = nullptr);
	~OperatorExpression();

	nlohmann::json toJson() const override;

	inline void setLeft(Expression* left)
	{
		m_left = left;
	}

	inline void setRight(Expression* right)
	{
		m_right = right;
	}

	inline void toAddOperator()
	{
		type = EXPRESSION_TYPE_ADD;
	}

	inline void toSubtractOperator()
	{
		type = EXPRESSION_TYPE_SUBTRACT;
	}

	inline void toMultiplyOperator()
	{
		type = EXPRESSION_TYPE_MULTIPLY;
	}

	inline void toDivideOperator()
	{
		type = EXPRESSION_TYPE_DIVIDE;
	}

private:
	Expression* m_left;
	Expression* m_right;
};

} // namespace ntt
