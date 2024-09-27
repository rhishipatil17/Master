#include <iostream>
#include "logging.h"

using namespace std;
using namespace sLogger;

MasterLogger &logger = MasterLogger::getInstance();

int main()
{
    cout << "Hello World" << endl;
    logger.init("Main");

    logger.log_msg("Hello World! Hi from 'Main'");
    this_thread::sleep_for(chrono::seconds(10));

    return 0;
}