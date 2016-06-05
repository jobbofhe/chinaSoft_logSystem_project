//#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void logMenu()
{
	system("color 5e");

	printf("-------------------------------------------------------------\n");
	printf("\n\n\n                 **** 管理系统 ****               \n\n");
	printf("-------------------------------------------------------------\n\n");
	printf("||                        1.用户名.                            \n\n");
	printf("||                        2.密  码.                          \n\n");
	printf("||                        0.退  出.                         \n");

	printf("-------------------------------------------------------------\n");
}

logM *logToSystem()
{
	//申请空间将登录的用户信息保存
	logM * plogM = (logM *)calloc(1, sizeof(logM));
	initStruct(plogM); //初始化结构体指针

	char userName[100] = { 0 };
	char password[100] = { 0 }; //创建临时变量保存用户登录时的信息
	char allMessge[200] = { 0 };

	int userNameLen = 0;
	int passwordLen = 0;
	int count = 0;

	do{
	logMenu();
	printf("\n请您先登录:");
	printf("\n请输入用户名(仅包含字母、数字或两者组合)：");
	gets(userName);
	printf("\n请输入密码(仅包含字母、数字或两者组合)：");
	fflush(stdin);
	gets(password);
	fflush(stdin);
	
	userNameLen = strlen(userName);
	passwordLen = strlen(password);
	if (userNameLen > 8)
	{
		system("cls");
		printf("\n您输入的用户名有误！超过8位！请重新输入\n");
	}
	if (passwordLen > 8)
	{
		system("cls");
		printf("\n您输入的密码有误！超过8位！\n");
	}
	count++;
	if (count > 3)
	{
		printf("您已经输错三次，系统将会在5秒钟后退出！");
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


void manageMenu()			//系统管理菜单
{
	printf("1.用户管理\n");
	printf("2.角色管理\n");
	printf("3.权限管理\n");
	printf("0.退 出\n");
}

void userManageMenu()			//用户管理菜单
{
	printf("1.增加用户.\n");
	printf("2.删除用户.\n");
	printf("3.修改用户.\n");
	printf("4.查询用户.\n");
	printf("0.退 出.\n");
}

void roleManageMenu()			//角色管理菜单
{
	printf("1.增加角色.\n");
	printf("2.删除角色.\n");
	printf("3.修改角色.\n");
	printf("4.查询角色.\n");
	printf("0.退 出.\n");
}

void permissionManageMenu()		//权限管理菜单
{
	printf("1.修改权限.\n");
	printf("2.查询权限.\n");
	printf("0.退 出.\n");
}

void userAllMessageMenu()
{
	printf("1.用户名.\n");
	printf("2.电 话.\n");
	printf("4.邮 箱.\n");
	printf("5.职位.\n");
	printf("6.创建者.\n");
	printf("7.创建时间.\n");
	printf("8.角色.\n");
	printf("0.退 出.\n");
}