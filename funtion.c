
//12346

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
	SOCKET sockClient;			//客户端Socket
	SOCKADDR_IN addrServer;		//服务端地址
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sockClient = socket(AF_INET, SOCK_STREAM, 0);	//新建客户端socket

	//定义要连接的服务端地址
	addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.53"); 
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(10002);		//连接端口10002

	//连接到服务端
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));

	return sockClient;
}

/************************************************************************/
/* 遍历用户信息判断非字母非数字                                                                     */
/************************************************************************/
int travUserMesg(char *userMessage)    //遍历用户信息
{
	if (userMessage == NULL)
	{
		printf("用户信息指针为空！\n");
		
		return -1;
	}

	while (*userMessage != '\0')							//遍历用户名
	{
		if (isalpha(*userMessage) || isdigit(*userMessage)) //判断字母和数字
		{
			userMessage++;
		}
		else
		{
			//system("cls");
			printf("用户信息仅限于纯数字、纯字母或两者组合!");
			return -1;
		}
	}
	return 1;
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
*初始化给服务发送消息的结构体
********************************************************************/
void initStruct(logM * plogM)
{
	memset(plogM->headFlag, 0, sizeof(plogM->headFlag));
	memset(plogM->userMessage, 0, sizeof(plogM->userMessage));
}
/************************************************************************/
/* 初始化用户所有信息结构体                                                                     */
/************************************************************************/
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
/* 处理服务器返回的headflag信息，根据返回消息确认处理方法                              */
/************************************************************************/
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient)
{
	logM *pSend = receiveServerMsg;
	SOCKET sok = sockClient;

	if (1 == pSend->headFlag[0])  //判断服务器传回消息
	{
		system("cls");
		//system("color 5d");
		printf("\n\n\n\n               登录成功……");
		Sleep(2000);
		system("cls");

		int choose = -1;       //登陆成功之后调用系统管理菜单的所有功能
		while (choose)			//循环用户选择 1.用户管理  2.角色管理  3.权限管理 
		{
			manageMenu();
			fflush(stdin);
			printf("\n------------------------------------------------------------------------\n");
			printf("请选择功能:");
			scanf("%d", &choose);
			if (getchar() != '\n')
			{
				printf("------------------------------------------------------------------------\n");
				printf("请重新输入下列选项编号：\n");
				continue;
			}
			system("cls");
			if (choose == 1)		//用户管理
			{
				userManage(sok);
			}
		
			else if (2 == choose)   //角色管理
			{
				roleManage(sok);
			}

			else if (3 == choose)
			{
				permissionManage(sok);
			}
			else if (0 != choose)
			{
				printf("------------------------------------------------------------------------\n");
				printf("请重新输入下列选项编号：\n");
			}
			}
		}
	else  //服务器传回消息失败
	{
		printf("------------------------------------------------------------------------\n");
		printf("\n登录失败！");
		Sleep(2000);
		exit(0);
	}
}


