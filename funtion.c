//#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/********************************************************************
*登录到服务器
********************************************************************/
SOCKET  connectToServer()
{
	WSADATA wsaData;
	SOCKET sockClient;       //客户端Socket
	SOCKADDR_IN addrServer;  //服务端地址
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sockClient = socket(AF_INET, SOCK_STREAM, 0);	//新建客户端socket

	//定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.40"); 
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(10002); //连接端口10002

	//连接到服务端
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	return sockClient;
}

/************************************************************************/
/* 遍历用户信息判断非字母非数字                                                                     */
/************************************************************************/
void travUserMesg(char *userMessage)    //遍历用户信息
{
	if (userMessage == NULL)
	{
		exit(0);
	}
	while (*userMessage != '\0')  //遍历用户名
	{
		if (isalpha(*userMessage) || isdigit(*userMessage)) //判断字母和数字
		{
			userMessage++;
		}
		else
		{
			system("cls");
			printf("用户信息仅限于纯数字、纯字母或两者组合!");
			printf("请重新输入:");
			scanf("%s", userMessage);
		}
	}
}

/*这段代码由于出现递归的低效率被舍弃
void judgeUserMessageOverEight(int userMessageLen)
{
	int choose = 0;
	int length = userMessageLen;
	if (length > 8)
	{
		printf("\n您输入的信息有误！超过8位！\n");
		printf("\n请选择：按1返回主界面。按任意键退出！");
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
*初始化结构体
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
/* 处理服务器返回的headflag信息，根据返回消息                                */
/************************************************************************/
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient)
{
	logM *pSend = receiveServerMsg;
	SOCKET sok = sockClient;

	if (1 == pSend->headFlag[0])
	{
		system("cls");
		printf("\n\n\n\n               登录成功");
		Sleep(2000);
		system("cls");

		//登陆成功之后调用系统管理菜单的所有功能
		int choose = -1;
		while (choose)
		{
			manageMenu();
			fflush(stdin);


			printf("\n请选择功能:");
			scanf("%d", &choose);
			if (choose == 1)		//用户管理
			{
				userManageMenu();
				printf("\n请选择功能:");
				scanf("%d", &choose);
				if (choose == 1)		//增加用户
				{
					printf("需要填写的信息如下：");
					userAllMessageMenu();
					addUser(sok);
				}
				else if (2 == choose)	//删除用户
				{
					deleteUser(sok);
				}
				else if (3 == choose)	//修改用户
				{
					changeUser(sok);
				}
				else if (4 == choose)	//查询用户
				{
					printf("查询用户：\n");
					queryUser(sok);
					printf("查询用户结束\n");
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

				printf("\n请选择功能:");
				scanf("%d", &choose);
				
				if (choose == 1)		//修改权限
				{
					printf("修改权限：");
					changePermission(sok);
				}
				
				else if (2 == choose)	//查询权限
				{
					printf("查询权限：\n");
					queryPermission(sok);
					printf("查询用户结束\n");

				}
				else
				{
					exit(0);
				}
			}
			else
			{
				printf("请重新输入！\n");
			}
		}
	}
	else
	{
		printf("\n登录失败！");
		Sleep(2000);
		exit(0);
	}
}

////////////////////////////////用户管理//////////////////////////////////
                   
/************************************************************************/
/* 增加新用户                                                             */
/************************************************************************/
void addUser(SOCKET sockClient)
{
	SOCKET sok = sockClient;
	userMsg *pUserMsg = (userMsg *)calloc(1, sizeof(userMsg));
	char *allMsg = (char *)calloc(1024, sizeof(char));

	logM *pRe = (logM *)calloc(1, sizeof(logM));		
	//登陆之后服务器返回给客户端headflag[1]=1;给服务器发送增加的用户的信息

	logM *pFromServer = (logM *)calloc(1, sizeof(logM)); //临时变量，接受服务器返回的用户添加成功与否信息

	initUserALLMsgStruct(pUserMsg);

	pRe->headFlag[0] = 2;	//用户管理
	pRe->headFlag[1] = 1;	//增加用户的标志

	printf("\n\n\n\n       请输入用户名:");
	scanf("%s", pUserMsg->userName);
	strcat(allMsg, pUserMsg->userName);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       请输入电话:");
	scanf("%s", pUserMsg->del);
	strcat(allMsg, pUserMsg->del);
	strcat(allMsg, ":");
	system("cls");
	
	printf("\n\n\n\n       请输入邮箱:");
	scanf("%s", pUserMsg->mail);
	strcat(allMsg, pUserMsg->mail);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       请输入职位:");
	scanf("%s", pUserMsg->job);

	strcat(allMsg, pUserMsg->job);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       请输入创建者:");
	scanf("%s", pUserMsg->createPerson);

	strcat(allMsg, pUserMsg->createPerson);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       请输入创建时间:");
	scanf("%s", pUserMsg->createTime);

	strcat(allMsg, pUserMsg->createTime);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       请输入角色:");
	scanf("%s", pUserMsg->role);

	strcat(allMsg, pUserMsg->role);
	strcat(allMsg, ":");
	system("cls");

	printf("\n\n\n\n       请输入密码:");
	scanf("%s", pUserMsg->password);

	strcat(allMsg, pUserMsg->password);
	system("cls");

	strcpy(pRe->userMessage, allMsg);

	printf("\n发送用户信息确认\n增加用户标识：headFlag[1]:%d\n用户信息：%s\n", pRe->headFlag[1], pRe->userMessage);
	send(sockClient, (char *)pRe, sizeof(*pRe), 0);			//发送数据

	recv(sockClient, (char *)pFromServer, sizeof(*pFromServer), 0);			//接受服务器返回的数据
	printf("received server :%d %s\n", pFromServer->headFlag[1], pFromServer->userMessage);

	if (1 == pFromServer->headFlag[1])
	{
		printf("添加用户成功!\n");
	}
	else
	{
		printf("添加用户失败！请检查您的输入，重新添加！\n");
	}

	free(pUserMsg);
	free(allMsg);
	free(pRe);
	free(pFromServer);
}

/************************************************************************/
/* 删除用户                                                               */
/************************************************************************/
void deleteUser(SOCKET sockClient)
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和用户信息

	plogM->headFlag[0] = 2;
	plogM->headFlag[1] = 4;	
	plogM->headFlag[2] = 1;	//申请查询标志
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据

	if (1 == plogMRe->headFlag[2])
	{
		//删除用户具体操作
		//列出所有用户名
		listExistUserName(plogMRe);

		//输入要删除的用户名，列出该用户的详细信息
		char queryName[20] = { 0 };
		plogM->headFlag[1] = 2;
		memset(plogMRe, 0, sizeof(logM));

		printf("请输入要删除的用户名：");
		scanf("%s", queryName);
		strcpy(plogM->userMessage, queryName);

		send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据
		printf("\n发送用户名确认headFlag[1]:%d %s\n", plogM->headFlag[1], plogM->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
		printf("received server :%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		if (2 == plogMRe->headFlag[1])
		{
			printf("删除成功！\n");
		}
		else
		{
			printf("删除失败！请检查您的操作！\n");
		}

	}
	else
	{
		printf("请求失败！\n");
	}

	free(plogM);
	free(plogMRe);
}

/************************************************************************/
/* 修改用户                                                              */
/************************************************************************/
void changeUser(SOCKET sockClient)
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和用户信息

	userMsg *pUserMsg = (userMsg *)calloc(1, sizeof(userMsg)); //接受输入的修改信息
	char *allMsg = (char *)calloc(1024, sizeof(char));			//保存修改信息，

	plogM->headFlag[0] = 2;	//用户管理标志
	plogM->headFlag[1] = 4;	//查询标志
	plogM->headFlag[2] = 1;	//申请查询标志
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询数据

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据判断是否可查

	if (1 == plogMRe->headFlag[2])  //可以查询，列出用户名
	{
		//修改用户具体操作
		//列出所有用户名
		listExistUserName(plogMRe);

		//输入要修改的用户名，和修改信息
		char queryName[20] = { 0 };
		plogM->headFlag[1] = 3;
		memset(plogMRe, 0, sizeof(logM));

		//输入要修改的用户名
		printf("\n\n\n\n       请输入要修改的用户名:");
		scanf("%s", pUserMsg->userName);
		strcat(allMsg, pUserMsg->userName);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入电话:");
		scanf("%s", pUserMsg->del);
		strcat(allMsg, pUserMsg->del);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入邮箱:");
		scanf("%s", pUserMsg->mail);
		strcat(allMsg, pUserMsg->mail);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入职位:");
		scanf("%s", pUserMsg->job);

		strcat(allMsg, pUserMsg->job);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入创建者:");
		scanf("%s", pUserMsg->createPerson);

		strcat(allMsg, pUserMsg->createPerson);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入创建时间:");
		scanf("%s", pUserMsg->createTime);

		strcat(allMsg, pUserMsg->createTime);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入角色:");
		scanf("%s", pUserMsg->role);

		strcat(allMsg, pUserMsg->role);
		strcat(allMsg, ":");
		system("cls");

		printf("\n\n\n\n       请输入密码:");
		scanf("%s", pUserMsg->password);

		strcat(allMsg, pUserMsg->password);
		system("cls");

		strcpy(plogMRe->userMessage, allMsg);
		plogMRe->headFlag[0] = 2;
		plogMRe->headFlag[1] = 3;

		send(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);			//发送数据
		printf("\n发送用户名确认headFlag[1]:%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
		printf("received server :%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		if (3 == plogMRe->headFlag[1])
		{
			printf("修改成功！\n");
		}
		else
		{
			printf("修改失败！请检查您的操作！\n");
		}

	}
	else
	{
		printf("请求失败！\n");
	}

	free(plogM);
	free(plogMRe);
	free(pUserMsg);
	free(allMsg);
}

/************************************************************************/
/* 查询用户                                                              */
/************************************************************************/
void queryUser(SOCKET sockClient)
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和用户信息

	plogM->headFlag[0] = 2;	//用户管理标志
	plogM->headFlag[1] = 4;	//查询用户标识
	plogM->headFlag[2] = 1;	//申请查询标志
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据

	if (1 == plogMRe->headFlag[2])
	{
		//列出已存在所有用户名
		char *allUserName = plogMRe->userMessage;
		char *pAum = allUserName;
		char buf[20] = { 0 };

		printf("所有用户信息:\n");
		while (*allUserName != '\0')
		{
			if (*allUserName == ':')
			{
				strncpy(buf, pAum, allUserName - pAum);
				buf[allUserName - pAum] = '\0';
				printf("用户名： %s\n",buf);
				pAum = pAum + (allUserName - pAum) + 1;
			}
			allUserName++;
		}

		//输入要查询的用户名，列出该用户的详细信息
		char queryName[20] = { 0 };
		plogM->headFlag[2] = 2;
		memset(plogMRe, 0, sizeof(logM));

		printf("请输入要查询的用户名：");
		scanf("%s", queryName);
		strcpy(plogM->userMessage, queryName);

		send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据
		printf("\n发送用户名确认headFlag[2]:%d %s\n", plogM->headFlag[2], plogM->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
		printf("received server :%d %s\n", plogMRe->headFlag[2], plogMRe->userMessage);

		strcat(plogMRe->userMessage, ":");
		if (2 == plogMRe->headFlag[2])
		{
			char *oneUserMsg = plogMRe->userMessage;
			char *pOum = oneUserMsg;
			char buf[40] = { 0 };

			printf("用户信息详细信息:\n");
			while (*oneUserMsg != '\0')
			{
				if (*oneUserMsg == ':')
				{
					strncpy(buf, pOum, oneUserMsg - pOum);
					buf[oneUserMsg - pOum] = '\0';

					printf("该用户信息： %s\n", buf);
					pOum = pOum + (oneUserMsg - pOum) + 1;
				}
				oneUserMsg++;
			}
		}

	}
	else
	{
		printf("请求失败！\n");
	}

	free(plogM);
	free(plogMRe);
}

/************************************************************************/
/* 列出当前所有用户名                                                      */
/************************************************************************/
void listExistUserName(logM * plogM)
{
	//SOCKET soc = sockClient;
	//logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询的消息
	//logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和用户信息

	//plogM->headFlag[0] = 2;		//用户管理标志
	//plogM->headFlag[1] = 4;		//查询用户标识
	//plogM->headFlag[2] = 1;		//申请查询标志
	//send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据

	//recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
	logM * plogMRe = plogM;

	if (1 == plogMRe->headFlag[2])
	{
		//列出已存在所有用户名
		char *allUserName = plogMRe->userMessage;
		char *pAum = allUserName;
		char buf[20] = { 0 };

		printf("所有用户信息:\n");
		while (*allUserName != '\0')
		{
			if (*allUserName == ':')
			{

				strncpy(buf, pAum, allUserName - pAum);
				buf[allUserName - pAum] = '\0';
				printf("用户名： %s\n", buf);
				pAum = pAum + (allUserName - pAum) + 1;
			}
			allUserName++;
		}
	}
	else
	{
		printf("删除请求出错，不能列出所有用户名！\n");
	}
}

////////////////////////////////角色管理////////////////////////////////////




////////////////////////////////权限管理////////////////////////////////////
void changePermission(SOCKET sockClient)			//修改权限
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息

	if (!soc)
	{
		printf("socket error！");
	}
		
	char permissionNum[20] = { 0 };
	printf("系统所有权限列表:\n");
	listExistPermission();

	printf("请选择权限：(输入1为添加，输入其他值为不添加)\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%s", permissionMessg[i]);
		fflush(stdin);
		scanf("%c", permissionNum + i);
	}

	//如果用户输入100位的排错代码
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

	plogM->headFlag[0] = 4;	//权限管理标志
	plogM->headFlag[1] = 1;	//申请修改标志
	strcpy(plogM->userMessage, permissionNum);

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询数据

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("收到服务器传回的字符串：\n heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);
	if (1 == plogMRe->headFlag[1])
	{
		printf("修改成功！\n");
	}
	else
	{
		printf("修改失败！\n");
	}

	free(plogM);
	free(plogMRe);
}

void queryPermission(SOCKET sockClient)				//查询权限
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息


	if (!soc)
	{
		printf("socket error！");
	}
	plogM->headFlag[0] = 4;	//权限管理标志
	plogM->headFlag[1] = 2;	//申请查询标志

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询数据

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("收到服务器传回的字符串：heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);

	if (2 == plogMRe->headFlag[1])
	{
		//列出已存在所有权限
		char *pAp = plogMRe->userMessage;  //是0 1字符串
		int len = strlen(pAp);


		printf("所有权限信息:\n");
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
		printf("请求失败！\n");
	}

	free(plogM);
	free(plogMRe);

}
void listExistPermission()			//列出当前所有权限名
{

	for (int i = 0; i < 10; i++)
	{
		printf("%s\n", permissionMessg[i]);
	}
}