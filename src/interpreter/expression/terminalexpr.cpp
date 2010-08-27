#include "context.h"
#include "terminalexpr.h"

#include <sstream>
#include <iostream>

namespace TermInterpreter
{

TerminalExpr::TerminalExpr(double value)
: m_value(value) {}

double TerminalExpr::evaluate(const Context& cont) const
{
	return m_value;
}

string TerminalExpr::toString() const
{
	char c[20];
	std::stringstream ss;
	ss.precision(5);
	ss << m_value;
	ss >> c;

	return string(c);
}

} // namespace
