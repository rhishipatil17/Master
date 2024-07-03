#include "ThreadHandler.h"

using namespace common_Tools;

void ThreadHandler::create(void (*func)(void))
{
    children.emplace(children.end(), func);
}

ThreadHandler& ThreadHandler::getInstance()
{
    static ThreadHandler handler;
    return handler;
}