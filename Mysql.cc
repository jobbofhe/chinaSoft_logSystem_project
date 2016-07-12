#include "Mysql.h"


int  Mysql::select_user_store(char *sql,char *user_info)
{	

	int reta = mysql_real_query1(sql);
	if ( 0 != reta){
		return (-1);
	}
	//process result  
	result = mysql_store_result(conn);  
	if (result == NULL){  
		if (mysql_error(conn))  
			fprintf(stderr, "%s\n", mysql_error(conn));  
		else  
			fprintf(stderr, "%s\n", "unknown error\n");  
		return -1;  
	}  

	row = mysql_fetch_row(result);
	if (!row)
	{
		cout << "the user you selected not exist!" << endl;
		return -2;
	}

	if (user_info == NULL)
	{
		return 0;
	}
	sprintf(user_info, "%s:%s:%s:%s:%s:%s:%s:%s", row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7]);

	return (0);
}	

Mysql::Mysql():result(NULL),conn(NULL),row(NULL)
{
	//create connection to MySQL  
	conn = mysql_init(NULL);  
	if (mysql_real_connect(conn, "localhost", "root", "qiaominghe", "zhong_soft", 0, NULL, 0) == NULL){  
		fprintf(stderr, "Sorry, no database connection ...\n");
		mysql_query(conn, "SET NAMES 'utf8'");  
		printf("daole\n");
	}
}

Mysql::~Mysql()
{
	//release memory, server connection  
	if (result)
	{
		mysql_free_result(result);  
	}
	mysql_close(conn);  
}



int Mysql::add_user(char user_info[8][512])
{
	char sql[MAX_SQL_LEN];
	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"insert into usrs(name,tel,mail,work,creater,create_time,privilege,passwd) values('%s','%s','%s','%s','%s','%s','%s','%s')",user_info[0],user_info[1],user_info[2],user_info[3],user_info[4],user_info[5],user_info[6],user_info[7]);

	return mysql_real_query1(sql); 
}

int Mysql::delete_user(char *name)
{
	char sql[MAX_SQL_LEN];
	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"delete from usrs where name = '%s'",name);

	return mysql_real_query1(sql);
}

int Mysql::select_users_name(char **p)
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"select name from usrs");
	int ret = mysql_real_query1(sql);
	if (ret != 0)
		return -1;

	result = mysql_store_result(conn);
	unsigned int num = mysql_field_count(conn);
	unsigned int count = mysql_num_rows(result);
	cout << "users name count:" << count << endl;
	char *buffer = new char[count * 8];
	bzero(buffer, count * 8);
	while (row = mysql_fetch_row(result))
	{
		for (unsigned int i = 0; i < num; i++)
		{
			strcat(buffer, row[i]);
			strcat(buffer, ":");
		}
	}
	*p = buffer;

	return 0;
}
int Mysql::select_user(char* acnt,char *user_info)
{
	if (NULL == acnt){	//如果输入acnt为NULL,则返回为-1
		return (-1);
	}

	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"select * from usrs where name = '%s'",acnt);
	cout << sql << endl;

	return	select_user_store(sql, user_info);
}


int Mysql::update_user(char user_info[8][512])
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"update usrs set name = '%s',tel = '%s',mail='%s',work = '%s',privilege = '%s',passwd = '%s'where name = '%s'",user_info[0],user_info[1],user_info[2],user_info[3],user_info[4],user_info[5], user_info[0]);
	printf("update usrs set name = '%s',tel = '%s',mail='%s',work = '%s',creater = '%s',create_time = '%s',role = '%s',passwd = '%s'\n",user_info[0],user_info[1],user_info[2],user_info[3],user_info[4],user_info[5],user_info[6],user_info[7]);

	return mysql_real_query1(sql);	
}

int Mysql::update_privilege(char *str)
{
	char sql[MAX_SQL_LEN];
	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"update privilege set id1 = '%c',id2='%c',id3 = '%c',id4 = '%c',id5 = '%c',id6 = '%c',id7 = '%c', id8 = '%c', id9 = '%c', id10 = '%c' where name = 'system'",str[0],str[1],str[2],str[3],str[4],str[5],str[6],str[7], str[8], str[9]);

	if (mysql_real_query1(sql))
	{
		return -1;
	}

	for (int i = 1; i <= 10; i++)
	{
		if (str[i-1] == '0')
		{
			bzero(sql,MAX_SQL_LEN);
			sprintf(sql, "update privilege set id%d = 0", i);
			cout << sql << endl;
			if (mysql_real_query1(sql))
			{
				return -1;
			}
		}
	}
	return 0;
}
int Mysql::select_privilege(char *str)
{
	char sql[MAX_SQL_LEN];
	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"select * from privilege where name = 'system'");

	if (mysql_real_query1(sql))
	{
		return -1;
	}
	result = mysql_store_result(conn);
	row = mysql_fetch_row(result);
	if (row == NULL)
	{
		return -1;
	}
	unsigned int num = mysql_field_count(conn);
	for (unsigned int i = 0; i < num-1; i++)
	{
		strcat(str, row[i]);
	}
	return 0;
}

