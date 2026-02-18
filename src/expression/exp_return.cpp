#include "exp_return.h"

namespace ntt {

ReturnExpression::ReturnExpression(Ref<Expression>& returnValue)
	: Expression(EXPRESSION_TYPE_RETURN)
	, m_returnValue(returnValue)
{
}

ReturnExpression::~ReturnExpression()
{
}

nlohmann::json ReturnExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]	 = "Return";
	jsonObj["value"] = m_returnValue ? m_returnValue->toJson() : nullptr;
	return jsonObj;
}

} // namespace ntt