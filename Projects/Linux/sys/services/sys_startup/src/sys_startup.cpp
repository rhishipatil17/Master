#include <iostream>
#include <unistd.h>

#include "StartupConfig.h"
#include "abstracted_api.h"

using namespace std;
using namespace abstracted_api;
using namespace startup_config;

int main(int argc, char **argv)
{
	cout << "Hello from startup app PID [%d]\n"<< getpid() << endl;
	
	StartupConfig::getInstance();
	return 0;
}