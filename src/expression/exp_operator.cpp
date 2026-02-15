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

std::string OperatorExpression::toString() const
{
	char buffer[256] = {0};

	switch (type)
	{
	case EXPRESSION_TYPE_ADD:
		snprintf(buffer,
				 sizeof(buffer),
				 "<AddExp left=%s right=%s>",
				 m_left->toString().c_str(),
				 m_right->toString().c_str());
		break;
	case EXPRESSION_TYPE_SUBTRACT:
		snprintf(buffer,
				 sizeof(buffer),
				 "<SubtractExp left=%s right=%s>",
				 m_left->toString().c_str(),
				 m_right->toString().c_str());
		break;
	case EXPRESSION_TYPE_MULTIPLY:
		snprintf(buffer,
				 sizeof(buffer),
				 "<MultiplyExp left=%s right=%s>",
				 m_left->toString().c_str(),
				 m_right->toString().c_str());
		break;
	case EXPRESSION_TYPE_DIVIDE:
		snprintf(buffer,
				 sizeof(buffer),
				 "<DivideExp left=%s right=%s>",
				 m_left->toString().c_str(),
				 m_right->toString().c_str());
		break;
	default:
		printf(" ? ");
		break;
	}

	return std::string(buffer);
}

} // namespace ntt
