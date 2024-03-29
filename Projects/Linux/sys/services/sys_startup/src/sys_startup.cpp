#include <iostream>
#include <unistd.h>

#include "abstracted_api.h"

using namespace std;
using namespace abstracted_api;

int main(int argc, char **argv)
{
	printf("Hello from startup app PID [%d]\n", getpid());
	// set_working_dir(getSysShareRoot().c_str());
	
}