#include "service_launcher.h"
#include "abstracted_api.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace sys_startup;
using namespace abstracted_api;

service_launcher& service_launcher::getInstance()
{
    static service_launcher launcher;
    return launcher;
}

service_launcher::service_launcher()
{
    struct service ser;

    ser.name = SER1_NAME;
    ser.directory = SER1_DIR;
    ser.exec = SER1_EXEC;
    ser.args.push_back(SER1_EXEC);
    service_list.push_back(ser);
    clear_Service(ser);

    ser.name = SER2_NAME;
    ser.directory = SER2_DIR;
    ser.exec = SER2_EXEC;
    ser.args.push_back(SER2_EXEC);
    service_list.push_back(ser);
    clear_Service(ser);

    running_process_count = 0;
}

void service_launcher::clear_Service(struct service &service)
{
    service.name.clear();
    service.directory.clear();
    service.exec.clear();
    service.args.clear();
    service.pid=0;
}

return_codes service_launcher::launch_services()
{
    std::string PID = std::to_string(getpid());
    set_working_dir(get_sysroot_dir());
    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        it->args.push_back(PID);
        set_working_dir(it->directory);
        const long int ret = exec_service(*it);
        if(ret != FAILURE)
        {
            it->pid = ret;
            running_process_count++;
        }
        else
        {
            //TODO_msg: print error message
        }
        set_working_dir(get_sysroot_dir());
    }
    set_working_dir(get_home_dir());
    return SUCCESS;
}

long int service_launcher::exec_service(struct service &s_service)
{
    unsigned int arg_size = s_service.args.size();
    unsigned int max_str_size = 20;
    char **arg;

    auto make_ArgArr = [&]()
    {
        arg = new char*[arg_size+1];
        for(unsigned int i=0; i<arg_size; i++)
        {
            arg[i] = new char[max_str_size];
            std::strcpy(arg[i], s_service.args[i].c_str());
        }
        arg[arg_size] = nullptr;
    };
    auto clear_ArgArr = [&]()
    {
        for(unsigned int i=0; i<arg_size; i++)
        {
            delete arg[i];
            arg[i] = nullptr;
        }
        delete arg;
        arg = nullptr;
    };

    make_ArgArr();

    long int ret = vfork();
    if(ret == -1)
    {
        clear_ArgArr();
        return FAILURE;
    }
    if(ret)
    {
        int status;
        if( waitpid(ret, &status, WNOHANG) == 0 )
        {
            clear_ArgArr();
            return ret;
        }
        else if( WIFEXITED(status) && WEXITSTATUS(status) )
        {
            clear_ArgArr();
            return FAILURE;
        }
    }
    else
    {
        const int ret = execv(arg[0], arg);
        if(ret == -1)
        {
            clear_ArgArr();
            exit(EXIT_FAILURE);
        }

        clear_ArgArr();
        return SUCCESS;
    }
    return FAILURE;
}