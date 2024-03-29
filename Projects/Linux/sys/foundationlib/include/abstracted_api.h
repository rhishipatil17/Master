#ifndef ABSTRACTEDAPI
#define ABSTRACTEDAPI

#include <string>

namespace abstracted_api
{
	std::string get_home_dir();
	std::string getFlashRoot();
	std::string getSysShareRoot();
	int set_working_dir(const char *directory);
}

#endif