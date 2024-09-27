#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "cIPC.h"
#include "mq_names.h"

using namespace ipc;

cIPC::cIPC(std::string name)
{
	initialized = false;
	if(name == PROC1)
	{
		ipc_name = IPC_PROC1;
		initialized = true;
	}
	else if(name == PROC2)
	{
		ipc_name = IPC_PROC2;
		initialized = true;
	}

	prio = 0;
	r_prio = nullptr;
	attr.mq_flags = 0;
	attr.mq_msgsize = QUEUE_MSGSIZE;
	attr.mq_maxmsg = QUEUE_MAXMSG;
	attr.mq_curmsgs = 0;
	int oflag = O_RDWR | O_CREAT | O_NONBLOCK;
	mode = S_IRWXU;

	mq = mq_open(QUEUE_NAME, oflag, mode, &attr);
	if(mq == Failure)
	{
		initialized = false;
	}
}

cIPC::~cIPC()
{

}

return_codes cIPC::send(std::string message)
{
	if(initialized)
	{
		strncpy(send_buffer, message.c_str(), QUEUE_MSGSIZE);
		if(mq_send(mq, buffer, QUEUE_MSGSIZE, prio) == Failure)
		{
			return Failure;
		}
	}
	else
	{
		return NoInit;
	}
	return Success;
}

return_codes receive(std::string &message, bool noBlock /*= 0*/)
{
	if(initialized)
	{
		ssize_t bytes_read = Failure;
		memset(rec_buffer, 0, sizeof(rec_buffer));
		if(noBlock)
		{
			bytes_read = mq_receive(mq, rec_buffer, QUEUE_MSGSIZE, r_prio);
		}
		else
		{
			errno = 0;
			while(bytes_read == Failure)
			{
				bytes_read = mq_receive(mq, rec_buffer, QUEUE_MSGSIZE, r_prio);
				if( (bytes_read == Failure) && (errno != EAGAIN) )
				{
					return Failure;
				}
			}
			rec_buffer[QUEUE_MSGSIZE] = TERMINATOR;
		}
	}
	else
	{
		return NoInit;
	}
}
