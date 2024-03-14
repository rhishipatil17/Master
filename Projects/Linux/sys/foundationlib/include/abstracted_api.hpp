#ifndef ABSTRACTEDAPI
#define ABSTRACTEDAPI

namespace abstracted_api
{
	std::string get_home_dir();
	std::string getFlashRoot();
	int set_working_dir(const char *directory);
}

#endif