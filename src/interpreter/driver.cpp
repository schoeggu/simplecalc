#include "expression.h"
#include "context.h"
#include "driver.h"
#include "parser.hpp"
//#include "scanner.hpp"

#include "util.h"

#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

extern int yydebug;
extern FILE* yyin;

namespace TermInterpreter
{
	Driver::Driver(bool debug) : m_debug(debug), m_globalContext(NULL), m_result(NULL)
	{
		//TODO init context, setup functions...
	}


	Driver::~Driver()
	{
		delete m_result;
		m_globalContext = NULL;
	//	yylex_destroy();
		//TODO delete funcitons/vars? eher weniger?
		//
	}

	void Driver::parse(string& term)
	{
		scanBegin(term);
		yy::Parser parser(*this);
		if (m_debug) { parser.set_debug_level(1);}
		parser.parse();
		scanEnd();
	}

	void Driver::setContext(Context* cont)
	{
		m_globalContext = cont;
	}

	void Driver::setVar(const string name, Expression* expr, bool ref)
	{
		//cout << '\'' << name << '\'' << " is set to: '";
		if (ref) {
			m_globalContext->setVar(name, expr);
		//	cout << expr->toString() << "' (" << expr->evaluate(*m_globalContext) << ")" << endl;
		} else {
			m_globalContext->setVar(name, expr->evaluate(*m_globalContext));
		//	cout << m_globalContext->lookupVar(name)->evaluate(*m_globalContext) << "'" << endl;
		}
	}

	void Driver::addFunction(string name, Function* func)
	{
		if (func) {
			m_globalContext->addFunction(name, func);
			cout << "added function '" << name << "'\n";
		}
	}

	void Driver::command(string command)
	{ //TODO mit callbacks libsigc oder observer oder ähnlicheshey

        if (command == "listfunctions") {
            const map<string, Function*>  * const vars = m_globalContext->getFuncs();

            map<string, Function*>::const_iterator iter;
            for (iter = vars->begin(); iter != vars->end(); ++iter) {

                vector<string> params = iter->second->getParams();

                cout << setw(12) << iter->first << "(";

                int numParams = iter->second->getNumParams(); //TODO schöner machen zwar in einen stringbuffer " name[max namlen+] ( parlist[maxparlistlen] ) : descr[egal]"
				for (int i = 0; i < numParams;) {
                    if (params.empty()) {
                        cout << setw(5);
                        cout << "par" << i+1;
                    } else {
                        cout << setw(6);
                        cout << params.at(i);
                    }
                    cout  << ((++i < numParams) ? ", " : "");
                }

                cout << ")" << setw(6 * (4 - numParams)) << "" << iter->second->getDescription() << endl;

            }
        } else if (command == "listvariables") {
            const map<string, Expression*>  * const vars = m_globalContext->getVars();
            map<string, Expression*>::const_iterator iter;
            for (iter = vars->begin(); iter != vars->end(); ++iter) {
                cout << setw(12) << iter->first << ":" << setw(12) << iter->second->evaluate(*m_globalContext) << endl;
            }
        }
	}

	void Driver::result(Expression* res)
	{
		m_globalContext->setResult(res);

	}

	void Driver::error(const yy::location& l, const string& m)
	{
			std::cerr << l << ':' << m << std::endl;
	}

	void Driver::error(const string& m)
	{
			std::cerr << m << std::endl;
	}


	void Driver::scanBegin(string& term)
	{
		if (!(yyin = Util::strFile(term))) error (string ("cannot open "));
	}

	void Driver::scanEnd()
	{
		fclose (yyin);
	}


} // namespace


