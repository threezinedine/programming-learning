#include "ast.h"
#include "expression/expression.h"
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

	std::string sourceCode((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
	ntt::AST	ast(sourceCode);

	if (ast.isValid())
	{
		ast.getRootExpression()->print();
		printf("\n");
	}
	else
	{
		fprintf(stderr, "Failed to parse expression.\n");
	}

	return 0;
}
