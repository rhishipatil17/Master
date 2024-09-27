#ifndef CIPC_H
#define CIPC_H

#include <thread>
#include <map>
#include <string>
#include <errno.h>
#include <mqueue.h>

#include <string>
#include <cstring>

#define QUEUE_MSGSIZE 1024
#define QUEUE_MAXMSG 10

#define TERMINATOR '\0'

namespace ipc
{
	enum return_codes
	{
		Failure = -1;
		NoInit = -2;
		Success;
		
	};
	class cIPC
	{
		public:
			cIPC(std::string name): proc_name(name) {}
			~cIPC();
			return_codes send(std::string message);
			return_codes receive(std::string &message, bool noBlock = 0);

		private:
			bool initialized;
			std::string proc_name;
			std::string ipc_name;
			mqd_t mq;
			struct mq_attr attr;
			char send_buffer[QUEUE_MSGSIZE];
			char rec_buffer[QUEUE_MSGSIZE + 1];
			unsigned int s_prio;
			unsigned int *r_prio = nullptr;
			int oflag;
			mode_t mode;
	};
}

#endif