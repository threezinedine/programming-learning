#pragma once
#include "exp_base.h"
#include "tokenizer.h"

namespace ntt {

class LiteralExpression : public Expression
{
public:
	LiteralExpression(Token token);
	~LiteralExpression() override;

	const Token& getToken() const
	{
		return m_token;
	}

	nlohmann::json toJson() const override;

private:
	Token m_token;
};

} // namespace ntt
