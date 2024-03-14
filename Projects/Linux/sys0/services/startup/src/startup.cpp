#include <iostream>

#include "abstracted_api.hpp"

using namespace std;

int main(int argc, char *argv)
{
	int ret = 0;
	abstracted_api::set_working_dir(get_home_dir().c_str());
}