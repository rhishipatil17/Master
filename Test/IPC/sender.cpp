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

using namespace std;

int main()
{
	mqd_t mq;
	struct mq_attr attr;
	char buffer[QUEUE_MSGSIZE];
	unsigned int prio = 0;

	attr.mq_flags = 0;
	attr.mq_msgsize = QUEUE_MSGSIZE;
	attr.mq_maxmsg = QUEUE_MAXMSG;
	attr.mq_curmsgs = 0;

	int oflag = O_CREAT | O_RDWR;
	// mode_t mode = S_IRWXG;
	// mode_t mode = S_IRWXG + S_IRWXO;
	mode_t mode = 0700;

	mq = mq_open(QUEUE_NAME, oflag, mode, &attr);
	if(mq == FAILURE)
	{
		cout << "Failed to open queue, errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	std::string input;
	while(true)
	{
		cout << "Enter the message to be sent or \"exit\" to end: ";
		cin >> input;

		strncpy(buffer, input.c_str(), QUEUE_MSGSIZE);
		if(mq_send(mq, buffer, QUEUE_MSGSIZE, prio) == FAILURE)
		{
			cout << "Failed to send the message" << endl << endl;
		}
		else
		{
			cout << "Message sent" << endl << endl;
		}

		if(input == MSG_EXIT)
		{
			break;
		}
	}

	mq_close(mq);
	// mq_unlink(QUEUE_NAME);

	return 0;
}