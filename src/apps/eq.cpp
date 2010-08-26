#include "terminterpreter.h"

#include <string>
#include <math.h>
#include <iostream>
#include <float.h>

using namespace std;
using namespace TermInterpreter;
int main(int argc, char** argv) 
{
	Context* c = new Context;
	c->addFunction("sqrt", new CFunction(1, &sqrt, "square root"));
	Driver d;
	d.setContext(c);

	string str = "";
	for (int i = 1; i < argc; i++) {
		string tmp(argv[i]);
		str = str + tmp;
	}
	d.parse(str);
	if (d.getResult() != DBL_MAX) cout << d.getResult() << endl;

	delete c;
	c = NULL;

	return 0;

}
