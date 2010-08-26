#include "context.h"

#include "customfunction.h"
#include "variableexpr.h"

#include <iostream>
#include <vector>
using namespace std;

namespace TermInterpreter
{

	CustomFunction::CustomFunction(vector<Expression*>* parList, Expression* func)
	: m_func(func)
	{

		if (parList) {
			m_numParams = parList->size();
			vector<Expression*>::iterator iter;
			for(iter = parList->begin(); iter != parList->end(); ++iter) {
				VariableExpr*	expr = dynamic_cast<VariableExpr*>(*iter);
				if (expr) {
					m_params.push_back(expr->getName());
					delete expr;
				} else {
					cerr << "ERROR: #customfunction.cpp:26" << endl;
					//TODO trhow exception
				}
			}
		} else {
			m_numParams = 0;
		}
		delete parList;
	}

	CustomFunction::CustomFunction(Expression* param, Expression* func)
	: m_func(func)
	{
		m_numParams = 1;
		VariableExpr* expr = dynamic_cast<VariableExpr*>(param);
		if (expr) {
			m_params.push_back(expr->getName());
			delete expr;
		} else {
					cerr << "ERROR: #customfunction.cpp:44" << endl;
			//TODO throw exception
		}
	}

	CustomFunction::~CustomFunction()
	{
		delete m_func;
	}

	double CustomFunction::call(vector<Expression*>* args, Context& globalContext) const
	{
		Context localContext(&globalContext, true);
		vector<string>::const_iterator name;
		vector<Expression*>::iterator arg;
		if (args) {
			if (args->size() != (unsigned int)m_numParams) {cerr << "ERROR: #customfunction.cpp:60" << endl; return 0;}//TODO error
			name = m_params.begin();
			arg = args->begin();
			while(name != m_params.end()) {
				localContext.setVar(*name, *arg);
				++name;
				++arg;
			}
		} else {
			if (m_numParams != 0) {
					cerr << "ERROR: #customfunction.cpp:70" << endl;
				//TODO error
			}
		}

		return m_func->evaluate(localContext);

	}


	vector<string> CustomFunction::getParams() const
	{
        return m_params;
	}

} // namespace

