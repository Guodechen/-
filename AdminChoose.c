#include"Admin.h"

void AdminChoose()
{
	int MenuNum;

	printf("ÇëÊäÈëÄãµÄÑ¡Ôñ£¡0-5 £º ");
	scanf("%d", &MenuNum);

	switch (MenuNum)
	{
	case 1:
		Login();
		break;
	case 2:
		DeleteAccount();
		break;
	case 3:
		AlterAccount();
		break;
	case 4:
		FindAccount();
		break;
	case 5:
		ChangePassword();
		break;
	case 0:
		break;
	}
}