
#include "context/context.h"
#include "parenthesisexpr.h"

namespace TermInterpreter
{

	ParenthesisExpr::ParenthesisExpr(Expression* par, bool neg)
	: m_par(par), m_negative(neg) {}

	ParenthesisExpr::~ParenthesisExpr()
	{
		delete m_par;
	}

	double ParenthesisExpr::evaluate(const Context& cont) const
	{
		return m_par->evaluate(cont) * (m_negative ? -1 : 1);
	}

	string ParenthesisExpr::toString() const
	{
		string str;
	   	str += m_negative ? "-" : "";
		str += "( ";
		str += m_par->toString();
		str += " )";

		return str;
	}

} // namespace

