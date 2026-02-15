#include "tokenizer.h"
#include <cstdio>

namespace ntt {

// clang-format off
TokenPattern patterns[] = {
	{TOKEN_TYPE_FLOAT   , std::regex("^\\d+\\.\\d+")    },
	{TOKEN_TYPE_INTEGER , std::regex("^\\d+")	        },
	{TOKEN_TYPE_OPERATOR, std::regex("^\\+|\\-|\\*|/|=")},
};
// clang-format on

bool extractNextToken(const std::string& sourceCode, i32& cursor, Token& token)
{
	for (const auto& pattern : patterns)
	{
		std::smatch match;
		std::string remainingCode = sourceCode.substr(cursor);
		if (std::regex_search(remainingCode, match, pattern.pattern))
		{
			token.type = pattern.type;

			if (pattern.type == TOKEN_TYPE_INTEGER)
			{
				token.value.integerValue = std::stoi(match.str());
			}
			else if (pattern.type == TOKEN_TYPE_FLOAT)
			{
				token.value.floatValue = std::stof(match.str());
			}
			else
			{
				memcpy(token.value.stringValue,
					   match.str().c_str(),
					   std::min(sizeof(token.value.stringValue) - 1, match.str().size()));
			}

			cursor += static_cast<i32>(match.length());

			return true;
		}
	}

	return false;
}

bool isIgnoringCharacter(char c)
{
	return std::isspace(c);
}

void skipIgnoringCharacters(const std::string& sourceCode, i32& cursor)
{
	while (cursor < static_cast<i32>(sourceCode.length()) && isIgnoringCharacter(sourceCode[cursor]))
	{
		cursor++;
	}
}

bool parseTokens(const std::string& sourceCode, std::vector<Token>& tokens)
{
	i32			sourceLength   = static_cast<i32>(sourceCode.length());
	i32			sourceCursor   = 0;
	std::string sourceCodeCopy = sourceCode;

	for (i32 i = 0; i < sourceLength; i++)
	{
		if (sourceCodeCopy[i] == '\n')
		{
			sourceCodeCopy[i] = ' ';
		}
	}

	while (true)
	{
		if (sourceCursor >= sourceLength)
		{
			return true;
		}

		skipIgnoringCharacters(sourceCodeCopy, sourceCursor);

		if (sourceCursor >= sourceLength)
		{
			return true;
		}

		Token token;
		if (!extractNextToken(sourceCodeCopy, sourceCursor, token))
		{
			return false;
		}
		tokens.push_back(token);
	}
}

void printToken(const Token& token)
{
	switch (token.type)
	{
	case TOKEN_TYPE_INTEGER:
		printf("<Token type=INTEGER value=%d>\n", token.value.integerValue);
		break;
	case TOKEN_TYPE_FLOAT:
		printf("<Token type=FLOAT value=%f>\n", token.value.floatValue);
		break;
	case TOKEN_TYPE_STRING:
		printf("<Token type=STRING value=%s>\n", token.value.stringValue);
	case TOKEN_TYPE_OPERATOR:
		printf("<Token type=OPERATOR value=%s>\n", token.value.stringValue);
		break;
	default:
		printf("<Token type=UNKNOWN>\n");
		break;
	}
}

} // namespace ntt