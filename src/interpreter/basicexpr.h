#ifndef BASICEXPR_H
#define BASICEXPR_H

#include "expression.h"

namespace TermInterpreter 
{

class Context;

enum OpType {
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	POWER
};

class BasicExpr : public Expression 
{
public: 
	BasicExpr(Expression*, Expression*, OpType t);
	virtual ~BasicExpr();

	virtual double evaluate(Context&) const;
	virtual string toString() const;
private:
	static double add(double op1, double op2);
	static double subtract(double op1, double op2);
	static double multiply(double op1, double op2);
	static double divide(double op1, double op2);
	static double power(double op1, double op2);

	Expression* m_op1;
	Expression* m_op2;
	OpType m_type;
	char m_op; /* just for printings sake */
	double (*m_function)(double, double);
}; 

} // namespace

#endif 
