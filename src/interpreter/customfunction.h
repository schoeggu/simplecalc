#ifndef CUSTOMFUNCTION_H
#define CUSTOMFUNCTION_H

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "expression.h"
#include "function.h"

namespace TermInterpreter
{

	class Context;


	class CustomFunction : public Function
	{
	public:
		CustomFunction(vector<Expression*>* parList, Expression* func);
		CustomFunction(Expression* param, Expression* func);
		virtual ~CustomFunction();

		virtual double call(vector<Expression*>* args, Context& globalContext) const;

		virtual vector<string> getParams() const;
		virtual string getDescription() const { return m_func->toString(); }
	private:

		Expression* m_func;
		vector<string> m_params;
};


} // namespace

#endif

