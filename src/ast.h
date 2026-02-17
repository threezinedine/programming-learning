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

	inline const Expression* getRootExpression() const
	{
		return m_pRootExpression;
	}

	inline bool isValid() const
	{
		return m_isValid;
	}

private:
	Expression* parsePrimaryExp();
	Expression* parseLiteral();
	Expression* parseLiteral_1();
	Expression* parseEpsilon();
	Expression* parseToken(TokenType expectedType);

private:
	Expression* parseExp();
	Expression* parseAddExp();
	Expression* parseLeftAddExp();
	bool		parseRightAddExp(OperatorExpression** ppAddExp);

	Expression* parseLeftMulExp();
	Expression* parseRightMulExp_1();
	Expression* parseRightMulExp();

private:
	std::vector<Token> m_tokens;
	i32				   m_tokenCursor;
	Expression*		   m_pRootExpression;
	bool			   m_isValid;
};

} // namespace ntt
