//#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void logMenu()
{
	system("color 5e");
	// ▍ ▃ ■ ● ◆ □ ◇ § ♪ ♫ ▎ ▏ ▂ ▁ ☆ ┍ ┑ ┕ ┙  ╭ ─ ╮ │ ╳ ┃ ╰ ━ ╯ 
	printf("\n\n");
	printf("\t************************* 欢迎来到 *************************\n");
	printf("\t*                                                          *\n");
	printf("\t*                     用 户 管 理 系 统                    *\n");
	printf("\t*----------------------------------------------------------* \n");
	printf("\t*                                                          *\n");
	printf("\t*                            ----本系统由\"011世界\"开发---- *\n");
	printf("\t*                            --2016/05/20——2016/06/20--- *\n");
	printf("\t************************************************************\n");
	printf("\n");
	printf("------------------------------------------------------------------------");
} 

logM *logToSystem()
{
	logM * plogM = (logM *)calloc(1, sizeof(logM)); //申请空间将登录的用户信息保存
	initStruct(plogM); //初始化结构体指针

	char userName[100] = { 0 };
	char password[100] = { 0 }; //创建临时变量保存用户登录时的信息
	char allMessge[200] = { 0 };

	int userNameLen = 0;
	int passwordLen = 0;
	int count = 0;
	int icountu = 0;
	int icountp = 0;

	do
	{
		logMenu();
		printf("\t请您先登录:\n");
		printf("------------------------------------------------------------------------");
		printf("\t请输入用户名(仅包含字母、数字或两者组合,用户名位数小于8位)：\n");
		//gets(userName);
		fgets(userName, 21, stdin);  //截取输入的20位
		//printf("%d", strlen(userName));
		userName[strlen(userName) - 1] = '\0';
		printf("------------------------------------------------------------------------");
		printf("\n请输入密码(仅包含字母、数字或两者组合)：\n");
		fflush(stdin);

		/*char c;
		for (int i = 0; i < 100; i++)
		{
			c = _getch();
			if (c == 13)
			{
				password[i] = '\0';
				break;
			}
			if ((c <= 90 && c >= 65) || (c >= 97 && c <= 122) || (c >= 48 || c <= 57))
			{
				printf("*");
			}
			password[i] = c;
		}*/

		/*char c;
		int n = 0;
		do
		{
		c = _getch();
		if (c != '\n' && c != '\r' && c != 127)
		{
			password[n] = c;
			printf("*");
			n++;
		}
		else if ((c != '\n' || c!= '\r') && c != 127)
		{
		if (n > 0)
		{
			n--;
			printf("\b \b");
		}
		}
		} while ((c != '\n' || c != '\r') &&  c!=127);
		password[n] = '\0';*/

		//判断密码
		judgePasswd(password);
		
		fflush(stdin);

		userNameLen = strlen(userName);
		passwordLen = strlen(password);
		if (userNameLen > 8 || userNameLen <= 0)
		{
			system("cls");
			printf("\n您输入的用户名位数有误！请重新确定\n");

		}
		if (passwordLen > 8 || passwordLen <= 0)
		{
			system("cls");
			printf("\n您输入的密码位数有误！请重新确定\n");
		}
		count++;

		printf("\n%s ", userName);
		printf("%s ", password);
		icountu = travUserMesg(userName);
		icountp = travUserMesg(password);
	
		if (count >= 3)
		{
			printf("您已经输错三次，系统将会在3秒钟后退出！");
			Sleep(3000);
			exit(0);
		}
	} while (userNameLen > 8 || passwordLen > 8 || userNameLen <= 0 || passwordLen <= 0 || icountu != 1 || icountp != 1);


	strcat(allMessge, userName);
	strcat(allMessge, ":");
	strcat(allMessge, password);

	plogM->headFlag[0] = 1;
	memcpy(plogM->userMessage, allMessge, userNameLen+passwordLen + 1);

	return plogM;
}


void manageMenu()			//系统管理菜单
{
	printf("------------------------------------------------------------------------\n");
	printf("\t\t**** 用户管理系统 ****\n");
	printf("------------------------------------------------------------------------\n");
	printf("\t\t1.用户管理\n");
	printf("\t\t2.角色管理\n");
	printf("\t\t3.权限管理\n");
	printf("\t\t0.退 出\n");
	printf("------------------------------------------------------------------------\n");

}

void userManageMenu()			//用户管理菜单
{
	printf("------------------------------------------------------------------------\n");
	printf("\t\t\t  **** 用户管理系统 ****\n");
	printf("------------------------------------------------------------------------\n");
	printf("\t----用户管理\n");
	printf("------------------------------------------------------------------------\n");
	printf("\t\t1.增加用户.\n");
	printf("\t\t2.删除用户.\n");
	printf("\t\t3.修改用户.\n");
	printf("\t\t4.查询用户.\n");
	printf("\t\t0.退 出.\n");
	printf("------------------------------------------------------------------------\n");
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

