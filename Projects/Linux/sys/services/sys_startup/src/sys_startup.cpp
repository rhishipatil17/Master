#include <iostream>
#include <unistd.h>

#include "abstracted_api.h"
#include "service_launcher.h"

using namespace std;
using namespace abstracted_api;
using namespace service_launcher;

int main(int argc, char **argv)
{
	printf("Hello from startup app PID [%d]\n", getpid());
	// set_working_dir(getSysShareRoot().c_str());
	ServiceLauncher launcher;
}