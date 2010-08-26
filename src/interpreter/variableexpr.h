#ifndef VARIABLEEXPR_H
#define VARIABLEEXPR_H

#include <string>
using std::string;

#include "expression.h"


namespace TermInterpreter
{

class Context;


class VariableExpr : public Expression
{
public:
	VariableExpr(string name);
	virtual ~VariableExpr(){}

	virtual double evaluate(const Context&) const;
	virtual string toString() const;

	string getName() { return m_name; }
private:

	string m_name;

};

} // namespace
#endif
