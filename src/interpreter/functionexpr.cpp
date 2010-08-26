#include "context.h"

#include "functionexpr.h"
#include "terminalexpr.h"
#include "expression.h"

#include <iostream>
#include <vector>
using namespace std;

namespace TermInterpreter
{

	FunctionExpr::FunctionExpr(string name, vector<Expression*>* parList)
	: m_name(name),  m_params(parList)
	{ 
		m_numParams = (m_params ? parList->size() : 0);
	}

	FunctionExpr::FunctionExpr(string name, Expression* param) 
	: m_name(name)
	{
		m_params = new vector<Expression*>();
		m_params->push_back(param);
		m_numParams = 1;
	}
	
	FunctionExpr::~FunctionExpr()
	{
		if(m_params) {
			vector<Expression*>::iterator iter;
			for(iter = m_params->begin();iter != m_params->end();++iter) {
				Expression* e = *iter;
				Context c;
//				TerminalExpr* t = dynamic_cast<TerminalExpr*>(*iter);
				delete e;
//				delete *iter;
			}
			m_params->clear();
			delete m_params;
		}
	}
	
	double FunctionExpr::evaluate(Context& cont) const
	{
			const Function* const func = cont.lookupFunction(m_name);
			return func->call(m_params, cont);
	}
	
	string FunctionExpr::toString() const
	{
		string str = m_name + "( ";
		if (m_params) {
			vector<Expression*>::iterator iter;
			int i = 0;
			for(iter = m_params->begin();iter != m_params->end(); ++iter) {
				(*iter)->toString(); 
				str += (*iter)->toString() + (m_numParams - i != 1 ? ", " : " ");
				i++;
			}
		}
		str += ')';
		return str;
	}

} // namespace
