#include "exp_operator.h"
#include <cstdio>

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

void OperatorExpression::print() const
{
	if (m_left)
	{
		m_left->print();
	}

	switch (type)
	{
	case EXPRESSION_TYPE_ADD:
		printf(" + ");
		break;
	case EXPRESSION_TYPE_SUBTRACT:
		printf(" - ");
		break;
	case EXPRESSION_TYPE_MULTIPLY:
		printf(" * ");
		break;
	case EXPRESSION_TYPE_DIVIDE:
		printf(" / ");
		break;
	default:
		printf(" ? ");
		break;
	}

	if (m_right)
	{
		m_right->print();
	}
}

} // namespace ntt
