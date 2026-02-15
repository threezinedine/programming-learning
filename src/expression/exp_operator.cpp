#include "exp_operator.h"

namespace ntt {

OperatorExpression::OperatorExpression(ExpressionType type, Expression* left, Expression* right)
	: Expression(type)
	, m_left(left)
	, m_right(right)
{
}

OperatorExpression::~OperatorExpression()
{
	delete m_left;
	delete m_right;
}

} // namespace ntt
