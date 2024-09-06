#include "service_launcher.h"

using namespace std;
using namespace sys_startup;

int main()
{
	service_launcher &launcher = service_launcher::getInstance();
	launcher.launch_services();
	return 0;
}