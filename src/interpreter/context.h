#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <map>
#include <math.h> //TP
using std::string;
using std::map;

#include "function.h"

namespace TermInterpreter
{


class Function;
class Expression;

class Context
{
public:

	Context(bool dontdelete = false);
	Context(const Context* parent, bool dontdelete = false);
	virtual ~Context();

	void setVar(string, Expression*);
	void setVar(string, double);
	const Expression* lookupVar(const string&) const;
	const map<string, Expression*> * const getVars() const { return &m_Vars; }

	void setDontDelete(bool b = true) { m_bDontDelete = b; }

    void setResult(Expression* res);
    double getResult() const;
    const Expression* getResultExpression() const;
    bool hasResultChanged();

	bool addFunction(string, Function*);
	const Function* lookupFunction(string) const;
	const map<string, Function*> * const getFuncs() const { return &m_Functions; }
private:
	map<string, Function*> m_Functions;
	map<string, Expression*> m_Vars;
	const Context* m_parent;
	bool m_bDontDelete;
	Expression* m_result;
	Expression* m_lastResult;
	bool m_bResultChanged;
};

} // namespace

#endif
