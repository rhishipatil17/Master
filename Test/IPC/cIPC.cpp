#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "cIPC.h"
#include "mq_names.h"

using namespace ipc;

cIPC::cIPC(std::string name)
{
	proc_name = name;
	initialized = false;
	s_prio = 0;
	r_prio = nullptr;
	attr.mq_flags = 0;
	attr.mq_msgsize = QUEUE_MSGSIZE;
	attr.mq_maxmsg = QUEUE_MAXMSG;
	attr.mq_curmsgs = 0;
	int oflag = O_RDWR | O_CREAT | O_NONBLOCK;
	mode = S_IRWXU;

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

	if(initialized)
	{
		mq = mq_open(ipc_name.c_str(), oflag, mode, &attr);
		if(mq == Failure)
		{
			initialized = false;
		}
	}
}

cIPC::~cIPC()
{
	close();
}

return_codes cIPC::send(std::string message)
{
	if(initialized)
	{
		strncpy(send_buffer, message.c_str(), QUEUE_MSGSIZE);
		if(mq_send(mq, send_buffer, QUEUE_MSGSIZE, s_prio) == Failure)
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

return_codes cIPC::receive(std::string &message, bool noBlock /*= 0*/)
{
	if(initialized)
	{
		return_codes ret = Failure;
		do
		{
			memset(rec_buffer, 0, sizeof(rec_buffer));
			if(noBlock)
			{
				if( mq_receive(mq, rec_buffer, QUEUE_MSGSIZE, r_prio) == Failure )
				{
					break;
				}
			}
			else
			{
				ssize_t bytes_read = Failure;
				errno = 0;
				do
				{
					bytes_read = mq_receive(mq, rec_buffer, QUEUE_MSGSIZE, r_prio);
				}while((bytes_read == Failure) && (errno == EAGAIN));

				if((bytes_read == Failure) && (errno != EAGAIN))
				{
					break;
				}
			}
			
			rec_buffer[QUEUE_MSGSIZE] = TERMINATOR;
			message = rec_buffer;
			ret = Success;
		}while(false);
		return ret;
	}
	else
	{
		return NoInit;
	}
}

return_codes cIPC::close()
{
	if(initialized)
	{
		mq_close(mq);
		mq_unlink(ipc_name.c_str());
		return Success;
	}
	else
	{
		return NoInit;
	}
}
