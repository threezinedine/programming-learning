#pragma once
#include "common.h"
#include "expression/expression.h"
#include "tokenizer.h"
#include <functional>

#define MAX_NODES 10

namespace ntt {

struct ParseNode;

enum ParseAtomic
{
	PARSE_ATOMIC_EPSILON,
	PARSE_ATOMIC_LITERAL,
	PARSE_ATOMIC_OR,
	PARSE_ATOMIC_AND,
};

typedef bool (*TokenParser)(const std::string& sourceCode, std::vector<Token>& tokens);
using ParseNodeHandler = std::function<Expression*(ParseNode* pNode)>;

struct ParseNode
{
	ParseAtomic		 type;
	ParseNode*		 pParseNodes[10];
	i32				 parseNodesCount;
	Token*			 pToken;
	ParseNodeHandler handler;
};

class AST
{
public:
	AST(const std::string& sourceCode, TokenParser tokenParser = nullptr);
	~AST();

	inline Expression* getRootExpression() const
	{
		return m_pRootExpression;
	}

	inline bool isValid() const
	{
		return m_isValid;
	}

private:
	bool parseLiteral(ParseNode* pNode);
	bool parseEpsilon(ParseNode* pNode);

private:
	bool parseExp(ParseNode* pNode);
	bool parseAddExp(ParseNode* pNode);

private:
	ParseNode* newNode();

private:
	std::vector<Token> m_tokens;
	i32				   m_tokenCursor;
	ParseNode*		   m_pRootExpNode;
	Expression*		   m_pRootExpression;
	bool			   m_isValid;
	ParseNode		   m_nodesHub[MAX_NODES];
	i32				   m_nodesHubCursor;
};

} // namespace ntt
