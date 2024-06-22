#include "service_launcher.h"
#include "abstracted_api.h"
#include "minIni.h"

#include <fstream>
#include <cstdio>
#include <unistd.h>

using namespace sys_startup;
using namespace abstracted_api;

service_launcher::service_launcher()
{
    read_SecurityServiceConfig();
    read_LaunchConfig();
}

void service_launcher::read_SecurityServiceConfig()
{
    std::ifstream file(SERVICE_SECURITY);
    if(!file)
    {
        return;
    }
    file.close();
    extract_LaunchConfig(SERVICE_SECURITY, service_security);
    
}

void service_launcher::read_LaunchConfig()
{
    std::ifstream file(SERVICE_LIST);
    if(!file)
    {
        return;
    }

    std::string tFileName = "temp";
    std::ofstream tFile(tFileName.c_str());
    std::string line;
    bool service_found = false;

    while(std::getline(file, line))
    {
        if(line.compare(SERVICE_LABEL))
        {
           if(service_found)
           {
                tFile << line;
           }
        }
        else
        {
            if(service_found)
            {
                struct service tService;
                clear_Service(tService);
                if(!extract_LaunchConfig(tFileName, tService))
                {
                    service_list.push_back(tService);
                }
            }
            std::ofstream clearFile(tFileName.c_str(), std::ios::trunc);
            clearFile.close();
        }
    }
    if(service_found)                                   //last service in the file will not have subsequent SERVICE_LABEL
    {
        struct service tService;
        clear_Service(tService);
        if(!extract_LaunchConfig(tFileName, tService))
        {
            service_list.push_back(tService);
        }
    }
    tFile.close();
    return;
}

int service_launcher::extract_LaunchConfig(std::string FileName, struct service &service)
{
    ConfigReader::minIni minFile(FileName);
    std::string value;

    if(!minFile.getKeyValue(SERVICE_NAME, value))
        return -1;
    service.name = value;

    if(!minFile.getKeyValue(SERVICE_ENABLED, value))
        return -1;
    service.enabled = value;

    if(!minFile.getKeyValue(SERVICE_DIRECTORY, value))
        return -1;
    service.directory = value;

    if(!minFile.getKeyValue(SERVICE_EXEC, value))
        return -1;
    service.exec = value;

    if(minFile.getKeyValue(SERVICE_ARGS, value))
    {
        ConfigReader::minIni::getCSValues(value, service.args);
        service.args.push_back(NULL);
    }
    return 0;
}

void service_launcher::clear_Service(struct service &service)
{
    service.name.clear();
    service.enabled.clear();
    service.directory.clear();
    service.exec.clear();
    service.args.clear();
    service.running=false;
}

void service_launcher::launch_services()
{
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        int ret = exec_service(*it);
        if(ret == -1)
        {
            it->enabled = false;
        }
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