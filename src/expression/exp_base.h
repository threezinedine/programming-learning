#pragma once
#include "exp_types.h"

namespace ntt {

class Expression
{
public:
	Expression(ExpressionType type);
	virtual ~Expression();

	virtual void print() const = 0;

protected:
	ExpressionType type;
};

} // namespace ntt
