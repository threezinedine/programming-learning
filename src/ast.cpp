#include "ast.h"

namespace ntt {

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

#define SETUP_PARSE_FUNCTION()                                                                                         \
	do                                                                                                                 \
	{                                                                                                                  \
		if (tokenCursor >= static_cast<i32>(tokens.size()))                                                            \
		{                                                                                                              \
			return nullptr;                                                                                            \
		}                                                                                                              \
	} while (0)

#define PARSE_SUB_FUNCTION(shiftTokenCount, parseFunc)                                                                 \
	do                                                                                                                 \
	{                                                                                                                  \
		i32 pivot = tokenCursor;                                                                                       \
                                                                                                                       \
		for (i32 i = 0; i < shiftTokenCount; i++)                                                                      \
		{                                                                                                              \
			if (tokenCursor >= static_cast<i32>(tokens.size()))                                                        \
			{                                                                                                          \
				return nullptr;                                                                                        \
			}                                                                                                          \
			tokenCursor++;                                                                                             \
		}                                                                                                              \
                                                                                                                       \
		Expression* subExp = parseFunc(tokens, tokenCursor);                                                           \
		if (subExp)                                                                                                    \
		{                                                                                                              \
			return subExp;                                                                                             \
		}                                                                                                              \
		tokenCursor = pivot;                                                                                           \
	} while (0)

static Expression* parseAddExp(const std::vector<Token>& tokens, i32& tokenCursor);
static Expression* parseLeftAddExp(const std::vector<Token>& tokens, i32& tokenCursor);
static Expression* parseRightAddExp(const std::vector<Token>& tokens, i32& tokenCursor);
static Expression* parseLeftMulExp(const std::vector<Token>& tokens, i32& tokenCursor);
static Expression* parseRightMulExp(const std::vector<Token>& tokens, i32& tokenCursor);
static Expression* parsePrimaryExp(const std::vector<Token>& tokens, i32& tokenCursor);
static Expression* parseLiteral(const std::vector<Token>& tokens, i32& tokenCursor);

Expression* parseExp(const std::vector<Token>& tokens)
{
	i32 tokenCount	= static_cast<i32>(tokens.size());
	i32 tokenCursor = 0;

	Expression* exp = parseLiteral(tokens, tokenCursor);

	if (tokenCursor != tokenCount)
	{
		// Handle error: not all tokens were consumed
		delete exp;
		return nullptr;
	}

	return exp;
}

static Expression* parseAddExp(const std::vector<Token>& tokens, i32& tokenCursor)
{
	return nullptr;
}

static Expression* parseLeftAddExp(const std::vector<Token>& tokens, i32& tokenCursor)
{
	return nullptr;
}

static Expression* parseRightAddExp(const std::vector<Token>& tokens, i32& tokenCursor)
{
	return nullptr;
}

static Expression* parseLeftMulExp(const std::vector<Token>& tokens, i32& tokenCursor)
{
	return nullptr;
}

static Expression* parseRightMulExp(const std::vector<Token>& tokens, i32& tokenCursor)
{
	return nullptr;
}

static Expression* parsePrimaryExp(const std::vector<Token>& tokens, i32& tokenCursor)
{
	SETUP_PARSE_FUNCTION();

	i32 pivotCursor = tokenCursor;

	const Token& token = tokens[tokenCursor];

	if (token.type == TOKEN_TYPE_OPEN_PARENTHESIS)
	{
		Expression* exp = nullptr;
		PARSE_SUB_FUNCTION(1, parseAddExp);
	}
	else
	{
		PARSE_SUB_FUNCTION(0, parseLiteral);
	}

	return nullptr;
}

static Expression* parseLiteral(const std::vector<Token>& tokens, i32& tokenCursor)
{
	SETUP_PARSE_FUNCTION();

	const Token& token = tokens[tokenCursor];

	if (token.type == TOKEN_TYPE_INTEGER || token.type == TOKEN_TYPE_FLOAT)
	{
		tokenCursor++;
		return new LiteralExpression(token);
	}

	return nullptr;
}

} // namespace ntt
