#include <unistd.h>
#include <string>

#ifdef WIN32
	static const char PATH_DELIM = '\\';
#endif

#if defined(__linux) || defined(__APPLE__)
	#include <sys/types.h>
	#include <pwd.h>
	static const char PATH_DELIM = '/';
#endif

std::string getHomeDirectory()
{
	std::string dir;
	char* home;

	#ifdef WIN32
		char* drive;
		home = getenv("USERPROFILE");
		if (home) dir = home;
		else {
			drive = getenv("HOMEDRIVE");
			home = getenv("HOMEPATH");
			if (drive && home) {
				dir = drive;
				dir += home;
			}
		}
	#endif

	#if defined(__linux) || defined(__APPLE__)
		home = getenv("HOME");
		if (home) dir = home;
		else {
			passwd* pwd = getpwuid(getuid());
			if (pwd) dir = pwd->pw_dir;
		}
	#endif
	return dir;
}

