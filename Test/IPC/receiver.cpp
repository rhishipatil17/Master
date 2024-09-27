#include <iostream>
#include <errno.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>
#include <cstring>

#define FAILURE -1

#define QUEUE_NAME "/test_queue"
#define QUEUE_MSGSIZE 1024
#define QUEUE_MAXMSG 10

#define MSG_EXIT "exit"
#define TERMINATOR '\0'

using namespace std;

int main()
{
	mqd_t mq;
	struct mq_attr attr;
	char buffer[QUEUE_MSGSIZE + 1];
	ssize_t bytes_read;
	unsigned int s_prio = 0;
	unsigned int *r_prio = nullptr;

	attr.mq_flags = 0;
	attr.mq_msgsize = QUEUE_MSGSIZE;
	attr.mq_maxmsg = QUEUE_MAXMSG;
	attr.mq_curmsgs = 0;

	// int oflag = O_CREAT | O_RDWR;
	int oflag = O_RDONLY;
	mode_t mode = S_IRWXG;

	// mq = mq_open(QUEUE_NAME, oflag, mode, &attr);
	mq = mq_open(QUEUE_NAME, oflag);
	if(mq == FAILURE)
	{
		cout << "Failed to open queue, errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	while(true)
	{
		memset(buffer, 0, sizeof(buffer));
		cout << "Waiting for a message" << endl;
		bytes_read = mq_receive(mq, buffer, QUEUE_MSGSIZE, r_prio);

		if(bytes_read >= 0)
		{
			buffer[bytes_read] = TERMINATOR;
			cout << "Received message: " << buffer << endl << endl;

			if(string(buffer) == MSG_EXIT)
			{
				break;
			}
		}
		else
		{
			cout << "Error receiving message" << endl << endl;
		}
	}

	mq_close(mq);
	mq_unlink(QUEUE_NAME);
	return 0;
}