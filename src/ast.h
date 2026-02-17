#pragma once
#include "common.h"
#include "expression/expression.h"
#include "tokenizer.h"
#include <functional>

#define MAX_NODES 20

namespace ntt {

struct ParseNode;

typedef bool (*TokenParser)(const std::string& sourceCode, std::vector<Token>& tokens);

/*

Grammar:

Exp: AddExp;

AddExp: LeftAddExp RightAddExp;

RightAddExp: + LeftAddExp RightAddExp
		   | - LeftAddExp RightAddExp
		   | ε
		   ;

LeftAddExp: LeftMulExp RightMulExp;

RightMulExp: * LeftMulExp RightMulExp
			 | / LeftMulExp RightMulExp
			 | ε
			 ;

LeftMulExp: PrimaryExp;

PrimaryExp: ( AddExp )
			| Literal
			;

Literal: Integer
		| Float
		;

 */

class AST
{
public:
	AST(const std::string& sourceCode, TokenParser tokenParser = nullptr);
	~AST();

	inline const Ref<Expression> getRootExpression() const
	{
		return m_pRootExpression;
	}

	inline bool isValid() const
	{
		return m_isValid;
	}

private:
	Ref<Expression> parsePrimaryExp();
	Ref<Expression> parseLiteral();
	Ref<Expression> parseLiteral_1();
	Ref<Expression> parseEpsilon();
	Token*			parseToken(TokenType expectedType);

private:
	Ref<Expression> parseExp();
	Ref<Expression> parseAddExp();
	Ref<Expression> parseLeftAddExp();
	bool			parseRightAddExp(Ref<OperatorExpression>& pAddExp);

	Ref<Expression> parseLeftMulExp();
	bool			parseRightMulExp(Ref<OperatorExpression>& pMulExp);

private:
	std::vector<Token> m_tokens;
	i32				   m_tokenCursor;
	Ref<Expression>	   m_pRootExpression;
	bool			   m_isValid;
};

} // namespace ntt
