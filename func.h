#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

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
/***************************************************************************/

//功能函数区
void travUserMesg(char *userMessage);				//遍历用户信息
void initStruct(logM * plogM);						//初始化用户登录信息结构体
SOCKET  connectToServer();							//连接到服务器
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//处理服务器返回值信息

void lisAlreadytExistUser();
void listExistUserName(logM * plogM);

void addUser(SOCKET sockClient);
void deleteUser(SOCKET sockClient);
void changeUser(SOCKET sockClient);
void queryUser(SOCKET sockClient);
