#include <iostream>
#include <unistd.h>

#include "sys_startup.h"
#include "abstracted_api.h"
#include "service_launcher.h"

using namespace std;
using namespace sys_startup;
using namespace startup_config;
using namespace abstracted_api;

startup_config::StartupConfig &StartupConfig = startup_config::StartupConfig::getInstance();

int main(int argc, char **argv)
{
	cout << "Hello from startup app PID [%d]\n"<< getpid() << endl;

	service_launcher &launcher = service_launcher::getInstance();
	if(launcher.get_SecurityStatus() == Sec_ConfigSuccess)
	{
		sys_SecurityCodes ret = launcher.launch_security();
	}
	else
	{
		return 0;
	}





	if(launcher.get_LauncherStatus() == launch_ConfigSuccess)
	{
		launcher.launch_services();
	}
	return 0;
}