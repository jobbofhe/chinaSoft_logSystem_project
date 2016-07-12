#include <signal.h>

void catch_Signal(int Sign)
{
	switch (Sign)
	{
	case SIGINT:
		//printf("signal SIGINT\n");
		break;
	case SIGPIPE:
		//printf("signal SIGPIPE\n");
		//signal1(SIGPIPE, catch_Signal);
		break;
	}
}

int signal1(int signo, void (*func)(int))
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	return sigaction(signo, &act, &oact);
}
