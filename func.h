#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#include<winsock2.h>				//socket()���ͷ�ļ�
#pragma comment(lib, "ws2_32.lib")  //socket()��ؿ�

struct LOGMessage		//������������û���Ϣ�ṹ��
{
	char  headFlag[4];
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
/***************************************************************************/

//���ܺ�����
void travUserMesg(char *userMessage);				//�����û���Ϣ
void initStruct(logM * plogM);						//��ʼ���û���¼��Ϣ�ṹ��
SOCKET  connectToServer();							//���ӵ�������
void processServerReMsg(logM *receiveServerMsg, SOCKET sockClient);		//�������������ֵ��Ϣ

void lisAlreadytExistUser();
void listExistUserName(logM * plogM);

void addUser(SOCKET sockClient);
void deleteUser(SOCKET sockClient);
void changeUser(SOCKET sockClient);
void queryUser(SOCKET sockClient);
