#include <cstdio>
#include <fstream>
#include <tokenizer.h>

int main(void)
{
	std::ifstream sourceFile(STRINGIFY(BASE_DIR) "/example.ntt");
	if (!sourceFile.is_open())
	{
		fprintf(stderr, "Failed to open source file.\n");
		return 1;
	}

	std::string				sourceCode((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
	std::vector<ntt::Token> tokens;

	if (!ntt::parseTokens(sourceCode, tokens))
	{
		fprintf(stderr, "Failed to parse tokens.\n");
		return 1;
	}

	for (const auto& token : tokens)
	{
		ntt::printToken(token);
	}

	return 0;
}
