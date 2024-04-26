#include <iostream>
#include <unistd.h>

#include "sys_startup.h"
#include "abstracted_api.h"
#include "service_launcher.h"

using namespace std;
using namespace sys_startup;
using namespace abstracted_api;

int main(int argc, char **argv)
{
	cout << "Hello from startup app PID [%d]\n"<< getpid() << endl;
	s_config();
	service_launcher launcher;
	// launcher.launch_services();
	return 0;
}

startup_config::StartupConfig& sys_startup::s_config()
{
	return startup_config::StartupConfig::getInstance();
}