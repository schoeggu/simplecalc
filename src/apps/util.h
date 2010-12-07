#ifdef WIN32
	static const char PATH_DELIM = '\\';
#endif

#ifdef __linux__
	static const char PATH_DELIM = '/';
#endif

#include <unistd.h>
#include <string>
#include <iostream>
	using std::cout;
	using std::endl;


std::string getHomeDirectory()
{
	cout << "USERPROFILE: " << (getenv("USERPROFILE") ? getenv("USERPROFILE")  : "") << endl;
	cout << "HOMEDRIVE: " << (getenv("HOMEDRIVE") ? getenv("HOMEDRIVE") : "") << endl;
	cout << "HOMEPATH: " << (getenv("HOMEPATH") ? getenv("HOMEPATH") : "") << endl;
	cout << "HOME: " << (getenv("HOME") ? getenv("HOME") : "") << endl;
	std::string dir;
	char* env;
	#ifdef WIN32
		if (env = getenv("USERPROFILE")) dir = env;
		else if (env = getenv("HOMEDRIVE") {
			dir = env;
			dir += getenv("HOMEPATH");
		}
	#endif

	#ifdef __linux__
		if (env = getenv("HOME")) dir = env;
	#endif
	return dir;
}