int Mysql::mysql_real_query1(char *sql)
{
	if (mysql_query(conn,sql)){
		fprintf(stderr,"%s\n\n",mysql_error(conn));
		fprintf(stderr,"%s\n",sql);

		return  (-1);
	}

	return (0);
}
int Mysql::add_role(char *role,char *role_info)
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"insert into privilege(id1,id2,id3,id4,id5,id6,id7,id8,id9,id10,name) values('%c','%c','%c','%c','%c','%c','%c','%c','%c','%c','%s')",role_info[0],role_info[1],role_info[2],role_info[3],role_info[4],role_info[5],role_info[6],role_info[7],role_info[8],role_info[9], role);

	return mysql_real_query1(sql);	
}
int Mysql::delete_role(char *role)
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"delete from privilege where name= '%s'",role);

	return mysql_real_query1(sql);
}
int Mysql::update_role(char *role,char *role_info)
{
	char sql[MAX_SQL_LEN];	
	bzero(sql,MAX_SQL_LEN);

	sprintf(sql,"update privilege set id1 = '%c',id2 = '%c',id3 = '%c',id4 = '%c',id5 = '%c',id6 = '%c',id7 ='%c',id8 = '%c',id9 = '%c',id10 = '%c' where name = '%s'",role_info[0],role_info[1],role_info[2],role_info[3],role_info[4],role_info[5],role_info[6],role_info[7],role_info[8],role_info[9], role);

	return mysql_real_query1(sql);
}
int Mysql::select_role(char *role,char *role_info)
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"select * from privilege where name = '%s'",role);

	return select_role_store(sql,role_info);
}
int Mysql::select_role_store(char *sql,char *role_info)
{ 	
	if ( -1 == mysql_real_query1(sql))
	{
		return (-1);
	}
	//process result  
	result = mysql_store_result(conn);  
	if (result == NULL)
	{  
		if (mysql_error(conn))  
			fprintf(stderr, "%s\n", mysql_error(conn));  
		fprintf(stderr, "%s\n", "unknown error\n");  
		return -1;  
	}  
	if (row = mysql_fetch_row(result))
	{
		if (NULL == role_info)
		{
			return (0);
		}else {
			sprintf(role_info,"%s%s%s%s%s%s%s%s%s%s%s:%s",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10]);
			return 0;
		}
	}
	else
		return -2;
	return (0);
}	
int Mysql::select_roles_name(char **p)
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"select name from privilege");
	int ret = mysql_real_query1(sql);
	if (ret != 0)
		return -1;

	result = mysql_store_result(conn);
	unsigned int num = mysql_field_count(conn);
	unsigned int count = mysql_num_rows(result);
	cout << "roles name count:" << count << endl;
	char *buffer = new char[count * 8];
	bzero(buffer, count * 8);
	while (row = mysql_fetch_row(result))
	{
		for (unsigned int i = 0; i < num; i++)
		{
			strcat(buffer, row[i]);
			strcat(buffer, ":");
		}
	}
	*p = buffer;

	return 0;
}

int Mysql::selectUserPrivilege(const char *name, char *body)
{
	char sql[MAX_SQL_LEN];

	bzero(sql,MAX_SQL_LEN);
	sprintf(sql,"select privilege.id1, privilege.id2, privilege.id3, privilege.id4, privilege.id5, privilege.id6, privilege.id7, privilege.id8, privilege.id9, privilege.id10, usrs.name from usrs, privilege where usrs.name = '%s' and usrs.privilege = privilege.name", name);

	cout << sql << endl;
	int ret = mysql_real_query1(sql);
	if (ret != 0)
		return -1;
	result = mysql_store_result(conn);
	if (row = mysql_fetch_row(result))
	{
		for (int i = 0; i < 11; i++)
		{
			strcat(body, row[i]);
		}
		cout << body << endl;
		return 0;
	}
	else
		return -2;
}
