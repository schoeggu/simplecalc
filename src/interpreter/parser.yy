%skeleton "lalr1.cc"
%debug



%define "parser_class_name" "Parser"


%code requires {
#include <string>
#include <vector>
#include "terminterpreter.h"
#include "customfunction.h"

using namespace TermInterpreter;

class function {
public:
	function(string name, std::vector<Expression*>* params) : name(name), parList(params) {}
	function(string name, Expression* param) : name(name) { parList = new vector<Expression*>(); parList->push_back(param);}
	virtual ~function() { parList = NULL; }
	string name;
	std::vector<Expression*>* parList;
};


}

%code provides {

#define YY_DECL \
	int yylex (yy::Parser::semantic_type* yylval, yy::location* yylloc, TermInterpreter::Driver& driver)
YY_DECL;
}

%parse-param { Driver& driver }
%lex-param { Driver& driver }

%locations
%initial-action
{
}

%union
{
	double number;
	string* str;
	Expression* expr;
	std::vector<Expression*>* parList;
	function* func;
}

%token <str>WORD
%token <number>NUMBER
%token <number>EXIT

%destructor { delete $$; } WORD function //why doesn't this work? if it worked the deletes below woudn't be nescesary

%type <expr> expr
%type <parList> paramList
%type <parList> paramListPart
%type <expr> parenthesisPart
%type <expr> parenthesis
%type <func> function

%start statement;
%left '+' '-';
%left '*' '/';
%left '';


%%
statement:
		assignment	 						{;}
		| command                           {;}
		| expr 								{driver.result($1);}

assignment:
		WORD '=' expr 						{driver.setVar(*$1, $3); delete $1;}
		| WORD ':=' expr 					{driver.setVar(*$1, $3, false); delete $1;}
		| function '=' expr					{driver.addFunction($1->name, new CustomFunction($1->parList, $3)); delete $1;}

parenthesisPart:
	   '(' expr								{$$ = $2;}

parenthesis:
		parenthesisPart ')'					{$$ = $1;}

paramListPart:
		parenthesisPart	',' expr			{$$ = new std::vector<Expression*>(); $$->push_back($1); $$->push_back($3);}
		| paramListPart ',' expr			{$$ = $1; $$->push_back($3);}

paramList:
		'(' ')'								{$$ = NULL;}
		| paramListPart ')'					{$$ = $1;}

function:
		WORD paramList						{$$ = new function(*$1, $2); delete $1;}
		| WORD parenthesis					{$$ = new function(*$1, $2); delete $1;}

command:
        ':' WORD                            {driver.command(*$2); delete $2;} //TODO command mit arguments und so

//commandPart:
//        ':'
//        | commandPart WORD
//        | commandPart NUMBER
//        | commandPart '-' WORD

expr:
		expr '+' expr						{$$ = new BasicExpr($1, $3, ADD);}
		| expr '-' expr						{$$ = new BasicExpr($1, $3, SUBTRACT);}
		| expr '*' expr						{$$ = new BasicExpr($1, $3, MULTIPLY);}
		| expr '/' expr						{$$ = new BasicExpr($1, $3, DIVIDE);}
		| expr '' expr						{$$ = new BasicExpr($1, $3, POWER);}
		| parenthesis 						{$$ = new ParenthesisExpr($1);}
		| function							{$$ = new FunctionExpr($1->name, $1->parList); delete $1;}
		| WORD								{$$ = new VariableExpr(*$1); delete $1;}
		| NUMBER							{$$ = new TerminalExpr($1);}
		| '-' expr							{$$ = new ParenthesisExpr($2, true);}

%%

void yy::Parser::error (const yy::Parser::location_type& l, const string& m)
{
	driver.error (l, m);
}

