//#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void logMenu()
{
	system("color 5e");

	printf("-------------------------------------------------------------\n");
	printf("\n\n\n                 **** ����ϵͳ ****               \n\n");
	printf("-------------------------------------------------------------\n\n");
	printf("||                        1.�û���.                            \n\n");
	printf("||                        2.��  ��.                          \n\n");
	printf("||                        0.��  ��.                         \n");

	printf("-------------------------------------------------------------\n");
}

logM *logToSystem()
{
	//����ռ佫��¼���û���Ϣ����
	logM * plogM = (logM *)calloc(1, sizeof(logM));
	initStruct(plogM); //��ʼ���ṹ��ָ��

	char userName[100] = { 0 };
	char password[100] = { 0 }; //������ʱ���������û���¼ʱ����Ϣ
	char allMessge[200] = { 0 };

	int userNameLen = 0;
	int passwordLen = 0;
	int count = 0;

	do{
	logMenu();
	printf("\n�����ȵ�¼:");
	printf("\n�������û���(��������ĸ�����ֻ��������)��");
	gets(userName);
	printf("\n����������(��������ĸ�����ֻ��������)��");
	fflush(stdin);
	gets(password);
	fflush(stdin);
	
	userNameLen = strlen(userName);
	passwordLen = strlen(password);
	if (userNameLen > 8)
	{
		system("cls");
		printf("\n��������û������󣡳���8λ������������\n");
	}
	if (passwordLen > 8)
	{
		system("cls");
		printf("\n��������������󣡳���8λ��\n");
	}
	count++;
	if (count > 3)
	{
		printf("���Ѿ�������Σ�ϵͳ������5���Ӻ��˳���");
		Sleep(3000);
		exit(0);
	}
	}while(userNameLen > 8 || passwordLen > 8);


	travUserMesg(userName);
	strcat(allMessge, userName);
	strcat(allMessge, ":");
	travUserMesg(password);
	strcat(allMessge, password);

	plogM->headFlag[0] = 1;
	memcpy(plogM->userMessage, allMessge, userNameLen+passwordLen + 1);

	return plogM;
}


void manageMenu()			//ϵͳ����˵�
{
	printf("1.�û�����\n");
	printf("2.��ɫ����\n");
	printf("3.Ȩ�޹���\n");
	printf("0.�� ��\n");
}

void userManageMenu()			//�û�����˵�
{
	printf("1.�����û�.\n");
	printf("2.ɾ���û�.\n");
	printf("3.�޸��û�.\n");
	printf("4.��ѯ�û�.\n");
	printf("0.�� ��.\n");
}

void roleManageMenu()			//��ɫ����˵�
{
	printf("1.���ӽ�ɫ.\n");
	printf("2.ɾ����ɫ.\n");
	printf("3.�޸Ľ�ɫ.\n");
	printf("4.��ѯ��ɫ.\n");
	printf("0.�� ��.\n");
}

void permissionManageMenu()		//Ȩ�޹���˵�
{
	printf("1.�޸�Ȩ��.\n");
	printf("2.��ѯȨ��.\n");
	printf("0.�� ��.\n");
}

void userAllMessageMenu()
{
	printf("1.�û���.\n");
	printf("2.�� ��.\n");
	printf("4.�� ��.\n");
	printf("5.ְλ.\n");
	printf("6.������.\n");
	printf("7.����ʱ��.\n");
	printf("8.��ɫ.\n");
	printf("0.�� ��.\n");
}