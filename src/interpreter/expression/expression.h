#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
using std::string;

namespace TermInterpreter
{

class Context;
class Expression
{
public:
	Expression(){}
	virtual ~Expression(){}

	virtual double evaluate(const Context&) const = 0;

	virtual string toString() const = 0;

};

} // namespace

#endif
