#ifndef _MYSQL_H_
#define _MYSQL_H_

#include <iostream>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

#define MAX_SQL_LEN   (4096)
#define SUM_SQL_LEN   (200*(MAX_SQL_LEN))
using namespace std;
class Mysql{
public:
	Mysql();
	~Mysql();

	int add_user(char user_info[8][512]);
	int select_user_store(char* sql,char *user_info);
	
	int delete_user(char *name);
		
	int select_users_name(char **p);
	int select_user(char* acnt,char* user_info = NULL);
	
	int update_user(char user_info[8][512]);
	int update_privilege(char *str);
	int select_privilege(char *str);
	int add_role(char *role,char *privi);
	int delete_role(char *role);
	int update_role(char *role,char *privi);
	int select_role(char *role,char *privi = NULL);
	int select_role_store(char *sql,char *role_info);
	int select_roles_name(char **p);
	int selectUserPrivilege(const char *name, char *body);
		
	#if 0	
	bool add_privi(char *role,char *privi);
	bool del_privi(char *role,char *privi);
	bool select_privi(char *role,char *privi);
	
	int select_user_store(char* sql,char ***user_info);
	#endif
	int mysql_real_query1(char *sql);
private:
	MYSQL_RES *result;
	MYSQL *conn;
	MYSQL_ROW row;
};

#endif
