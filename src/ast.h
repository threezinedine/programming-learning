#pragma once
#include "common.h"
#include "expression/expression.h"
#include "tokenizer.h"
#include <functional>

#define MAX_NODES 20

namespace ntt {

struct ParseNode;

typedef bool (*TokenParser)(const std::string& sourceCode, std::vector<Token>& tokens);
using ParseNodeHandler = std::function<Expression*(Ref<ParseNode> pNode)>;

struct ParseNode
{
	Ref<ParseNode>				pParentNode;
	std::vector<Ref<ParseNode>> pParseNodes;
	const Token*				pToken;
	ParseNodeHandler			handler;
};

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
	bool parseLiteral(Ref<ParseNode> pNode);
	bool parseLiteral_1(Ref<ParseNode> pNode);
	bool parseEpsilon(Ref<ParseNode> pNode);
	bool parseToken(Ref<ParseNode> pNode, TokenType expectedType);

private:
	bool parseExp(Ref<ParseNode> pNode);
	bool parseAddExp(Ref<ParseNode> pNode);
	bool parseLeftAddExp(Ref<ParseNode> pNode);

	bool parseRightAddExp_1(Ref<ParseNode> pNode);
	bool parseRightAddExp(Ref<ParseNode> pNode);

private:
	std::vector<Token> m_tokens;
	i32				   m_tokenCursor;
	Ref<ParseNode>	   m_pRootExpNode;
	Expression*		   m_pRootExpression;
	bool			   m_isValid;
};

} // namespace ntt
