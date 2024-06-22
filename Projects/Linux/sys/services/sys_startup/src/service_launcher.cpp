#include "service_launcher.h"
#include "abstracted_api.h"
#include "minIni.h"

#include <fstream>
#include <cstdio>
#include <unistd.h>

using namespace sys_startup;
using namespace abstracted_api;

service_launcher& service_launcher::getInstance()
{
    static service_launcher launcher;
    return launcher;
}

service_launcher::service_launcher()
{
    security_status = read_SecurityServiceConfig();
    launcher_status = read_LaunchConfig();
}

sys_SecurityCodes service_launcher::read_SecurityServiceConfig()
{
    std::ifstream file(SERVICE_SECURITY);
    if(!file)
    {
        return Sec_ConfigFailure;
    }
    file.close();

    clear_Service(service_security);
    service_security.enabled = ENABLED_TRUE;
    
    ConfigReader::minIni minFile(SERVICE_SECURITY);
    std::string value;

    if(!minFile.getKeyValue(SERVICE_NAME, value))
        return Sec_ConfigFailure;
    service_security.name = value;

    if(!minFile.getKeyValue(SERVICE_DIRECTORY, value))
        return Sec_ConfigFailure;
    service_security.directory = value;

    if(!minFile.getKeyValue(SERVICE_EXEC, value))
        return Sec_ConfigFailure;
    service_security.exec = value;

    if(minFile.getKeyValue(SERVICE_ARGS, value))
    {
        ConfigReader::minIni::getCSValues(value, service_security.args);
        service_security.args.push_back(NULL);
    }
    return Sec_ConfigSuccess;
}

launcher_codes service_launcher::read_LaunchConfig()
{
    std::ifstream file(SERVICE_LIST);
    if(!file)
    {
        service_list.clear();
        return launch_ConfigFailure;
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
    tFile.close();
    if(service_found)                                   //last service in the file will not have subsequent SERVICE_LABEL
    {
        struct service tService;
        clear_Service(tService);
        if(!extract_LaunchConfig(tFileName, tService))
        {
            service_list.push_back(tService);
        }
    }
    else
    {
        service_list.clear();
        return launch_NoServices;
    }
    remove(tFileName.c_str());
    return launch_ConfigSuccess;
}

short int service_launcher::extract_LaunchConfig(std::string FileName, struct service &service)
{
    ConfigReader::minIni minFile(FileName);
    std::string value;
    short int result = FAILURE;

    do
    {
        if(!minFile.getKeyValue(SERVICE_NAME, value))
            break;
        service.name = value;

        if(!minFile.getKeyValue(SERVICE_ENABLED, value))
            break;
        service.enabled = value;

        if(!minFile.getKeyValue(SERVICE_DIRECTORY, value))
            break;
        service.directory = value;

        if(!minFile.getKeyValue(SERVICE_EXEC, value))
            break;
        service.exec = value;

        result = SUCCESS;
        if(minFile.getKeyValue(SERVICE_ARGS, value))
        {
            ConfigReader::minIni::getCSValues(value, service.args);
            service.args.push_back(NULL);
        }
    }
    while(0);
    return result;
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

launcher_codes service_launcher::launch_services()
{
    if(launcher_status != launch_ConfigSuccess)
    {
        return launch_Failure;
    }
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        it->running = false;
    }
    
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        long int ret = exec_service(*it);
    }

    launcher_status = launch_RunningServices;
    return launch_Success;
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
        return FAILURE;
    }
}