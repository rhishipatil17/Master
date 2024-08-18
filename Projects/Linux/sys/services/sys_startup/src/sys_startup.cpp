#include "service_launcher.h"

using namespace std;
using namespace sys_startup;

int main(int argc, char **argv)
{
	service_launcher &launcher = service_launcher::getInstance();
	launcher.launch_services();
	return 0;
}