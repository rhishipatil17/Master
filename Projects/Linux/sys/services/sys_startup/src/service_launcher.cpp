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
    clear_Service(service_security);
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        clear_Service(*it);
    }
    total_process_count = 0;
    running_process_count = 0;

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
    if(extract_LaunchConfig(SERVICE_SECURITY, service_security))
    {
        return Sec_ConfigFailure;
    }
    service_security.enabled = ENABLED_TRUE;
    
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
                    total_process_count += 1;
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
            total_process_count += 1;
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
            getCSValues(value, service.args);
        }
    }
    while(0);
    if(result == FAILURE)
    {
        clear_Service(service);
    }
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
    service.pid=0;
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
        it->pid = 0;
    }
    
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        const long int ret = exec_service(*it);
        if(ret != FAILURE)
        {
            if(launcher_status == launch_ConfigSuccess)
            {
                launcher_status = launch_RunningServices;
            }
            it->running = true;
            it->pid = ret;
            running_process_count += 1;
        }
        else
        {
            //TODO_msg: print error message
        }
    }
    if(launcher_status == launch_ConfigSuccess)
    {
        launcher_status = launch_NoServices;
    }
    return launch_Success;
}

sys_SecurityCodes service_launcher::launch_security()
{
    if(security_status != Sec_ConfigSuccess)
    {
        return Sec_Failure;
    }
    service_security.running = false;
    service_security.pid = 0;
    
    const long int ret = exec_service(service_security);
    if(ret != FAILURE)
    {
        security_status = Sec_Running;
        service_security.running = true;
        service_security.pid = ret;
    }
    else
    {
        //TODO_msg: print error message
        security_status = Sec_Failure;
        return Sec_Failure;
    }
    return Sec_Success;
}

long int service_launcher::exec_service(struct service &s_service)
{
    if(!s_service.enabled.compare(ENABLED_TRUE))
    {
        //TODO_msg: print if enabled

        long int ret = vfork();

        if(ret != 0)
        {
            //TODO_work: if execv fails the parent should know
            return ret;
        }
        if(ret == -1)
        {
            return FAILURE;
        }
        else
        {
            set_working_dir( get_home_dir() + s_service.directory );
            //TODO_work: argv list to execv function
            const int ret = execv(s_service.exec.c_str(), s_service.args.data());
            if(ret == -1)
            {
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        //TODO_msg: print if not enabled
        return FAILURE;
    }
}