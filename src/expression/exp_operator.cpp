#include "exp_operator.h"
#include <cstdio>

namespace ntt {

OperatorExpression::OperatorExpression(ExpressionType type, Ref<Expression> left, Ref<Expression> right)
	: Expression(type)
	, m_left(left)
	, m_right(right)
{
}

OperatorExpression::~OperatorExpression()
{
}

nlohmann::json OperatorExpression::toJson() const
{
	nlohmann::json jsonObj = nlohmann::json::parse("{}");
	switch (type)
	{
	case EXPRESSION_TYPE_ADD:
		jsonObj["type"] = "Add";
		break;
	case EXPRESSION_TYPE_SUBTRACT:
		jsonObj["type"] = "Subtract";
		break;
	case EXPRESSION_TYPE_MULTIPLY:
		jsonObj["type"] = "Multiply";
		break;
	case EXPRESSION_TYPE_DIVIDE:
		jsonObj["type"] = "Divide";
		break;
	default:
		jsonObj["type"] = "Unknown";
		break;
	}

	jsonObj["left"]	 = m_left->toJson();
	jsonObj["right"] = m_right->toJson();

	return jsonObj;
}

} // namespace ntt
