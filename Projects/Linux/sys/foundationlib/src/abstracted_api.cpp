#include <string.h>
#include <unistd.h>

#include <dirent.h>

#include "abstracted_api.h"

namespace abstracted_api
{
	std::string get_home_dir()
	{
		return std::getenv("HOME");
	}

	std::string getShareRoot()
	{
		return std::string(get_home_dir() + "/sys_share");
	}

	int set_working_dir(std::string directory)
	{
		return chdir(directory.c_str());
	}

	bool getFilesList(std::vector<std::string> &files, std::string mask, std::string path)
	{
		bool ret = 0;
		DIR *directory;
		struct dirent *entry;

		do
		{
			directory = opendir(path.c_str());
			if(directory != nullptr)
			{	
				while( (entry = readdir(directory)) != nullptr)
				{
					if( entry->d_type == DT_REG)
					{
						if(!mask.empty())
						{
							std::string type_reg(entry->d_name);
							if(type_reg.find(mask))
							{
								files.push_back(entry->d_name);
							}
						}
						else
						{
							files.push_back(entry->d_name);
						}
					}
				}
				ret = 1;
			}

		}
		while(0);
		return ret;
	}

	bool getDirList(std::vector<std::string> dir, std::string mask, std::string path)
	{
		bool ret = 0;
		DIR *directory;
		struct dirent *entry;

		do
		{
			directory = opendir(path.c_str());
			if(directory != nullptr)
			{	
				while( (entry = readdir(directory)) != nullptr)
				{
					if( entry->d_type == DT_DIR)
					{
						if(!mask.empty())
						{
							std::string type_dir(entry->d_name);
							if(type_dir.find(mask))
							{
								dir.push_back(entry->d_name);
							}
						}
						else
						{
							dir.push_back(entry->d_name);
						}
					}
				}
				ret = 1;
			}
		}
		while(0);
		return ret;
	}

	void getCSValues(const std::string data, std::vector<std::string> &values)
	{
		std::string temp_str;
		for(std::string::const_iterator it=data.begin(); it!=data.end(); it++)
		{
			if(*it != COMMA)
			{
				temp_str.push_back(*it);
			}
			else
			{
				if(!temp_str.empty())
				{
					values.push_back(temp_str);
					temp_str.clear();
				}
			}
		}
		if(!temp_str.empty())
		{
			values.push_back(temp_str);
			temp_str.clear();
		}
		//TODO_work: put nullptr at the end of the values vector
	}
}