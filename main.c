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

	printf("������Ϣȷ��:%d %s\n", pSend->headFlag[0], pSend->userMessage);//���Դ������ݵ���ȷ��

	SOCKET sockClient = connectToServer();//���ӵ�������
	send(sockClient, (const char *)pSend, sizeof(*pSend), 0);	//��������
	//Sleep(5000);
	system("cls");

	recv(sockClient, (char *)&pSendRe, sizeof(pSendRe), 0);			//���ܷ��������ص�����
	printf("������Ϣȷ��:%d   %s\n", pSendRe.headFlag[0], pSendRe.userMessage);//���Դ������ݵ���ȷ��


	printf("�������ظ�:%d\n", pSendRe.headFlag[0]);
	processServerReMsg(&pSendRe, sockClient);

	/************************************************************************
	*���յ����������ص���Ϣ֮�󣬽����ж��ǳ����û�������ͨ�û������ò�ͬ��Ȩ�޵ĺ���
	************************************************************************/

	//�ر�socket
	closesocket(sockClient);
	WSACleanup();

	system("pause");
}