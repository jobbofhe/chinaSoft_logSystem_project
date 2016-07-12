#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "myServer.h"
#include "Mysql.h"


int main(int arg, char *args[])
{
	if (arg < 2)//如果没有参数，main函数返回
	{
		printf("usage:server port\n");
		return -1;
	}

	int iport = atoi(args[1]);
	if (iport == 0)
	{
		printf("port %d is invalid\n", iport);
		return -1;
	}

	//Mysql my;
	//int ret = my.select_name_and_passwd("root", "123456");
	//cout << ret << endl;
//	setdaemon();//进入daemon状态
	myServer s = myServer(iport);

	printf("qqserver is begin\n");

//	signal1(SIGINT, catch_Signal);
//	signal1(SIGPIPE, catch_Signal);
	s.run();
	printf("qqserver is end\n");
	return 0;
}
