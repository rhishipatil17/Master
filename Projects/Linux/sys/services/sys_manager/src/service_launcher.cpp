#include "service_launcher.h"
#include "abstracted_api.h"

#include <cstdio>
#include <unistd.h>

using namespace sys_manager;
using namespace abstracted_api;

service_launcher& service_launcher::getInstance()
{
    static service_launcher launcher;
    return launcher;
}

service_launcher::service_launcher()
{
    struct service ser;

    // ser.name = SER1_NAME;
    // ser.directory = SER1_DIR;
    // ser.exec = SER1_EXEC;
    // service_list.push_back(ser);
    // clear_Service(ser);

    // ser.name = SER2_NAME;
    // ser.directory = SER2_DIR;
    // ser.exec = SER2_EXEC;
    // service_list.push_back(ser);
    // clear_Service(ser);

    running_process_count = 0;
}

void service_launcher::clear_Service(struct service &service)
{
    service.name.clear();
    service.directory.clear();
    service.exec.clear();
    service.pid=0;
}

return_codes service_launcher::launch_services()
{
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        it->pid = 0;
    }
    
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        const long int ret = exec_service(*it);
        if(ret != FAILURE)
        {
            it->pid = ret;
            running_process_count += 1;
        }
        else
        {
            //TODO_msg: print error message
        }
    }
    return SUCCESS;
}

long int service_launcher::exec_service(struct service &s_service)
{
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
        // const int ret = execv(s_service.exec.c_str(), s_service.args.data());
        const int ret = 0;
        if(ret == -1)
        {
            exit(EXIT_FAILURE);
        }
        return SUCCESS;
    }
}