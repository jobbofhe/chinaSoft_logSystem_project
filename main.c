//#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>


void main()
{
	logM *pSend = logToSystem();
	logM pSendRe;

	memset(&pSendRe, 0, sizeof(pSendRe));

	printf("发送信息确认:%d %s\n", pSend->headFlag[0], pSend->userMessage);//测试传输数据的正确性

	SOCKET sockClient = connectToServer();//连接到服务器
	send(sockClient, (const char *)pSend, sizeof(*pSend), 0);	//发送数据
	//Sleep(5000);
	system("cls");

	recv(sockClient, (char *)&pSendRe, sizeof(pSendRe), 0);			//接受服务器返回的数据
	printf("发送信息确认:%d   %s\n", pSendRe.headFlag[0], pSendRe.userMessage);//测试传输数据的正确性


	printf("服务器回复:%d\n", pSendRe.headFlag[0]);
	processServerReMsg(&pSendRe, sockClient);

	/************************************************************************
	*接收到服务器传回的消息之后，进行判断是超级用户还是普通用户，调用不同的权限的函数
	************************************************************************/

	//关闭socket
	closesocket(sockClient);
	WSACleanup();

	system("pause");
}