#include "terminterpreter.h"

#include <string>
#include <math.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <tclap/SwitchArg.h>


using namespace std;
using namespace TermInterpreter;

double myrand() {
	return rand();
}

double testfun(double t1, double t2, double t3) {
	return t1*t2/t3;
}

void doCalculations(Driver* d, Context* c, istream& stream);
void initContext(Context* c);
void printHelp(char* prname);

int main(int argc, char** argv)
{
	bool debug = false;
	bool init = false;
	bool interactive = true;
	string filename;
	string initfile;


    try {

		TCLAP::CmdLine cmd("Simplecalc", ' ', "0.4.3");

		TCLAP::ValueArg<string> initArg("z", "initialize", "initializes with [file]", false, "", "file");
		TCLAP::ValueArg<string> scriptArg("s", "script", "Process [file]", false, "", "file");
		TCLAP::SwitchArg interactiveSwitch("i", "interactive", "interactive mode", false);
		TCLAP::SwitchArg debugSwitch("d", "debug", "enable debug output", false);

	    cmd.add(initArg);
	    cmd.add(scriptArg);
	    cmd.add(interactiveSwitch);
		cmd.add(debugSwitch);

	    cmd.parse(argc, argv);

		interactive = interactiveSwitch.isSet();
		debug = debugSwitch.isSet();
		init = initArg.isSet();
		if (init) initfile = initArg.getValue();
		if (scriptArg.isSet()) { interactive = false; filename = scriptArg.getValue(); }

    } catch (TCLAP::ArgException &e)  // catch any exceptions
        { cerr << "error: " << e.error() << " for arg " << e.argId() << "\n"; }


	Context* c = new Context;
	initContext(c);

	Driver d(debug);
	d.setContext(c);

	if (init) {
		ifstream file(initfile.c_str(), ifstream::in);
		doCalculations(&d, c, file);
		file.close();
	}

	if (!interactive) {
		ifstream file(filename.c_str(), ifstream::in);
		doCalculations(&d, c, file);
		file.close();
	} else {
		doCalculations(&d, c, cin);
	}

	delete c;
	c = NULL;

	return 0;
}

void doCalculations(Driver* d, Context* c, istream& stream)
{
	string line;
	char* pc = new char[99];
	stream.getline(pc, 99);
	line = pc;
	while (stream.good() && line != "q" && line != "quit") {
		d->parse(line);
		if (c->hasResultChanged() && c->getResult() != DBL_MAX) {
			cout << c->getResultExpression()->toString() << " = " << c->getResult() << endl;
		}
		stream.getline(pc, 99);

		size_t compos =  line.find("#");
		line = line.substr(0, (compos == string::npos) ? 100 : compos);

		line = pc;
	}

	delete [] pc;
	pc = NULL;
}


void initContext(Context* c)
{
	srand ( time(NULL) );
	c->addFunction("rand", new CFunction(0, &myrand, "random number between 0 and RAND_MAX"));

	c->addFunction("sqrt", new CFunction(1, &sqrt, "square root"));
	c->addFunction("sin", new CFunction(1, &sin));
	c->addFunction("cos", new CFunction(1, &cos));
	c->addFunction("tan", new CFunction(1, &tan));

	c->addFunction("max", new CFunction(2, &fmax));
	c->addFunction("min", new CFunction(2, &fmin));

	c->addFunction("X", new CFunction(3, &testfun));

	c->setVar("PI", new TerminalExpr(M_PI));
	c->setVar("RAND_MAX", new TerminalExpr(RAND_MAX));
	c->setVar("RES", new TerminalExpr(0));
}

void printHelp(char* prgName)
{
	cout << "usage: " << prgName << " [-i] [-I file] [-f file] [-d] [-h]\n"
		    "\n"
		    "if no file is specified, the programm will enter its interactive mode.\n"
		    "\n"
		    "[-i]              interactive mode\n"
		    "[-I file]         initialize with [file]\n"
  		    "[-f file]         read commands from [file]\n"
			"[-d]              enable debug output\n"
			"[-h]              print this help\n";

}
