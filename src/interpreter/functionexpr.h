#ifndef FUNCTIONEXPR_H
#define FUNCTIONEXPR_H 

#include <string>
#include <vector>
using std::string;
using std::vector;

#include "expression.h"
#include "function.h"

namespace TermInterpreter
{

	class Context;
	
	
	class FunctionExpr : public Expression 
	{
	public: 
		FunctionExpr(string name, vector<Expression*>* parList);
		FunctionExpr(string name, Expression* param);
		virtual ~FunctionExpr();
	
		virtual double evaluate(Context&) const;
		virtual string toString() const;
	private:
	
		string m_name;
		int m_numParams;
		vector<Expression*>* m_params;
};


} // namespace

#endif 
