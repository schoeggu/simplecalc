#include "context.h"

#include "variableexpr.h"

namespace TermInterpreter
{

VariableExpr::VariableExpr(string name)
: m_name(name) {}

double VariableExpr::evaluate(const Context& cont) const
{
	return cont.lookupVar(m_name)->evaluate(cont);
}

string VariableExpr::toString() const
{
	return m_name;
}

} // namespace