////////////////////////////////用户管理//////////////////////////////////
void addUser(SOCKET sockClient)
{
	SOCKET sok = sockClient;
	userMsg *pUserMsg = (userMsg *)calloc(1, sizeof(userMsg));
	char *allMsg = (char *)calloc(1024, sizeof(char));

	logM *pRe = (logM *)calloc(1, sizeof(logM));		
	//登陆之后服务器返回给客户端headflag[1]=1;给服务器发送增加的用户的信息

	logM *pFromServer = (logM *)calloc(1, sizeof(logM)); //临时变量，接受服务器返回的用户添加成功与否信息

	char *pum = NULL;
	initUserALLMsgStruct(pUserMsg);

	pRe->headFlag[0] = 2;	//用户管理
	pRe->headFlag[1] = 1;	//增加用户的标志
	while (1)
	{
		printf("\n------------------------------------------------------------------------");
		printf("\n       请输入用户名:");
		scanf("%s", pUserMsg->userName);
		pum = pUserMsg->userName;
		if (1 == travUserMesg(pum))
		{
			strcat(allMsg, pUserMsg->userName);
			strcat(allMsg, ":");
			break;
		}
		else
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("输入格式不对，请重新输入：\n");
		}
		
		system("cls");
	}
	int index;
	while (1)
	{
		printf("\n       请输入电话:");
		scanf("%s", pUserMsg->del);
		if (strlen(pUserMsg->del) == 11)
		{
			for (index = 0; index < 11; index++)
			{
				if (isdigit(pUserMsg->del[index]))
				{
					;
				}
				else
				{
					break;
				}
			}
			if (index == 11)
			{
				strcat(allMsg, pUserMsg->del);
				strcat(allMsg, ":");
				break;
			}
			else
			{
				printf("输入格式不对，请重新输入：\n");
			}
		}
		else
		{
			printf("输入格式不对，请重新输入：\n");
		}
		
		system("cls");
	}
	
	while (1)
	{
		printf("\n       请输入邮箱:");
		scanf("%s", pUserMsg->mail);
		char *p = strstr(pUserMsg->mail, "@");
		if (p)
		{
			char *tmp = pUserMsg->mail + strlen(pUserMsg->mail) - 4;
			if (strncmp(tmp, ".com", 4) == 0)
			{
				strcat(allMsg, pUserMsg->mail);
				strcat(allMsg, ":");
				break;
			}
		}
		else
		{
			printf("输入格式不对，请重新输入：\n");
		}
		system("cls");
	}
	while (1)
	{
		printf("\n       请输入职位:");
		scanf("%s", pUserMsg->job);
		int length = strlen(pUserMsg->job);
		if (length > 0 && length < 20)
		{
			for (index = 0; index < length; index++)
			{
				if (!isalpha(pUserMsg->job[index]))
				{
					break;
				}
			}
			if (index == length)
			{
				strcat(allMsg, pUserMsg->job);
				strcat(allMsg, ":");
				break;
			}
		}
		else
		{
			printf("输入格式不对，请重新输入：\n");
		}
		
		system("cls");
	}
	

	printf("\n       请输入创建者:");
	scanf("%s", pUserMsg->createPerson);

	strcat(allMsg, pUserMsg->createPerson);
	strcat(allMsg, ":");
	system("cls");

	printf("\n       请输入创建时间:");
	scanf("%s", pUserMsg->createTime);

	strcat(allMsg, pUserMsg->createTime);
	strcat(allMsg, ":");
	system("cls");

	listExistRole(sok);
	printf("\n       请输入角色:");
	fflush(stdin);
	scanf("%s", pUserMsg->role);

	strcat(allMsg, pUserMsg->role);
	strcat(allMsg, ":");
	system("cls");

	printf("\n        请输入密码:");
	scanf("%s", pUserMsg->password);
	pum = pUserMsg->password;
	travUserMesg(pum);
	strcat(allMsg, pUserMsg->password);
	system("cls");

	strcpy(pRe->userMessage, allMsg);

	//printf("\n发送用户信息确认\n增加用户标识：headFlag[1]:%d\n用户信息：%s\n", pRe->headFlag[1], pRe->userMessage);
	send(sockClient, (char *)pRe, sizeof(*pRe), 0);			//发送数据

	recv(sockClient, (char *)pFromServer, sizeof(*pFromServer), 0);			//接受服务器返回的数据
	//printf("received server :%d %s\n", pFromServer->headFlag[1], pFromServer->userMessage);

	if (1 == pFromServer->headFlag[1])
	{
		printf("\n\n------------------------------------------------------------------------\n");
		printf("--添加用户成功!回车键返回菜单\n");
		getchar();
		getchar();
		system("cls");
	}
	else
	{
		printf("\n\n------------------------------------------------------------------------\n");
		printf("■--添加用户失败！请检查您的输入，重新添加！\n回车键返回菜单。");
		getchar();
		getchar();
		system("cls");
	}

	free(pUserMsg);
	free(allMsg);
	free(pRe);
	free(pFromServer);
}
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
		printf("------------------------------------------------------------------------\n");
		printf("\t\t\t  **** 用户管理系统 ****\n");
		printf("------------------------------------------------------------------------\n");
		printf("\t----用户管理\n");
		printf("\t-------删除用户\n");
		printf("------------------------------------------------------------------------\n\n");

		listExistUserName(plogMRe);
		//输入要删除的用户名，列出该用户的详细信息
		char queryName[20] = { 0 };
		plogM->headFlag[1] = 2;
		memset(plogMRe, 0, sizeof(logM));

		printf("\n------------------------------------------------------------------------\n");
		printf("请输入要删除的用户名：");
		scanf("%s", queryName);
		strcpy(plogM->userMessage, queryName);

		send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据
		//printf("\n发送用户名确认headFlag[1]:%d %s\n", plogM->headFlag[1], plogM->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
		//printf("received server :%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		if (2 == plogMRe->headFlag[1])
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("删除成功！回车键返回菜单\n");
			getchar();
			getchar();
			system("cls");
		}
		else
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("删除失败！请检查您的操作！回车键返回菜单\n\n");
			getchar();
			getchar();
			system("cls");
		}

	}
	else
	{
		printf("\n------------------------------------------------------------------------\n");
		printf("请求失败！回车键返回菜单。\n");
		getchar();
		getchar();
		system("cls");
	}

	free(plogM);
	free(plogMRe);
}
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
		printf("------------------------------------------------------------------------\n");
		printf("\t\t\t  **** 用户管理系统 ****\n");
		printf("------------------------------------------------------------------------\n");
		printf("\t----用户管理\n");
		printf("\t-------修改用户\n");
		printf("------------------------------------------------------------------------\n\n");
		listExistUserName(plogMRe);
		printf("\n\n------------------------------------------------------------------------\n");
		//输入要修改的用户名，和修改信息
		char queryName[20] = { 0 };
		plogM->headFlag[1] = 3;
		//memset(plogMRe, 0, sizeof(logM));

		//输入要修改的用户名
		printf("\n       请输入要修改的用户名:");
		scanf("%s", pUserMsg->userName);
		strcat(allMsg, pUserMsg->userName);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入电话:");
		scanf("%s", pUserMsg->del);
		strcat(allMsg, pUserMsg->del);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入邮箱:");
		scanf("%s", pUserMsg->mail);
		strcat(allMsg, pUserMsg->mail);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入职位:");
		scanf("%s", pUserMsg->job);

		strcat(allMsg, pUserMsg->job);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入创建者:");
		scanf("%s", pUserMsg->createPerson);

		strcat(allMsg, pUserMsg->createPerson);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入创建时间:");
		scanf("%s", pUserMsg->createTime);

		strcat(allMsg, pUserMsg->createTime);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入角色:");
		scanf("%s", pUserMsg->role);

		strcat(allMsg, pUserMsg->role);
		strcat(allMsg, ":");
		system("cls");

		printf("\n       请输入密码:");
		scanf("%s", pUserMsg->password);

		strcat(allMsg, pUserMsg->password);
		system("cls");

		strcpy(plogMRe->userMessage, allMsg);
		plogMRe->headFlag[0] = 2;
		plogMRe->headFlag[1] = 3;

		send(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);			//发送数据
		//printf("\n发送用户名确认headFlag[1]:%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
		//printf("received server :%d %s\n", plogMRe->headFlag[1], plogMRe->userMessage);

		if (3 == plogMRe->headFlag[1])
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("修改成功！\n");
		}
		else
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("修改失败！请检查您的操作！\n");
		}

	}
	else
	{
		printf("\n------------------------------------------------------------------------\n");
		printf("请求失败！\n");
	}

	free(plogM);
	free(plogMRe);
	free(pUserMsg);
	free(allMsg);
}
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
		printf("------------------------------------------------------------------------\n");
		printf("\t\t\t  **** 用户管理系统 ****\n");
		printf("------------------------------------------------------------------------\n");
		printf("\t----用户管理\n");
		printf("\t-------查询用户\n");
		printf("------------------------------------------------------------------------\n\n");
		printf("\n\n------------------------------------------------------------------------\n");
		printf("所有用户信息:\n");
		while (*allUserName != '\0')
		{
			if (*allUserName == ':')
			{
				strncpy(buf, pAum, allUserName - pAum);
				buf[allUserName - pAum] = '\0';
				printf("\t用户名： %s\n",buf);
				pAum = pAum + (allUserName - pAum) + 1;
			}
			allUserName++;
		}

		//输入要查询的用户名，列出该用户的详细信息
		char queryName[20] = { 0 };
		plogM->headFlag[2] = 2;
		memset(plogMRe, 0, sizeof(logM));

		printf("\n\n------------------------------------------------------------------------\n");
		printf("请输入要查询的用户名：");
		scanf("%s", queryName);
		strcpy(plogM->userMessage, queryName);
		system("cls");
		send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据
		//printf("\n发送用户名确认headFlag[2]:%d %s\n", plogM->headFlag[2], plogM->userMessage);

		recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
		//printf("received server :%d %s\n", plogMRe->headFlag[2], plogMRe->userMessage);

		strcat(plogMRe->userMessage, ":");
		system("cls");
		if (2 == plogMRe->headFlag[2])
		{
			char *oneUserMsg = plogMRe->userMessage;
			char *pOum = oneUserMsg;
			char buf[40] = { 0 };

			printf("\n------------------------------------------------------------------------\n");
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
		printf("\n\n------------------------------------------------------------------------\n");
		printf("请求失败！\n");
		getchar();
		getchar();
		system("cls");
	}

	free(plogM);
	free(plogMRe);
}
void listExistUserName(logM * plogM)
{
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
void addRole(SOCKET sockClient)				//增加角色、
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息

	char roleName[100] = { 0 };		//暂存角色名称
	char roleNameAndPermission[1024] = { 0 };   //暂存要发给服务器的信息
	char buf[10] = { 0 };

	if (!soc)
	{
		printf("socket error！");
	}

	plogM->headFlag[0] = 3;
	plogM->headFlag[1] = 1;

	printf("\n请输入角色名称：");
	scanf("%s", roleName);
	strcat(roleNameAndPermission, roleName);
	strcat(roleNameAndPermission, ":");
	fflush(stdin);

	printf("\n请选择要给所添加的角色赋予的权限：");
	printf("\n输入1表示赋予该权限，0表示不赋予该权限！\n");

	printf("1.增加用户:");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("2.删除用户");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("3.修改用户");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("4.查询用户");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("5.增加角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("6.删除角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("7.修改角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("8.查询角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("9.修改权限");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);
 
	printf("10.查询权限");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	strcpy(plogM->userMessage, roleNameAndPermission);
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询数据
	printf("\n增加角色确认发送：\n heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("收到服务器传回的字符串：\n heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);
	
	if (1 == plogMRe->headFlag[1])
	{
		printf("\n角色添加成功！");
	}
	else
	{
		printf("\n角色添加失败！");
	}

	free(plogM);
	free(plogMRe);
}
void deleteRole(SOCKET sockClient)			//删除角色
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息
	char roleName[100] = { 0 };

	if (!soc)
	{
		printf("socket error！");
	}

	plogM->headFlag[0] = 3;
	plogM->headFlag[1] = 2;

	listExistRole(soc);
	printf("\n请输入要删除的角色名称：");
	scanf("%s", roleName);
	strcat(plogM->userMessage, roleName);

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询数据
	printf("\n删除角色确认：\n heafFlag[1]=%d   %s", plogMRe->headFlag[1], plogMRe->userMessage);

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("\n服务器传回：\n heafFlag[1]=%d   %s", plogMRe->headFlag[1], plogMRe->userMessage);

	if (2 == plogMRe->headFlag[1])
	{
		printf("\n删除成功！\n");
	}
	else
	{
		printf("\n删除失败！\n");
	}
}
void changeRole(SOCKET sockClient)			//修改角色
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息

	char roleName[100] = { 0 };		//暂存角色名称
	char roleNameAndPermission[1024] = { 0 };   //暂存要发给服务器的信息
	char buf[10] = { 0 };
	listExistRole(soc);

	//输入要修改的角色名
	char changeName[200] = { 0 };

	plogM->headFlag[0] = 3;
	plogM->headFlag[1] = 3;
	memset(plogMRe, 0, sizeof(logM));

	printf("\n请输入要修改的角色名称：");
	scanf("%s", roleName);
	strcat(roleNameAndPermission, roleName);
	strcat(roleNameAndPermission, ":");
	fflush(stdin);

	printf("\n请重新赋予该角色权限。\n");
	printf("\n输入1表示赋予该权限，0表示不赋予该权限！\n");

	printf("1.增加用户:");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("2.删除用户");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("3.修改用户");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("4.查询用户");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("5.增加角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("6.删除角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("7.修改角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("8.查询角色");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("9.修改权限");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	printf("10.查询权限");
	scanf("%s", buf);
	strcat(roleNameAndPermission, buf);

	strcpy(plogM->userMessage, roleNameAndPermission);
	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询数据
	printf("\n增加角色确认发送：\n heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	printf("收到服务器传回的字符串：\n heafFlag[1]=%d %s", plogMRe->headFlag[1], plogMRe->userMessage);

	if (3 == plogMRe->headFlag[1])
	{
		printf("\n角色修改成功！\n");
	}
	else
	{
		printf("\n角色修改失败！\n");
	}

	free(plogM);
	free(plogMRe);
}
void queryRole(SOCKET sockClient)			//查询角色
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息

	listExistRole(soc);
		
	//输入要查询的角色名，列出该用户的详细信息
	char queryName[200] = { 0 };

	plogM->headFlag[0] = 3;
	plogM->headFlag[1] = 4;
	plogM->headFlag[2] = 2;
	memset(plogMRe, 0, sizeof(logM));

	printf("请输入要查询的角色名：");
	scanf("%s", queryName);
	strcpy(plogM->userMessage, queryName);

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送数据
	printf("\n发送用户名确认headFlag[2]:%d %s\n", plogM->headFlag[2], plogM->userMessage);

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);		//接受服务器返回的数据
	printf("received server :%d %s\n", plogMRe->headFlag[2], plogMRe->userMessage);

	strcat(plogMRe->userMessage, ":");
	if (2 == plogMRe->headFlag[2])
	{
		char *oneRolePermission = plogMRe->userMessage;

		printf("角色详细信息:\n");
		for (int i = 0; oneRolePermission[i] != ':'; i++)
		{
			if (oneRolePermission[i] == '1')
			{
				printf("%s\n", permissionMessg[i]);
			}	
		}
	}
	else
	{
		printf("\n查询失败！\n");
	}

	
	free(plogM);
	free(plogMRe);
}
void listExistRole(SOCKET sockClient)		//列出当前所有角色名
{
	SOCKET soc = sockClient;
	logM *plogM = (logM *)calloc(1, sizeof(logM));		//发送向服务其请求查询权限的消息
	logM *plogMRe = (logM *)calloc(1, sizeof(logM));	//接受服务器回传的状态信息和权限信息

	if (!soc)
	{
		printf("socket error！");
	}
	plogM->headFlag[0] = 3;
	plogM->headFlag[1] = 4;
	plogM->headFlag[2] = 1;

	send(sockClient, (char *)plogM, sizeof(*plogM), 0);			//发送请求查询角色
	//printf("\n增加角色送确认：\n heafFlag[1]=%d\n", plogMRe->headFlag[2]);

	recv(sockClient, (char *)plogMRe, sizeof(*plogMRe), 0);
	//printf("\n服务器传回：\n heafFlag[1]=%d\n", plogMRe->headFlag[2]);

	if (1 == plogMRe->headFlag[2])			//请求查询角色成功
	{
		//列出已存在所有角色名称
		char *allRoleName = plogMRe->userMessage;
		char *pArn = allRoleName;
		char buf[20] = { 0 };		//暂存角色一条名称

		//printf("所有角色信息:\n");
		while (*allRoleName != '\0')
		{
			if (*allRoleName == ':')
			{
				strncpy(buf, pArn, allRoleName - pArn);
				buf[allRoleName - pArn] = '\0';
				printf("角色名： %s\n", buf);
				//memset(buf, 0, sizeof(buf));
				pArn = pArn + (allRoleName - pArn) + 1;
			}
			allRoleName++;
		}
	}
	else
	{
		printf("\n请求查询角色信息失败！");
	}

	free(plogM);
	free(plogMRe);
}

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

