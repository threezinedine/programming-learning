#pragma once
#include "exp_types.h"
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

	virtual std::string toString() const = 0;

	void print() const
	{
		printf("%s", toString().c_str());
	}

protected:
	ExpressionType type;
};

class EpsilonExpression : public Expression
{
public:
	EpsilonExpression();
	~EpsilonExpression();

	std::string toString() const override
	{
		return "ε";
	}
};

} // namespace ntt
