#ifndef CFUNCTION_H
#define CFUNCTION_H

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "expression.h"
#include "function.h"

namespace TermInterpreter
{

	union Func{
		double (*fptr0)();
		double (*fptr1)(double d1);
		double (*fptr2)(double d1, double d2);
		double (*fptr3)(double d1, double d2, double d3);
		double (*fptr4)(double d1, double d2, double d3, double d4);

		//Constructors
		Func(double(*fun)()) { fptr0 = fun; }
		Func(double(*fun)(double)) { fptr1 = fun; }
		Func(double(*fun)(double, double)) { fptr2 = fun; }
		Func(double(*fun)(double, double, double)) { fptr3 = fun; }
		Func(double(*fun)(double, double, double, double)) { fptr4 = fun; }
	};


	class Context;


	class CFunction : public Function
	{
	public:
		CFunction(int numParams, Func func);
		CFunction(int numParams, Func func, std::string descr);
		virtual ~CFunction();

		virtual double call(std::vector<Expression*>* args, const Context& globalContext) const;

		virtual string getDescription() const { return m_description; }
	private:

		Func m_func;

		std::string m_description;
};


} // namespace

#endif


