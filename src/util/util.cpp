#include <stdio.h>
#include "util.h"

namespace Util {
	FILE* strFile(std::string str)
	{
		FILE* f;
		f = tmpfile();
		if (!f) { return NULL; }
		fwrite(str.c_str(), sizeof(char), str.size(), f);
		rewind(f);

		return f;
	}
} // namespace
