#include "abstracted_api.hpp"

std::string get_home_dir()
{
	return std::getenv("Home");
}

std::string getFlashRoot()
{
	return std::string(get_home_dir() + "/flash");
}

int set_working_dir(const char *directory)
{
	return chdir(directory);
}