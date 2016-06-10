//123
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>

#include<winsock2.h>				//socket()¿¿¿¿¿
#pragma comment(lib, "ws2_32.lib")  //socket()¿¿¿

struct LOGMessage		//¿¿¿¿¿¿¿¿¿¿¿¿¿
{
	char  headFlag[4];
<<<<<<< HEAD
	char  userMessage[1024];    //ÓÃ»§ÃûºÍÃÜÂë
};
typedef struct LOGMessage logM;

//ÓÃ»§Ãû µç»° ÓÊÏä ¹¤×÷ ´´½¨Õß ´´½¨Ê±¼ä  ½ÇÉ« ÃÜÂë
struct USERMessage		//ÓÃ»§ÐÅÏ¢±¾µØ»º´æ½á¹¹Ìå
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

/******Ò»¼¶²Ëµ¥******/
void logMenu();			//»¶Ó­½çÃæ
logM *logToSystem();	//ÓÃ»§µÄÂ¼µ½ÏµÍ³

/******¶þ¼¶²Ëµ¥******/
void manageMenu();				//¹ÜÀí²Ëµ¥

/******Èý¼¶²Ëµ¥******/
void userManageMenu();			//ÓÃ»§¹ÜÀí²Ëµ¥
void roleManageMenu();			//½ÇÉ«¹ÜÀí²Ëµ¥
void permissionManageMenu();	//È¨ÏÞ¹ÜÀí²Ëµ¥

/******ËÄ¼¶¼¶²Ëµ¥******/
void userAllMessageMenu();

/***************************************************************************/
//¹¦ÄÜº¯ÊýÇø
int travUserMesg(char *userMessage);				//±éÀúÓÃ»§ÐÅÏ¢
void initStruct(logM * plogM);						//³õÊ¼»¯ÓÃ»§µÇÂ¼ÐÅÏ¢½á¹¹Ìå
SOCKET  connectToServer();							//Á¬½Óµ½·þÎñÆ÷
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//´¦Àí·þÎñÆ÷·µ»ØÖµÐÅÏ¢

//ÓÃ»§¹ÜÀíº¯Êý
logM *listExistUserName(SOCKET sockClient);
void addUser(SOCKET sockClient);
void deleteUser(SOCKET sockClient);
void changeUser(SOCKET sockClient);
void queryUser(SOCKET sockClient);


//½ÇÉ«¹ÜÀíº¯Êý
void addRole(SOCKET sockClient);			//Ôö¼Ó½ÇÉ«¡¢
void deleteRole(SOCKET sockClient);			//É¾³ý½ÇÉ«
void changeRole(SOCKET sockClient);			//ÐÞ¸Ä½ÇÉ«
void queryRole(SOCKET sockClient);			//²éÑ¯½ÇÉ«
logM* listExistRole(SOCKET sockClient);		//ÁÐ³öµ±Ç°ËùÓÐ½ÇÉ«Ãû


//È¨ÏÞ¹ÜÀíº¯Êý
void changePermission(SOCKET sockClient);			//ÐÞ¸ÄÈ¨ÏÞ
void queryPermission(SOCKET sockClient);			//²éÑ¯È¨ÏÞ
void listExistPermission();		//ÁÐ³öµ±Ç°ËùÓÐÈ¨ÏÞÃû


void judgePasswd(char *password);
void userManage(SOCKET sockClient);
void roleManage(SOCKET sockClient);
void permissionManage(SOCKET sockClient);

void getSystemTime(char *str);
int getNameOrRoleInput(char *str, char *msg);

//12346
=======
		char  userMessage[1024];    //¿¿¿¿¿¿
		};
		typedef struct LOGMessage logM;

		//¿¿¿ ¿¿ ¿¿ ¿¿ ¿¿¿ ¿¿¿¿  ¿¿ ¿¿
		struct USERMessage		//¿¿¿¿¿¿¿¿¿¿¿
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

										/******¿¿¿¿******/
										void logMenu();			//¿¿¿¿
										logM *logToSystem();	//¿¿¿¿¿¿¿

										/******¿¿¿¿******/
										void manageMenu();				//¿¿¿¿

										/******¿¿¿¿******/
										void userManageMenu();			//¿¿¿¿¿¿
										void roleManageMenu();			//¿¿¿¿¿¿
										void permissionManageMenu();	//¿¿¿¿¿¿

										/******¿¿¿¿¿******/
										void userAllMessageMenu();

										/***************************************************************************/
										//¿¿¿¿¿
										int travUserMesg(char *userMessage);				//¿¿¿¿¿¿
										void initStruct(logM * plogM);						//¿¿¿¿¿¿¿¿¿¿¿¿
										SOCKET  connectToServer();							//¿¿¿¿¿¿
										void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//¿¿¿¿¿¿¿¿¿¿

										//¿¿¿¿¿¿
										logM *listExistUserName(SOCKET sockClient);
										void addUser(SOCKET sockClient);
										void deleteUser(SOCKET sockClient);
										void changeUser(SOCKET sockClient);
										void queryUser(SOCKET sockClient);


										//¿¿¿¿¿¿
										void addRole(SOCKET sockClient);			//¿¿¿¿¿
										void deleteRole(SOCKET sockClient);			//¿¿¿¿
										void changeRole(SOCKET sockClient);			//¿¿¿¿
										void queryRole(SOCKET sockClient);			//¿¿¿¿
										logM* listExistRole(SOCKET sockClient);		//¿¿¿¿¿¿¿¿¿


										//¿¿¿¿¿¿
										void changePermission(SOCKET sockClient);			//¿¿¿¿
										void queryPermission(SOCKET sockClient);			//¿¿¿¿
										void listExistPermission();		//¿¿¿¿¿¿¿¿¿


										void judgePasswd(char *password);
										void userManage(SOCKET sockClient);
										void roleManage(SOCKET sockClient);
										void permissionManage(SOCKET sockClient);

										void getSystemTime(char *str);
										int getNameOrRoleInput(char *str, char *msg);
>>>>>>> dev
