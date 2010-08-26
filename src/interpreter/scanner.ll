%{                                            /* -*- C++ -*- */
#include <cstdlib>
#include <errno.h>
#include <limits.h>
#include <string>
#include "driver.h"
#include "parser.hpp"
%}

%option noyywrap nounput batch

digit		[0-9]
alpha		[a-zA-Z]

int			{digit}+
decimal		{int}?\.{int}
number		(\(-\))?({int}|{decimal})

word		({alpha}|_)({alpha}|{digit}|_)*

opplus		\+
opcomma		,
opminus		-
opmult		\*
opdiv		\/
klammauf	\(
klammzu		\)
gleich		\=
colon       :
semicolon   ;
hoch		\^
operator	{opplus}|{opminus}|{opmult}|{opdiv}|{klammauf}|{klammzu}|{gleich}|{opcomma}|{colon}|{semicolon}|{hoch}|\n

%{
#define YY_USER_ACTION  yylloc->columns (yyleng);
%}

%%

%{
	yylloc->step ();
%}

{number}		{
					/* ugly way to make string usable for atof() */
					char* pyytext = yytext;
					if (*pyytext == '(') {
						pyytext[2] = '-';
						pyytext += 2;
					}
					yylval->number = atof(pyytext);
					return yy::Parser::token::NUMBER;
				}
{operator}		{
					return *yytext;
				}
{word}			{
					yylval->str = new string(yytext);
					return yy::Parser::token::WORD;
				}

[ \t]+			{yylloc->step();}

%%

