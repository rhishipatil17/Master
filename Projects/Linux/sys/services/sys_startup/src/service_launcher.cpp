#include "service_launcher.h"
#include "abstracted_api.h"
#include "minIni.h"

#include <fstream>
#include <cstdio>
#include <unistd.h>

using namespace sys_startup;
using namespace abstracted_api;

service_launcher::service_launcher()
{}

void service_launcher::read_LaunchConfig()
{
    std::ifstream file(SERVICE_LIST);

    if(!file)
    {
        return;
    }

    std::string line;
    std::vector<service>::iterator it;
    while(std::getline(file, line))
    {
        if(!line.compare(SERVICE_LABEL))
        {
            std::string tFile = "temp";
            struct service tService;

            std::ofstream tempFile(tFile.c_str());
            while(line.compare(SERVICE_LABEL))
            {
                tempFile << line;
            }
            tempFile.close();

            //Todo_work: solve warning
            file.seekg(file.tellg() - line.length());

            ConfigReader::minIni minFile(tFile);
            std::string value;
            bool found_all = false;

            while(1)
            {
                if(!minFile.getKeyValue(SERVICE_NAME, value))
                    break;
                tService.name = value;

                if(!minFile.getKeyValue(SERVICE_ENABLED, value))
                    break;
                tService.enabled = value;

                if(!minFile.getKeyValue(SERVICE_DIRECTORY, value))
                    break;
                tService.directory = value;

                if(!minFile.getKeyValue(SERVICE_EXEC, value))
                    break;
                tService.exec = value;

                minFile.getKeyValue(SERVICE_ARGS, value);
                ConfigReader::minIni::getCSValues(value, tService.args);

                found_all = true;
                break;
            }

            remove(tFile.c_str());

            if(found_all)
            {
                service_list.push_back(tService);
            }
        }
    }
    file.close();
}

void service_launcher::launch_services()
{
    read_LaunchConfig();

    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        int ret = exec_service(*it);
    }
}

long int service_launcher::exec_service(struct service &s_service)
{
    if(!s_service.enabled.compare(ENABLED_TRUE))
    {
        //TODO_msg: print if enabled

        long int ret = vfork();

        if(ret != 0)
        {

        }
        else
        {

        }
    }
    else
    {
        return -1;
    }
}