#ifndef PARENTHESISEXPR
#define PARENTHESISEXPR

#include "expression.h"

namespace TermInterpreter
{

	class Context;

	class ParenthesisExpr : public Expression
	{
	public:
		ParenthesisExpr(Expression*, bool = false);
		virtual ~ParenthesisExpr();

		virtual double evaluate(const Context&) const;
		virtual string toString() const;
	private:
		Expression* m_par;
		bool m_negative;
	};

} // namespace
#endif

