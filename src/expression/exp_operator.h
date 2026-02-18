#pragma once

#include "exp_base.h"

namespace ntt {

class OperatorExpression : public Expression
{
public:
	OperatorExpression(ExpressionType type, Ref<Expression> left = nullptr, Ref<Expression> right = nullptr);
	~OperatorExpression();

	nlohmann::json toJson() const override;

	inline void setLeft(Ref<Expression> left)
	{
		m_left = left;
	}

	inline void setRight(Ref<Expression> right)
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

	inline void setType(ExpressionType newType)
	{
		type = newType;
	}

private:
	Ref<Expression> m_left;
	Ref<Expression> m_right;
};

} // namespace ntt
