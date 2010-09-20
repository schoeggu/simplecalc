#include "expression/expression.h"
#include "context/context.h"
#include "context/lookupexception.h"
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
		//yylex_destroy();
		//TODO delete funcitons/vars? eher weniger?
	}

	void Driver::parse(string& term)
	{
	    if (term.empty()) return;
	    m_term = term;
		scanBegin(m_term);
		yy::Parser parser(*this);
		if (m_debug) { parser.set_debug_level(1);}
		try {
            parser.parse();
		} catch (LookupException e) {
            error(e.getExceptionText() + ": " + e.getObject());
		}
		scanEnd();
	}

	void Driver::setContext(Context* cont)
	{
		m_globalContext = cont;
	}

	void Driver::setVar(const string name, Expression* expr, bool ref)
	{
		if (ref) {
			m_globalContext->setVar(name, expr);
		} else {
			m_globalContext->setVar(name, expr->evaluate(*m_globalContext));
		}
	}

	void Driver::addFunction(string name, Function* func)
	{
		if (func) {
			m_globalContext->addFunction(name, func);
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
			std::cerr << "Error: " << l << ' ' << m << std::endl;
            std::cerr << m_term << std::endl;
            int collumn = l.begin.column;
            for (int i = 1; i < collumn; i++) std::cerr << ' ';
            std::cerr << '^' << std::endl;
	}

	void Driver::error(const string& m)
	{
			std::cerr << "Error: " << m << std::endl;
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


