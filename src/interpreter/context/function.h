#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include "expression/expression.h"
#include "context.h"

namespace TermInterpreter
{

class Function
{
public:
    Function(int numParams = 0) : m_numParams(numParams) {}
	virtual ~Function() {}

	virtual double call(std::vector<Expression*>* args, const Context&) const = 0;

	virtual int getNumParams() { return m_numParams; }
	virtual std::vector<string> getParams() const;
	virtual string getDescription() const { return ""; }
protected:
    int m_numParams;
};

} // namespace

#endif
