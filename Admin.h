#ifndef Admin_H
#define Admin_H
#pragma warning (disable:4996)


typedef struct Admin
{
	char Username[20];
	char Name[20];
	int JobNO;
	char Password[20];
}Admin;

typedef struct AdminLink
{
	char Username[20];
	char Name[20];
	int JobNO;
	char Password[20];
	struct AdminLink *next;
}AdminLink;

void Login();
int CheckUsername(char Username[20]);
void FindAccount();
void AlterAccount();
void DeleteAccount();
void ChangePassword();



#endif // !Admin_H