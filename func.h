#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>

#include<winsock2.h>				//socket()相关头文件
#pragma comment(lib, "ws2_32.lib")  //socket()相关库

struct LOGMessage		//向服务器发送用户信息结构体
{
	char  headFlag[4];
	char  userMessage[1024];    //用户名和密码
};
typedef struct LOGMessage logM;

//用户名 电话 邮箱 工作 创建者 创建时间  角色 密码
struct USERMessage		//用户信息本地缓存结构体
{
	char userName[20];
	char del[20];
	char mail[20];
	char job[20];
	char createPerson[20];
	char createTime[20];
	char role[20];
	char password[20];
};
typedef struct USERMessage userMsg;
char userInfo[40];
char *permissionMessg[10];

/******一级菜单******/
void logMenu();			//欢迎界面
logM *logToSystem();	//用户的录到系统

/******二级菜单******/
void manageMenu();				//管理菜单

/******三级菜单******/
void userManageMenu();			//用户管理菜单
void roleManageMenu();			//角色管理菜单
void permissionManageMenu();	//权限管理菜单

/******四级级菜单******/
void userAllMessageMenu();

/***************************************************************************/
//功能函数区
int travUserMesg(char *userMessage);				//遍历用户信息
void initStruct(logM * plogM);						//初始化用户登录信息结构体
SOCKET  connectToServer();							//连接到服务器
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//处理服务器返回值信息

//用户管理函数
logM *listExistUserName(SOCKET sockClient);
void addUser(SOCKET sockClient);
void deleteUser(SOCKET sockClient);
void changeUser(SOCKET sockClient);
void queryUser(SOCKET sockClient);


//角色管理函数
void addRole(SOCKET sockClient);			//增加角色、
void deleteRole(SOCKET sockClient);			//删除角色
void changeRole(SOCKET sockClient);			//修改角色
void queryRole(SOCKET sockClient);			//查询角色
logM* listExistRole(SOCKET sockClient);		//列出当前所有角色名


//权限管理函数
void changePermission(SOCKET sockClient);			//修改权限
void queryPermission(SOCKET sockClient);			//查询权限
void listExistPermission();		//列出当前所有权限名


void judgePasswd(char *password);
void userManage(SOCKET sockClient);
void roleManage(SOCKET sockClient);
void permissionManage(SOCKET sockClient);

void getSystemTime(char *str);
int getNameOrRoleInput(char *str, char *msg);

//12346
