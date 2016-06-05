//#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/********************************************************************
*��¼��������
********************************************************************/
SOCKET  connectToServer()
{
	WSADATA wsaData;
	SOCKET sockClient;       //�ͻ���Socket
	SOCKADDR_IN addrServer;  //����˵�ַ
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sockClient = socket(AF_INET, SOCK_STREAM, 0);	//�½��ͻ���socket

	//����Ҫ���ӵķ���˵�ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.40"); 
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(10002); //���Ӷ˿�10002

	//���ӵ������
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	return sockClient;
}

/************************************************************************/
/* �����û���Ϣ�жϷ���ĸ������                                                                     */
/************************************************************************/
void travUserMesg(char *userMessage)    //�����û���Ϣ
{
	if (userMessage == NULL)
	{
		exit(0);
	}
	while (*userMessage != '\0')  //�����û���
	{
		if (isalpha(*userMessage) || isdigit(*userMessage)) //�ж���ĸ������
		{
			userMessage++;
		}
		else
		{
			system("cls");
			printf("�û���Ϣ�����ڴ����֡�����ĸ���������!");
			printf("����������:");
			scanf("%s", userMessage);
		}
	}
}

/*��δ������ڳ��ֵݹ�ĵ�Ч�ʱ�����
void judgeUserMessageOverEight(int userMessageLen)
{
	int choose = 0;
	int length = userMessageLen;
	if (length > 8)
	{
		printf("\n���������Ϣ���󣡳���8λ��\n");
		printf("\n��ѡ�񣺰�1���������档��������˳���");
		fflush(stdin);
		scanf("%d", &choose);
		fflush(stdin);
		if (choose == 1)
		{
			system("cls");
			logToSystem();
		}
		else
		{
			exit(0);
		}
	}
}
*/

/********************************************************************
*��ʼ���ṹ��
********************************************************************/
void initStruct(logM * plogM)
{
	memset(plogM->headFlag, 0, sizeof(plogM->headFlag));
	memset(plogM->userMessage, 0, sizeof(plogM->userMessage));
}

void initUserALLMsgStruct(userMsg * pUserMsg)
{
	memset(pUserMsg->userName, 0, sizeof(pUserMsg->userName));
	memset(pUserMsg->del, 0, sizeof(pUserMsg->del));

	memset(pUserMsg->mail, 0, sizeof(pUserMsg->mail));
	memset(pUserMsg->job, 0, sizeof(pUserMsg->job));
	memset(pUserMsg->createPerson, 0, sizeof(pUserMsg->createPerson));
	memset(pUserMsg->createTime, 0, sizeof(pUserMsg->createTime));
	memset(pUserMsg->role, 0, sizeof(pUserMsg->role));
	memset(pUserMsg->password, 0, sizeof(pUserMsg->password));
}
/************************************************************************/
/* ������������ص�headflag��Ϣ�����ݷ�����Ϣ                                */
/************************************************************************/
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient)
{
	logM *pSend = receiveServerMsg;
	SOCKET sok = sockClient;

	if (1 == pSend->headFlag[0])
	{
		system("cls");
		printf("\n\n\n\n               ��¼�ɹ�");
		Sleep(2000);
		system("cls");

		//��½�ɹ�֮�����ϵͳ����˵������й���
		int choose = -1;
		while (choose)
		{
			manageMenu();
			fflush(stdin);


			printf("\n��ѡ����:");
			scanf("%d", &choose);
			if (choose == 1)		//�û�����
			{
				userManageMenu();
				printf("\n��ѡ����:");
				scanf("%d", &choose);
				if (choose == 1)		//�����û�
				{
					printf("��Ҫ��д����Ϣ���£�");
					userAllMessageMenu();
					addUser(sok);
				}
				else if (2 == choose)	//ɾ���û�
				{
					deleteUser(sok);
				}
				else if (3 == choose)	//�޸��û�
				{
					changeUser(sok);
				}
				else if (4 == choose)	//��ѯ�û�
				{
					printf("��ѯ�û���\n");
					queryUser(sok);
					printf("��ѯ�û�����\n");
				}
				else
				{
					exit(0);
				}
			}


			else if (2 == choose)
			{
				roleManageMenu();
			}


			else if (3 == choose)
			{
				permissionManageMenu();
				fflush(stdin);

				printf("\n��ѡ����:");
				scanf("%d", &choose);
				
				if (choose == 1)		//�޸�Ȩ��
				{
					printf("�޸�Ȩ�ޣ�");
					changePermission(sok);
				}
				
				else if (2 == choose)	//��ѯȨ��
				{
					printf("��ѯȨ�ޣ�\n");
					queryPermission(sok);
					printf("��ѯ�û�����\n");

				}
				else
				{
					exit(0);
				}
			}
			else
			{
				printf("���������룡\n");
			}
		}
	}
	else
	{
		printf("\n��¼ʧ�ܣ�");
		Sleep(2000);
		exit(0);
	}
}

