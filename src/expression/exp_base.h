#pragma once
#include "exp_types.h"
#include <nlohmann/json.hpp>
#include <string>

namespace ntt {

class Expression
{
public:
	Expression(ExpressionType type);
	virtual ~Expression();

	inline ExpressionType getType() const
	{
		return type;
	}

	virtual nlohmann::json toJson() const = 0;

	void print() const
	{
		printf("%s", toJson().dump(4).c_str());
	}

protected:
	ExpressionType type;
};

class EpsilonExpression : public Expression
{
public:
	EpsilonExpression();
	~EpsilonExpression();

	nlohmann::json toJson() const override
	{
		return nlohmann::json("{ \"type\": \"Epsilon\" }");
	}
};

} // namespace ntt
