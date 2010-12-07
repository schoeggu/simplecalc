#ifdef WIN32
	static const char PATH_DELIM = '\\';
#endif

#ifdef __linux__
	static const char PATH_DELIM = '/';
#endif

#include <unistd.h>
#include <string>


std::string getHomeDirectory()
{
	std::string dir;
	char* env;
	#ifdef WIN32
		if (env = getenv("USERPROFILE")) dir = env;
		else if (env = getenv("HOMEDRIVE")) {
			dir = env;
			dir += getenv("HOMEPATH");
		}
	#endif

	#ifdef __linux__
		if (env = getenv("HOME")) dir = env;
	#endif
	return dir;
}