////////////////////////////////�û�����//////////////////////////////////
                   
/************************************************************************/
/* �������û�                                                             */
/************************************************************************/
void addUser(SOCKET sockClient)
{
	SOCKET sok = sockClient;
	userMsg *pUserMsg = (userMsg *)calloc(1, sizeof(userMsg));
	char *allMsg = (char *)calloc(1024, sizeof(char));

	logM *pRe = (logM *)calloc(1, sizeof(logM));		
	//��½֮����������ظ��ͻ���headflag[1]=1;���������������ӵ��û�����Ϣ

	logM *pFromServer = (logM *)calloc(1, sizeof(logM)); //��ʱ���������ܷ��������ص��û���ӳɹ������Ϣ

	initUserALLMsgStruct(pUserMsg);

	pRe->headFlag[0] = 2;	//�û�����
	pRe->headFlag[1] = 1;	//�����û��ı�־

	printf("\n\n\n\n       �������û���:");
	scanf("%s", pUserMsg->userName);
	strcat(allMsg, pUserMsg->userName);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       ������绰:");
	scanf("%s", pUserMsg->del);
	strcat(allMsg, pUserMsg->del);
	strcat(allMsg, ":");
	system("cls");
	
	printf("\n\n\n\n       ����������:");
	scanf("%s", pUserMsg->mail);
	strcat(allMsg, pUserMsg->mail);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       ������ְλ:");
	scanf("%s", pUserMsg->job);

	strcat(allMsg, pUserMsg->job);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       �����봴����:");
	scanf("%s", pUserMsg->createPerson);

	strcat(allMsg, pUserMsg->createPerson);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       �����봴��ʱ��:");
	scanf("%s", pUserMsg->createTime);

	strcat(allMsg, pUserMsg->createTime);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       �������ɫ:");
	scanf("%s", pUserMsg->role);

	strcat(allMsg, pUserMsg->role);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       ����������:");
	scanf("%s", pUserMsg->password);

	strcat(allMsg, pUserMsg->password);
	system("cls");

	strcpy(pRe->userMessage, allMsg);

	printf("\n�����û���Ϣȷ��\n�����û���ʶ��headFlag[1]:%d\n�û���Ϣ��%s\n", pRe->headFlag[1], pRe->userMessage);
	send(sockClient, (char *)pRe, sizeof(*pRe), 0);			//��������

	recv(sockClient, (char *)pFromServer, sizeof(*pFromServer), 0);			//���ܷ��������ص�����
	printf("received server :%d %s\n", pFromServer->headFlag[1], pFromServer->userMessage);

	if (1 == pFromServer->headFlag[1])
	{
		printf("����û��ɹ�!\n");
	}
	else
	{
		printf("����û�ʧ�ܣ������������룬������ӣ�\n");
	}

	free(pUserMsg);
	free(allMsg);
	free(pRe);
	free(pFromServer);
}

