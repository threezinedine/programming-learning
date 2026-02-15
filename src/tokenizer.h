#pragma once
#include "common.h"
#include <cstring>
#include <regex>
#include <string>
#include <vector>

namespace ntt {

enum TokenType
{
	TOKEN_TYPE_UNKNOWN,
	TOKEN_TYPE_INTEGER,
	TOKEN_TYPE_FLOAT,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_OPERATOR,
	TOKEN_TYPE_OPEN_PARENTHESIS,
	TOKEN_TYPE_CLOSE_PARENTHESIS,
	TOKEN_TYPE_OPEN_BRACE,
	TOKEN_TYPE_CLOSE_BRACE,
	TOKEN_TYPE_SEMICOLON,
	TOKEN_TYPE_COLON,
	TOKEN_TYPE_COMMA,
	TOKEN_TYPE_COUNT,
};

struct TokenPattern
{
	TokenType  type;
	std::regex pattern;
};

union TokenValue {
	i32	 integerValue;
	f32	 floatValue;
	char stringValue[256];

	TokenValue()
	{
		memset(this, 0, sizeof(TokenValue));
	}
};

struct Token
{
	TokenType  type;
	TokenValue value;
};

void printToken(const Token& token);

bool parseTokens(const std::string& sourceCode, std::vector<Token>& tokens);

} // namespace ntt
