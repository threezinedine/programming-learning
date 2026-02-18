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

StatementList: Statement RemainingStatements
			 | ε
			 ;

RemainingStatements: Statement RemainingStatements
				 | ε
				 ;

Statement: VariableDeclaration
		 | AssignmentStatement
		 | FunctionCallStatement
		 ;

VariableDeclaration: let Identifier;

AssignmentStatement: Identifier = Exp;

FunctionCallStatement: Identifier ( ExpList );

ExpList: Exp , ExpList
	   | Exp
	   | ε
	   ;

Exp: CompareExp;

CompareExp: CompareExpLeft CompareExpRight;

CompareExpRight: < CompareExpLeft
			   | > CompareExpLeft
			   | == CompareExpLeft
			   | != CompareExpLeft
			   | <= CompareExpLeft
			   | >= CompareExpLeft
			   | ε
			   ;

CompareExpLeft: LeftAddExp RightAddExp;

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
		  | Identifier
		  ;

Literal: Integer
	   | Float
	   | String
	   | Boolean
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
	Ref<Expression> parseStatementList();
	bool			parseRemainingStatements(Ref<StatementListExpression>& statements);
	Ref<Expression> parseStatement();
	Ref<Expression> parseVariableDeclaration();
	Ref<Expression> parseAssignmentStatement();
	Ref<Expression> parseFunctionCallStatement();
	bool			parseExpList(std::vector<Ref<Expression>>& arguments);
	Ref<Expression> parsePrimaryExp();
	Ref<Expression> parseLiteral();
	Ref<Expression> parseExpBlock();
	Ref<Expression> parseEpsilon();
	Token*			parseToken(TokenType expectedType);

private:
	Ref<Expression> parseExp();
	Ref<Expression> parseCompareExp();
	Ref<Expression> parseCompareExpLeft();
	bool			parseCompareExpRight(Ref<OperatorExpression>& pExp);
	Ref<Expression> parseLeftAddExp();
	bool			parseRightAddExp(Ref<OperatorExpression>& pAddExp);

	Ref<Expression> parseLeftMulExp();
	bool			parseRightMulExp(Ref<OperatorExpression>& pMulExp);

private:
	Token* getNextTokenWithType(TokenType expectedType);
	Token* getNextToken();

private:
	std::vector<Token> m_tokens;
	i32				   m_tokenCursor;
	Ref<Expression>	   m_pRootExpression;
	bool			   m_isValid;
};

} // namespace ntt
