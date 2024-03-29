#include <string.h>
#include <unistd.h>

#include "abstracted_api.h"

namespace abstracted_api
{
	std::string get_home_dir()
	{
		return std::getenv("HOME");
	}

	std::string getFlashRoot()
	{
		return std::string(get_home_dir() + "/sys_startup/flash");
	}

	std::string getSysShareRoot()
	{
		return std::string(get_home_dir() + "/sys_share");
	}

	int set_working_dir(const char *directory)
	{
		return chdir(directory);
	}
}