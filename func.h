//123
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <time.h>

#include<winsock2.h>				//socket()�����
#pragma comment(lib, "ws2_32.lib")  //socket()���

struct LOGMessage		//�������������
{
	char  headFlag[4];
<<<<<<< HEAD
	char  userMessage[1024];    //�û���������
};
typedef struct LOGMessage logM;

//�û��� �绰 ���� ���� ������ ����ʱ��  ��ɫ ����
struct USERMessage		//�û���Ϣ���ػ���ṹ��
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

/******һ���˵�******/
void logMenu();			//��ӭ����
logM *logToSystem();	//�û���¼��ϵͳ

/******�����˵�******/
void manageMenu();				//����˵�

/******�����˵�******/
void userManageMenu();			//�û�����˵�
void roleManageMenu();			//��ɫ����˵�
void permissionManageMenu();	//Ȩ�޹���˵�

/******�ļ����˵�******/
void userAllMessageMenu();

/***************************************************************************/
//���ܺ�����
int travUserMesg(char *userMessage);				//�����û���Ϣ
void initStruct(logM * plogM);						//��ʼ���û���¼��Ϣ�ṹ��
SOCKET  connectToServer();							//���ӵ�������
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//�������������ֵ��Ϣ

//�û�������
logM *listExistUserName(SOCKET sockClient);
void addUser(SOCKET sockClient);
void deleteUser(SOCKET sockClient);
void changeUser(SOCKET sockClient);
void queryUser(SOCKET sockClient);


//��ɫ������
void addRole(SOCKET sockClient);			//���ӽ�ɫ��
void deleteRole(SOCKET sockClient);			//ɾ����ɫ
void changeRole(SOCKET sockClient);			//�޸Ľ�ɫ
void queryRole(SOCKET sockClient);			//��ѯ��ɫ
logM* listExistRole(SOCKET sockClient);		//�г���ǰ���н�ɫ��


//Ȩ�޹�����
void changePermission(SOCKET sockClient);			//�޸�Ȩ��
void queryPermission(SOCKET sockClient);			//��ѯȨ��
void listExistPermission();		//�г���ǰ����Ȩ����


void judgePasswd(char *password);
void userManage(SOCKET sockClient);
void roleManage(SOCKET sockClient);
void permissionManage(SOCKET sockClient);

void getSystemTime(char *str);
int getNameOrRoleInput(char *str, char *msg);

//12346
=======
		char  userMessage[1024];    //������
		};
		typedef struct LOGMessage logM;

		//��� �� �� �� ��� ����  �� ��
		struct USERMessage		//�����������
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

										/******����******/
										void logMenu();			//����
										logM *logToSystem();	//�������

										/******����******/
										void manageMenu();				//����

										/******����******/
										void userManageMenu();			//������
										void roleManageMenu();			//������
										void permissionManageMenu();	//������

										/******�����******/
										void userAllMessageMenu();

										/***************************************************************************/
										//�����
										int travUserMesg(char *userMessage);				//������
										void initStruct(logM * plogM);						//������������
										SOCKET  connectToServer();							//������
										void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//����������

										//������
										logM *listExistUserName(SOCKET sockClient);
										void addUser(SOCKET sockClient);
										void deleteUser(SOCKET sockClient);
										void changeUser(SOCKET sockClient);
										void queryUser(SOCKET sockClient);


										//������
										void addRole(SOCKET sockClient);			//�����
										void deleteRole(SOCKET sockClient);			//����
										void changeRole(SOCKET sockClient);			//����
										void queryRole(SOCKET sockClient);			//����
										logM* listExistRole(SOCKET sockClient);		//���������


										//������
										void changePermission(SOCKET sockClient);			//����
										void queryPermission(SOCKET sockClient);			//����
										void listExistPermission();		//���������


										void judgePasswd(char *password);
										void userManage(SOCKET sockClient);
										void roleManage(SOCKET sockClient);
										void permissionManage(SOCKET sockClient);

										void getSystemTime(char *str);
										int getNameOrRoleInput(char *str, char *msg);
>>>>>>> dev
