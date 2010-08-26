#include <math.h>
#include "context.h"

#include "basicexpr.h"

namespace TermInterpreter
{

BasicExpr::BasicExpr(Expression* op1, Expression* op2, OpType t)
: m_op1(op1), m_op2(op2), m_type(t)
{
	switch (m_type)
	{
		case ADD:
			m_function = (&add);	
			m_op = '+';
			break;
		case SUBTRACT:
			m_function = (&subtract);
			m_op = '-';
			break;
		case MULTIPLY:
			m_function = (&multiply);
			m_op = '*';
			break;
		case DIVIDE:
			m_function = (&divide);
			m_op = '/';
			break;
		case POWER:
			m_function = (&power);
			m_op = '^';
			break;
		default:
			m_op = '\0';
			m_function = NULL;
	}
}

BasicExpr::~BasicExpr()
{
	delete m_op1;
	delete m_op2;
}

double BasicExpr::evaluate(Context& cont) const
{

	return (*m_function)(m_op1->evaluate(cont), m_op2->evaluate(cont));
}

string BasicExpr::toString() const
{
	string str;
	str = m_op1->toString() + ' ' + m_op + ' ' + m_op2->toString();
	return str;
}

double BasicExpr::add(double op1, double op2) { return op1 + op2; }
double BasicExpr::subtract(double op1, double op2) { return op1 - op2; }
double BasicExpr::multiply(double op1, double op2) { return op1 * op2; }
double BasicExpr::divide(double op1, double op2) { return op1 / op2; }
double BasicExpr::power(double op1, double op2) { return pow(op1, op2); }

} // namespace

