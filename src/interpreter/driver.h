#ifndef DRIVER_H
#define DRIVER_H


#include <string>
#include <float.h>
using std::string;

namespace yy
{
	class Parser;
	class location;
}


namespace TermInterpreter
{
	class Driver;
	class Context;
}

#include "expression.h"
#include "function.h"

using namespace TermInterpreter;


namespace TermInterpreter
{
	class Driver
	{
	public:
		Driver(bool debug = false);
		virtual ~Driver();

		void parse(string&);

		void setVar(const string, Expression*, bool ref = true);
		void setContext(Context*);


		void addFunction(string, Function*);

		void command(string);
	//	bool hookupCommand(string command, void *(), bool override = false); //todo libsig oder so
	//	bool removeCommand(string command);

		void result(Expression*);
		Expression* getExpression() { return m_result; }
		double getResult() { return m_result ? m_result->evaluate(*m_globalContext) : DBL_MAX; }

		void error(const yy::location&, const string&);
		void error(const string&);


	private:
		void scanBegin(string&);
		void scanEnd();

		bool m_debug;
		Context* m_globalContext;
		Expression* m_result; //TODO history
	};
}

#endif
