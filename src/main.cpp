#include "ast.h"
#include "expression/expression.h"
#include <cstdio>
#include <fstream>
#include <tokenizer.h>

int main(void)
{
#if 0
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
#else
#define TEST_EXPR(code)                                                                                                \
	do                                                                                                                 \
	{                                                                                                                  \
		printf("############# Expression: %s #############\n", code);                                                  \
		ntt::AST ast(code);                                                                                            \
		if (ast.isValid())                                                                                             \
		{                                                                                                              \
			ast.getRootExpression()->print();                                                                          \
			printf("\n");                                                                                              \
		}                                                                                                              \
		else                                                                                                           \
		{                                                                                                              \
			fprintf(stderr, "Failed to parse expression: %s\n", code);                                                 \
		}                                                                                                              \
		printf("\n");                                                                                                  \
		printf("\n");                                                                                                  \
		printf("\n");                                                                                                  \
	} while (0)

	TEST_EXPR("3");
	// TEST_EXPR("3 * 4");
	TEST_EXPR("3 + 4");
	TEST_EXPR("3 + 4 - 5");
	TEST_EXPR("3 - (4 - 5)");

#endif

	return 0;
}
