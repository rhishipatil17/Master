#include "service_launcher.h"
#include "abstracted_api.h"
#include "minIni.h"

using namespace sys_startup;
using namespace abstracted_api;

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
        struct service s_service;
        bool valid = 1;

        if(!s_file.getKeyValue(service_name, s_service.name))
            valid = 0;
        if(!s_file.getKeyValue(service_enabled, s_service.enabled))
            valid = 0;
        if(!s_file.getKeyValue(service_directory, s_service.directory))
            valid = 0;
        if(!s_file.getKeyValue(service_exec, s_service.exec))
            valid = 0;

        if(valid)
        {
            s_service.running = false;
            service_list.push_back(s_service);
        }
    }

    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        int ret = exec_service(*it);
    }
}

int service_launcher::exec_service(struct service &s_service)
{
    if(!s_service.enabled.compare(enabled_true))
    {
        
    }
}