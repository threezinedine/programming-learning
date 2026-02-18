#pragma once

#include "exp_base.h"
#include <vector>

namespace ntt {

class ProgramExpression : public Expression
{
public:
	ProgramExpression();
	~ProgramExpression();

	inline void addSegment(Ref<Expression>& segment)
	{
		m_segments.push_back(segment);
	}

	inline void updateSegment(std::vector<Ref<Expression>>& segments)
	{
		for (const auto& segment : segments)
		{
			m_segments.push_back(segment);
		}
	}

	nlohmann::json toJson() const override;

private:
	std::vector<Ref<Expression>> m_segments;
};

} // namespace ntt
