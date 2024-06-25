#ifndef ABSTRACTEDAPI
#define ABSTRACTEDAPI

#include <string>
#include <vector>

#define COMMA ','

namespace abstracted_api
{
	std::string get_home_dir();
	std::string getFlashRoot();
	std::string getSysShareRoot();
	int set_working_dir(std::string);

	bool getFilesList(std::vector<std::string> files, std::string mask, std::string path = ".");
	bool getDirList(std::vector<std::string> dirs, std::string mask, std::string path = ".");
	void getCSValues(const std::string data, std::vector<std::string> &values);
    void getCSValues(const std::string data, std::vector<char[20]> &values);
}

#endif