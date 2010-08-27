#include "expression/expression.h"
#include "expression/terminalexpr.h"
#include "context.h"
#include "function.h"
#include "cfunction.h"
#include <iostream>
#include <float.h>

namespace TermInterpreter
{
	double dummy() { return 0; }

	Context::Context(bool dontdelete) : m_parent(NULL), m_bDontDelete(dontdelete), m_result(new TerminalExpr(0)), m_lastResult(new TerminalExpr(0)), m_bResultChanged(false) {}
	Context::Context(const Context* parent, bool dontdelete) : m_parent(parent), m_bDontDelete(dontdelete), m_result(NULL), m_lastResult(NULL), m_bResultChanged(false) {}

	Context::~Context()
	{
		if (!m_bDontDelete) {
			map<string, Expression*>::iterator iter;
			for (iter = m_Vars.begin(); iter != m_Vars.end();)
			{
//				std::cout << iter->second << std::endl;
				delete iter->second;
				m_Vars.erase(iter++);
			}
			map<string, Function*>::iterator iter2;
			for (iter2 = m_Functions.begin(); iter2 != m_Functions.end();)
			{
				delete iter2->second;
				m_Functions.erase(iter2++);
			}
		}

		m_parent = NULL;
	}

	void Context::setVar(string name, Expression* expr)
	{
		map<string, Expression*>::iterator iter = m_Vars.find(name);
		if (iter != m_Vars.end()) delete iter->second;
		m_Vars[name] = expr;
	}

	void Context::setVar(string name, double val)
	{
		map<string, Expression*>::iterator iter = m_Vars.find(name);
		if (iter != m_Vars.end()) delete iter->second;
		m_Vars[name] = new TerminalExpr(val);
	}

	const Expression* Context::lookupVar(const string& name) const
	{
		map<string, Expression*>::const_iterator iter = m_Vars.find(name);
		if (iter != m_Vars.end()) return iter->second;
		if (m_parent) {
			return m_parent->lookupVar(name);
		} else {
				std::cerr << "ERROR: #context.cpp:53" << std::endl;
			return NULL; //TODO throw exception
		}
	}

	bool Context::addFunction(string name, Function* ptr)
	{
		map<string, Function*>::iterator iter = m_Functions.find(name);
		if (iter != m_Functions.end()) delete iter->second;
		return m_Functions.insert(std::make_pair(name, ptr)).second;
	}

	const Function* Context::lookupFunction(string name) const
	{
		map<string, Function*>::const_iterator iter = m_Functions.find(name);
		if (iter != m_Functions.end()) return iter->second;
		if (m_parent) {
			return m_parent->lookupFunction(name);
		} else {
			Function* f = new CFunction(0, &dummy);
			std::cerr << "ERROR: #context.cpp:73" << std::endl;
			return f; //TODO throw exception
		}
	}

	void Context::setResult(Expression* res)
	{
        delete m_lastResult;
        m_lastResult = m_result;
        m_result = res;
        setVar("RES", m_lastResult->evaluate(*this));
        m_bResultChanged = true;
	}

    double Context::getResult() const
    {
        return m_result ? m_result->evaluate(*this) : DBL_MAX;
    }

    const Expression* Context::getResultExpression() const
    {
        return m_result;
    }

    bool Context::hasResultChanged()
    {
        bool tmp = m_bResultChanged;
        m_bResultChanged = false;
        return tmp;
    }

} // TermInterpreter
