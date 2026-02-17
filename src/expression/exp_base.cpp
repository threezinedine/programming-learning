#include "exp_base.h"

namespace ntt {

Expression::Expression(ExpressionType type)
	: type(type)
{
}

Expression::~Expression()
{
}

EpsilonExpression::EpsilonExpression()
	: Expression(EXPRESSION_TYPE_EPSILON)
{
}

EpsilonExpression::~EpsilonExpression()
{
}

} // namespace ntt
