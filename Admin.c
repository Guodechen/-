#include "Main.h"
#include "Catalog.h"
#include "Admin.h"

void Login()
{
	Admin A;
	FILE *fp;
	char  Password1 [20];
	char  Password2 [20];
	int wy; //0唯一，1不唯一

	if((fp=fopen("Admin.dat","ab"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		printf("请输入管理员信息。当输入用户名#结束：\n");
		printf("用户名：");
		scanf("%s",A.Username );
		while(strcmp(A.Username,"#")!=0)
		{
			wy=CheckUsername(A.Username);//检查用户名唯一性
			if(wy==1)
				printf("用户名已有，重新输入！");
			else
			{
				printf("姓名：");
				scanf("%s",A.Name );

				printf("工号：");
				scanf("%d",&A.JobNO );

				printf("密码：");
				scanf("%s",Password1 );

				printf("再次输入密码：");
				scanf("%s",Password2 );
				if(strcmp(Password1,Password2)==0)
				{
					strcpy(A.Password,Password1);

					fwrite(&A,sizeof(Admin),1,fp);
					printf("注册成功！\n");
				}
				else 
					printf("两次密码不相同！请重新输入！\n");

				printf("用户名：");
				scanf("%s",A.Username );	

			}//while
		}
	}
	fclose(fp);

}

int CheckUsername(char Username[20])
{
	int wy; //0唯一，1不唯一
	Admin A;
	FILE *fp;

	if((fp=fopen("Admin.dat","rb"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&A, sizeof(Admin),1,fp);

		while(!feof(fp))
		{

			if(strcmp(A.Username ,Username)==0)
			{	
				printf("账户名已存在，重新输入。\n\n");
				wy=1;
				break;
			}
			fread(&A, sizeof(Admin),1,fp);			
		}
	}
	fclose(fp);
	return wy;
}

//查询账户
void FindAccount( )
{
	Admin A;
	char Username[20];
	int num=0;//记录个数
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" 输入查询用户名： ");
	scanf(" %s",Username);

	if((fp=fopen("Admin.dat","rb"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&A, sizeof(Admin),1,fp);

		while(!feof(fp)) 
		{

			if(strcmp(A.Username ,Username)==0)
			{	
				printf(" %s\t%s\t%d\n\n",A.Username,A.Name,A.JobNO );
				break;
			}

			fread(&A, sizeof(Admin),1,fp);			
		}
	}
	fclose(fp);
}

//修改账户
void AlterAccount(  )
{
	Admin A;
	char Username[20];
	int num=0;//记录个数
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" 输入要修改的用户名： ");
	scanf("%s",A.Username);

	if((fp=fopen("Admin.dat","rb+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&A, sizeof(Admin),1,fp);

		while(!feof(fp))
		{			
			if(strcmp(A.Username ,Username)==0)
			{	
				printf(" %s\t%s\t%d\n\n",A.Username,A.Name,A.JobNO );
				break;
			}			
			fread(&A, sizeof(Admin),1,fp);
			num++;
		}
	}

	printf(" 输入更改后的账户信息。 \n\n");
	printf("用户名：");
	scanf("%s",A.Username );
	printf("姓名：");
	scanf("%s",A.Name );			
	printf("工号：");
	scanf("%d",&A.JobNO );	

	fseek(fp,num*sizeof(Admin),SEEK_SET);  
	fwrite(&A,sizeof(Admin),1,fp);
	printf(" 修改成功！\n\n");
	fclose(fp);			

}					


//删除账户
void DeleteAccount()
{
	Admin A;
	char Username[20];
	int num=0;//记录个数
	Admin  blankAdmin={"NULL","NULL","NULL","NULL"};
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" 输入要删除账户的用户名： ");
	scanf("%s",Username);	
	if((fp=fopen("Admin.dat","rb+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&A, sizeof(Admin),1,fp);

		while(!feof(fp))
		{			
			if(strcmp(A.Username ,Username)==0)
			{	
				printf(" 要删除的账户信息：\n\n");
				printf(" %s\t%s\t%d\n\n",A.Username,A.Name,A.JobNO );
				break;
			}			
			fread(&A, sizeof(Admin),1,fp);
			num++;
		}
	}	
	fseek(fp,num*sizeof(Admin),SEEK_SET);  
	fwrite(&blankAdmin,sizeof(Admin),1,fp);
	printf(" 删除成功！\n\n");
	fclose(fp);			 

}

//修改密码
void ChangePassword()
{
	Admin A;
	char Username[20];
	int num=0;//记录个数
	int Find=0; //1输入成功,0失败
	char Password1[20] = {"NULL"}, Password2[20] = { "NULL" };
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" 输入要修改密码的用户名： ");
	scanf("%s",Username);

	if((fp=fopen("Admin.dat","rb+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&A, sizeof(Admin),1,fp);

		while(!feof(fp))
		{			
			if(strcmp(A.Username ,Username)==0)
			{	
				printf(" %s\t%s\t%d\n\n",A.Username,A.Name,A.JobNO );
				break;
			}			
			fread(&A, sizeof(Admin),1,fp);
			num++;
		}
	}

	do{
		printf("输入新密码：");
		scanf("%s",Password1 );

		printf("再次输入新密码：");
		scanf("%s",Password2 );
		if(strcmp(Password1,Password2)==0)
		{
			strcpy(A.Password,Password1);
			Find=1;
		}
		else 
			printf("两次密码不相同！请重新输入！\n");
	}while(Find=0);			

	fseek(fp,num*sizeof(Admin),SEEK_SET);  
	fwrite(&A,sizeof(Admin),1,fp);
	printf(" 密码修改成功！\n\n");
	fclose(fp);	  
}