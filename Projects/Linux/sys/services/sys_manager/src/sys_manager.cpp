#include "sys_manager.h"

using namespace std;
using namespace sys_manager;

sys_man::sys_man()
{
	launcher = service_launcher::getInstance();
}

int main(int argc, char **argv)
{
	sys_man manager;
	return 0;
}