//////////////////////////////////////////////////////////////////////////////
void judgePasswd(char *password)
{
	char c;
	int a = 0;
	for (int i = 0; i < 100; i++)
	{
		c = _getch();
		if (c == 13)
		{
			break;
		}
		if ((c <= 90 && c >= 65) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		{
			printf("*");
			password[i] = c;
		}
		while (c == 8 && i >= 0)
		{
			printf("\b \b");
			i--;
			c = _getch();
			a++;
		}
		while (a == 1)
		{
			c = _getch();
			if ((c <= 90 && c >= 65) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
				password[i] = c;
			a--;
		}
	}
}

void userManage(SOCKET sockClient)
{
	SOCKET sok = sockClient;

	int chooseU = -1;
	while (chooseU)		//循环用户管理 的4个选项
	{
		userManageMenu();
		printf("\n------------------------------------------------------------------------");
		printf("\n请选择功能:");
		scanf("%d", &chooseU);

		if (getchar() != '\n')  //排除1A  的输入
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("请重新输入下列选项编号：\n");
			continue;
		}
		system("cls");
		if (chooseU == 1)		//增加用户
		{
			printf("\n------------------------------------------------------------------------\n");
			printf("需要填写的信息如下：\n");
			userAllMessageMenu();
			addUser(sok);
		}
		else if (2 == chooseU)	//删除用户
		{
			deleteUser(sok);
		}
		else if (3 == chooseU)	//修改用户
		{
			changeUser(sok);
		}
		else if (4 == chooseU)	//查询用户
		{
			//printf("\n------------------------------------------------------------------------");
			//printf("\n查询用户：\n");
			queryUser(sok);
			printf("\n\n------------------------------------------------------------------------");
			printf("\n查询用户结束!\n按回车键回到菜单。\n");
			getchar();
			getchar();
			system("cls");
		}
		else if (0 != chooseU)
		{
			printf("\n------------------------------------------------------------------------");
			printf("\n您的输入有误！请重新输入：\n");

		}
	}
}
void roleManage(SOCKET sockClient)
{
	SOCKET sok = sockClient;
	int chooseR = -1;
	fflush(stdin);
	while (chooseR)
	{
		printf("角色管理菜单：\n");
		roleManageMenu();
		printf("\n请选择功能:");
		scanf("%d", &chooseR);

		if (getchar() != '\n')  //排除1A  的输入
		{
			printf("请重新输入下列选项编号：\n");
			continue;
		}

		if (chooseR == 1)		//增加角色
		{
			printf("\n需要填写的信息如下：");
			addRole(sok);
		}
		else if (2 == chooseR)	//删除角色
		{
			deleteRole(sok);
		}
		else if (3 == chooseR)	//修改角色
		{
			changeRole(sok);
		}
		else if (4 == chooseR)	//查询角色
		{
			queryRole(sok);
		}
		else if (0 != chooseR)
		{
			printf("您的输入有误！请重新输入：\n");

		}
	}
}
void permissionManage(SOCKET sockClient)
{
	SOCKET sok = sockClient;
	int chooseP = -1;

	while (chooseP)
	{
		printf("权限管理菜单：\n");
		permissionManageMenu();
		fflush(stdin);

		printf("\n请选择功能:");
		scanf("%d", &chooseP);

		if (chooseP == 1)		//修改权限
		{
			printf("修改权限：");
			changePermission(sok);
		}

		else if (2 == chooseP)	//查询权限
		{
			printf("查询权限：\n");
			queryPermission(sok);
			printf("查询用户结束\n");

		}
		else if (0 != chooseP)
		{
			printf("您的输入有误！请重新输入：\n");
		}
	}

}
