#include "context.h"

#include "cfunction.h"

#include <iostream>
#include <vector>
using namespace std;

namespace TermInterpreter
{

	CFunction::CFunction(int numParams, Func func)
	: Function(numParams),  m_func(func), m_description("native C Function")
	{ }

	CFunction::CFunction(int numParams, Func func, std::string descr)
	: Function(numParams),  m_func(func), m_description(descr)
	{ }

	CFunction::~CFunction()
	{ }

	double CFunction::call(vector<Expression*>* args, Context& globalContext) const
	{
		if (args) {
			if (args->size() != (unsigned int)m_numParams) {cerr << "ERROR: #cfunction.cpp:22" << endl;return 0; }//TODO error
		} else {
			if (m_numParams != 0) {cerr << "ERROR: #cfunction.cpp:24" << endl;return 0; }//TODO error
		}

		switch(m_numParams)
		{
		case 0:
			return ((*m_func.fptr0)());
		case 1:
			return ((*m_func.fptr1)(args->at(0)->evaluate(globalContext)));
		case 2:
			return ((*m_func.fptr2)(args->at(0)->evaluate(globalContext),
								args->at(1)->evaluate(globalContext)));
		case 3:
			return ((*m_func.fptr3)(args->at(0)->evaluate(globalContext),
								args->at(1)->evaluate(globalContext),
								args->at(2)->evaluate(globalContext)));
		case 4:
			return ((*m_func.fptr4)(args->at(0)->evaluate(globalContext),
								args->at(1)->evaluate(globalContext),
								args->at(2)->evaluate(globalContext),
								args->at(3)->evaluate(globalContext)));
		default:
			//TODO throw exception
			cerr << "ERROR: #cfunction.cpp:47" << endl;
			return 0;
		}
	}
} // namespace


