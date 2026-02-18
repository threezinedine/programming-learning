#include "exp_program.h"

namespace ntt {

ProgramExpression::ProgramExpression()
	: Expression(EXPRESSION_TYPE_PROGRAM)
{
}

ProgramExpression::~ProgramExpression()
{
}

nlohmann::json ProgramExpression::toJson() const
{
	nlohmann::json jsonObj;
	jsonObj["type"]		= "Program";
	jsonObj["segments"] = nlohmann::json::array();
	for (const auto& segment : m_segments)
	{
		jsonObj["segments"].push_back(segment->toJson());
	}
	return jsonObj;
}

} // namespace ntt