/************************************************************************/
/* ɾ���û�                                                               */
/************************************************************************/
void deleteUser(SOCKET sockClient)
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//����������������ѯ����Ϣ
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//���ܷ������ش���״̬��Ϣ���û���Ϣ

	plogM->headFlag[0] = 2;
	plogM->headFlag[1] = 4;	
	plogM->headFlag[2] = 1;	//�����ѯ��־
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//��������

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص�����

	if (1 == plogMRe->headFlag[2])
	{
		//ɾ���û��������
		//�г������û���
		listExistUserName(plogMRe);

		//����Ҫɾ�����û������г����û�����ϸ��Ϣ
		char queryName[20] = { 0 };
		plogM->headFlag[1] = 2;
		memset(plogMRe, 0, sizeof(logM));

		printf("������Ҫɾ�����û�����");
		scanf("%s", queryName);
		strcpy(plogM->userMessage, queryName);

		send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//��������
		printf("\n�����û���ȷ��headFlag[1]:%d %s\n", plogM->headFlag[1], plogM->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص�����
		printf("received server :%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		if (2 == plogMRe->headFlag[1])
		{
			printf("ɾ���ɹ���\n");
		}
		else
		{
			printf("ɾ��ʧ�ܣ��������Ĳ�����\n");
		}

	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}

	free(plogM);
	free(plogMRe);
}

/************************************************************************/
/* �޸��û�                                                              */
/************************************************************************/
void changeUser(SOCKET sockClient)
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//����������������ѯ����Ϣ
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//���ܷ������ش���״̬��Ϣ���û���Ϣ

	userMsg *pUserMsg = (userMsg *)calloc(1, sizeof(userMsg)); //����������޸���Ϣ
	char *allMsg = (char *)calloc(1024, sizeof(char));			//�����޸���Ϣ��

	plogM->headFlag[0] = 2;	//�û������־
	plogM->headFlag[1] = 4;	//��ѯ��־
	plogM->headFlag[2] = 1;	//�����ѯ��־
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//���������ѯ����

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص������ж��Ƿ�ɲ�

	if (1 == plogMRe->headFlag[2])  //���Բ�ѯ���г��û���
	{
		//�޸��û��������
		//�г������û���
		listExistUserName(plogMRe);

		//����Ҫ�޸ĵ��û��������޸���Ϣ
		char queryName[20] = { 0 };
		plogM->headFlag[1] = 3;
		memset(plogMRe, 0, sizeof(logM));

		//����Ҫ�޸ĵ��û���
		printf("\n\n\n\n       ������Ҫ�޸ĵ��û���:");
		scanf("%s", pUserMsg->userName);
		strcat(allMsg, pUserMsg->userName);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       ������绰:");
		scanf("%s", pUserMsg->del);
		strcat(allMsg, pUserMsg->del);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       ����������:");
		scanf("%s", pUserMsg->mail);
		strcat(allMsg, pUserMsg->mail);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       ������ְλ:");
		scanf("%s", pUserMsg->job);

		strcat(allMsg, pUserMsg->job);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       �����봴����:");
		scanf("%s", pUserMsg->createPerson);

		strcat(allMsg, pUserMsg->createPerson);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       �����봴��ʱ��:");
		scanf("%s", pUserMsg->createTime);

		strcat(allMsg, pUserMsg->createTime);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       �������ɫ:");
		scanf("%s", pUserMsg->role);

		strcat(allMsg, pUserMsg->role);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       ����������:");
		scanf("%s", pUserMsg->password);

		strcat(allMsg, pUserMsg->password);
		system("cls");

		strcpy(plogMRe->userMessage, allMsg);
		plogMRe->headFlag[0] = 2;
		plogMRe->headFlag[1] = 3;

		send(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);			//��������
		printf("\n�����û���ȷ��headFlag[1]:%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص�����
		printf("received server :%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		if (3 == plogMRe->headFlag[1])
		{
			printf("�޸ĳɹ���\n");
		}
		else
		{
			printf("�޸�ʧ�ܣ��������Ĳ�����\n");
		}

	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}

	free(plogM);
	free(plogMRe);
	free(pUserMsg);
	free(allMsg);
}

/************************************************************************/
/* ��ѯ�û�                                                              */
/************************************************************************/
void queryUser(SOCKET sockClient)
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//����������������ѯ����Ϣ
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//���ܷ������ش���״̬��Ϣ���û���Ϣ

	plogM->headFlag[0] = 2;	//�û������־
	plogM->headFlag[1] = 4;	//��ѯ�û���ʶ
	plogM->headFlag[2] = 1;	//�����ѯ��־
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//��������

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص�����

	if (1 == plogMRe->headFlag[2])
	{
		//�г��Ѵ��������û���
		char *allUserName = plogMRe->userMessage;
		char *pAum = allUserName;
		char buf[20] = { 0 };

		printf("�����û���Ϣ:\n");
		while (*allUserName != '\0')
		{
			if (*allUserName == ':')
			{
				strncpy(buf, pAum, allUserName - pAum);
				buf[allUserName - pAum] = '\0';
				printf("�û����� %s\n",buf);
				pAum = pAum + (allUserName - pAum) + 1;
			}
			allUserName++;
		}

		//����Ҫ��ѯ���û������г����û�����ϸ��Ϣ
		char queryName[20] = { 0 };
		plogM->headFlag[2] = 2;
		memset(plogMRe, 0, sizeof(logM));

		printf("������Ҫ��ѯ���û�����");
		scanf("%s", queryName);
		strcpy(plogM->userMessage, queryName);

		send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//��������
		printf("\n�����û���ȷ��headFlag[2]:%d %s\n", plogM->headFlag[2], plogM->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص�����
		printf("received server :%d %s\n", plogMRe->headFlag[2], plogMRe->userMessage);

		strcat(plogMRe->userMessage, ":");
		if (2 == plogMRe->headFlag[2])
		{
			char *oneUserMsg = plogMRe->userMessage;
			char *pOum = oneUserMsg;
			char buf[40] = { 0 };

			printf("�û���Ϣ��ϸ��Ϣ:\n");
			while (*oneUserMsg != '\0')
			{
				if (*oneUserMsg == ':')
				{
					strncpy(buf, pOum, oneUserMsg - pOum);
					buf[oneUserMsg - pOum] = '\0';

					printf("���û���Ϣ�� %s\n", buf);
					pOum = pOum + (oneUserMsg - pOum) + 1;
				}
				oneUserMsg++;
			}
		}

	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}

	free(plogM);
	free(plogMRe);
}

/************************************************************************/
/* �г���ǰ�����û���                                                      */
/************************************************************************/
void listExistUserName(logM * plogM)
{
	//SOCKET soc = sockClient;
	//logM *plogM = (logM *)calloc(1, sizeof(logM));		//����������������ѯ����Ϣ
	//logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//���ܷ������ش���״̬��Ϣ���û���Ϣ

	//plogM->headFlag[0] = 2;		//�û������־
	//plogM->headFlag[1] = 4;		//��ѯ�û���ʶ
	//plogM->headFlag[2] = 1;		//�����ѯ��־
	//send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//��������

	//recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//���ܷ��������ص�����
	logM * plogMRe = plogM;

	if (1 == plogMRe->headFlag[2])
	{
		//�г��Ѵ��������û���
		char *allUserName = plogMRe->userMessage;
		char *pAum = allUserName;
		char buf[20] = { 0 };

		printf("�����û���Ϣ:\n");
		while (*allUserName != '\0')
		{
			if (*allUserName == ':')
			{

				strncpy(buf, pAum, allUserName - pAum);
				buf[allUserName - pAum] = '\0';
				printf("�û����� %s\n", buf);
				pAum = pAum + (allUserName - pAum) + 1;
			}
			allUserName++;
		}
	}
	else
	{
		printf("ɾ��������������г������û�����\n");
	}
}

////////////////////////////////��ɫ����////////////////////////////////////




////////////////////////////////Ȩ�޹���////////////////////////////////////
void changePermission(SOCKET sockClient)			//�޸�Ȩ��
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//����������������ѯȨ�޵���Ϣ
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//���ܷ������ش���״̬��Ϣ��Ȩ����Ϣ

	if (!soc)
	{
		printf("socket error��");
	}
		
	char permissionNum[20] = { 0 };
	printf("ϵͳ����Ȩ���б�:\n");
	listExistPermission();

	printf("��ѡ��Ȩ�ޣ�(����1Ϊ��ӣ���������ֵΪ�����)\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%s", permissionMessg[i]);
		fflush(stdin);
		scanf("%c", permissionNum + i);
	}

	//����û�����100λ���Ŵ����
	for (int i = 0; i < 10; i++)
	{
		if (permissionNum[i] == '1')
		{
			permissionNum[i] = '1';
		}
		else
		{
			permissionNum[i] = '0';
		}
	}

	plogM->headFlag[0] = 4;	//Ȩ�޹����־
	plogM->headFlag[1] = 1;	//�����޸ı�־
	strcpy(plogM->userMessage, permissionNum);

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//���������ѯ����

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("�յ����������ص��ַ�����\n heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);
	if (1 == plogMRe->headFlag[1])
	{
		printf("�޸ĳɹ���\n");
	}
	else
	{
		printf("�޸�ʧ�ܣ�\n");
	}

	free(plogM);
	free(plogMRe);
}

void queryPermission(SOCKET sockClient)				//��ѯȨ��
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//����������������ѯȨ�޵���Ϣ
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//���ܷ������ش���״̬��Ϣ��Ȩ����Ϣ


	if (!soc)
	{
		printf("socket error��");
	}
	plogM->headFlag[0] = 4;	//Ȩ�޹����־
	plogM->headFlag[1] = 2;	//�����ѯ��־

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//���������ѯ����

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("�յ����������ص��ַ�����heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);

	if (2 == plogMRe->headFlag[1])
	{
		//�г��Ѵ�������Ȩ��
		char *pAp = plogMRe->userMessage;  //��0 1�ַ���
		int len = strlen(pAp);


		printf("����Ȩ����Ϣ:\n");
		for (int i = 0; i < len; i++)
		{
			if (pAp[i] != '0')
			{
				printf("%s\n", permissionMessg[i]);
			}
		}
	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}

	free(plogM);
	free(plogMRe);

}
void listExistPermission()			//�г���ǰ����Ȩ����
{

	for (int i = 0; i < 10; i++)
	{
		printf("%s\n", permissionMessg[i]);
	}
}