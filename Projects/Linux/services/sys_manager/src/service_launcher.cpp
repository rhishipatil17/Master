#include "service_launcher.h"
#include "abstracted_api.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace sys_manager;
using namespace abstracted_api;

service_launcher& service_launcher::getInstance()
{
    static service_launcher launcher;
    return launcher;
}

service_launcher::service_launcher()
{
    //read services from header file and store it in a list
    struct service ser;

    ser.name = SER1_NAME;
    ser.directory = SER1_DIR;
    ser.exec = SER1_EXEC;
    ser.args.push_back(SER1_EXEC);
    service_list.push_back(ser);
    clear_Service(ser);

    running_process_count = 0;
}

void service_launcher::clear_Service(struct service &service)
{
    //clear all details previously stored
    service.name.clear();
    service.directory.clear();
    service.exec.clear();
    service.args.clear();
    service.pid=0;
}

return_codes service_launcher::launch_services()
{
    //get current PID to send to children
    std::string PID = std::to_string(getpid());

    //set working directory to the system's root
    set_working_dir(get_sysroot_dir());

    for(std::vector<service>::iterator it = service_list.begin(); it != service_list.end(); it++)
    {
        //second argument to the new process
        it->args.push_back(PID);
        //set directory to the new process
        set_working_dir(it->directory);
        const long int ret = exec_service(*it);
        if(ret != FAILURE)
        {
            //store details if new process was successfully started
            it->pid = ret;
            running_process_count++;
        }
        else
        {
            //TODO_msg: print error message
        }
        //set directory to the sys root after process starting finishes
        set_working_dir(get_sysroot_dir());
    }
    //reset the directory to the startup home after everything is done
    set_working_dir(get_home_dir());
    return SUCCESS;
}

long int service_launcher::exec_service(struct service &s_service)
{
    unsigned int arg_size = s_service.args.size();
    unsigned int max_str_size = MAX_ARG_SIZE;
    char **arg;

    //create the list of arguments to send to the new process
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

    //cleanup of list
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

    //using vfork as the child will immediately get converted to new process anyways
    long int ret = vfork();
    if(ret == -1)
    {
        //child creation failed
        clear_ArgArr();
        return FAILURE;
    }
    if(ret)
    {
        //parent process
        int status;
        //check if the child PID is running
        //WNOHANG- return 0 without stopping if process is running
        if( waitpid(ret, &status, WNOHANG) == 0 )
        {
            //return child's PID if everything is good
            //TODO_work: again check after some delay if new process was successfully started
            clear_ArgArr();
            return ret;
        }
        else if( WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_FAILURE) )
        {
            //if the child exited and the status is EXIT_FAILURE (1)
            clear_ArgArr();
            return FAILURE;
        }
    }
    else
    {
        //child process
        //convert to new process here
        const int ret = execv(arg[0], arg);
        if(ret == -1)
        {
            //failed to convert to new process
            clear_ArgArr();
            exit(EXIT_FAILURE);
        }

        clear_ArgArr();
        return SUCCESS;
    }
    clear_ArgArr();
    return FAILURE;
}