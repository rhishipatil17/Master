#include "service_launcher.h"
#include "abstracted_api.h"
#include "minIni.h"

using namespace sys_startup;
using namespace abstracted_api;

service_launcher::service_launcher()
{
    read_launch_config();
}

void service_launcher::launch_services()
{
    set_working_dir(getSysShareRoot());

    std::vector<std::string> files;
    bool ret = getFilesList(files, service_run);

    if(!ret || files.empty())
    {
        //TODO_msg: error
    }

    //TODO_msg: print files found

    for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++)
    {
        ConfigReader::minIni s_file(*it);
        //TODO_work: default values of members
        struct service s_service;
        bool valid = 0;

        while(1)
        {
            if(!s_file.getKeyValue(service_name, s_service.name))
                break;
            if(!s_file.getKeyValue(service_enabled, s_service.enabled))
                break;
            if(!s_file.getKeyValue(service_directory, s_service.directory))
                break;
            if(!s_file.getKeyValue(service_exec, s_service.exec))
                break;

            valid = 1;
            break;
        }
        if(valid)
        {
            //TODO_msg: print if valid or error
            service_list.push_back(s_service);
        }
    }

    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        int ret = exec_service(*it);
    }
}

bool service_launcher::read_launch_config()
{

}

int service_launcher::exec_service(struct service &s_service)
{
    if(!s_service.enabled.compare(enabled_true))
    {
        //TODO_msg: print if enabled


    }
}