#ifndef TERMINALEXPR
#define TERMINALEXPR

#include "expression.h"

namespace TermInterpreter
{

class Context;

class TerminalExpr : public Expression 
{
public:
	TerminalExpr(double value);
	virtual ~TerminalExpr(){}

	virtual double evaluate(Context&) const;
	virtual string toString() const;
private:
	double m_value;
};

} // namespace
#endif

