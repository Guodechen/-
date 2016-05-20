#include "Main.h"
#include "Catalog.h"
#include "Admin.h"

void Login()
{
	Admin A;
	FILE *fp;
	char  Password1 [20];
	char  Password2 [20];
	int wy; //0Ψһ��1��Ψһ

	if((fp=fopen("Admin.dat","ab"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		printf("���������Ա��Ϣ���������û���#������\n");
		printf("�û�����");
		scanf("%s",A.Username );
		while(strcmp(A.Username,"#")!=0)
		{
			wy=CheckUsername(A.Username);//����û���Ψһ��
			if(wy==1)
				printf("�û������У��������룡");
			else
			{
				printf("������");
				scanf("%s",A.Name );

				printf("���ţ�");
				scanf("%d",&A.JobNO );

				printf("���룺");
				scanf("%s",Password1 );

				printf("�ٴ��������룺");
				scanf("%s",Password2 );
				if(strcmp(Password1,Password2)==0)
				{
					strcpy(A.Password,Password1);

					fwrite(&A,sizeof(Admin),1,fp);
					printf("ע��ɹ���\n");
				}
				else 
					printf("�������벻��ͬ�����������룡\n");

				printf("�û�����");
				scanf("%s",A.Username );	

			}//while
		}
	}
	fclose(fp);

}

int CheckUsername(char Username[20])
{
	int wy; //0Ψһ��1��Ψһ
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
				printf("�˻����Ѵ��ڣ��������롣\n\n");
				wy=1;
				break;
			}
			fread(&A, sizeof(Admin),1,fp);			
		}
	}
	fclose(fp);
	return wy;
}

//��ѯ�˻�
void FindAccount( )
{
	Admin A;
	char Username[20];
	int num=0;//��¼����
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" �����ѯ�û����� ");
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

//�޸��˻�
void AlterAccount(  )
{
	Admin A;
	char Username[20];
	int num=0;//��¼����
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" ����Ҫ�޸ĵ��û����� ");
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

	printf(" ������ĺ���˻���Ϣ�� \n\n");
	printf("�û�����");
	scanf("%s",A.Username );
	printf("������");
	scanf("%s",A.Name );			
	printf("���ţ�");
	scanf("%d",&A.JobNO );	

	fseek(fp,num*sizeof(Admin),SEEK_SET);  
	fwrite(&A,sizeof(Admin),1,fp);
	printf(" �޸ĳɹ���\n\n");
	fclose(fp);			

}					


//ɾ���˻�
void DeleteAccount()
{
	Admin A;
	char Username[20];
	int num=0;//��¼����
	Admin  blankAdmin={"NULL","NULL","NULL","NULL"};
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" ����Ҫɾ���˻����û����� ");
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
				printf(" Ҫɾ�����˻���Ϣ��\n\n");
				printf(" %s\t%s\t%d\n\n",A.Username,A.Name,A.JobNO );
				break;
			}			
			fread(&A, sizeof(Admin),1,fp);
			num++;
		}
	}	
	fseek(fp,num*sizeof(Admin),SEEK_SET);  
	fwrite(&blankAdmin,sizeof(Admin),1,fp);
	printf(" ɾ���ɹ���\n\n");
	fclose(fp);			 

}

//�޸�����
void ChangePassword()
{
	Admin A;
	char Username[20];
	int num=0;//��¼����
	int Find=0; //1����ɹ�,0ʧ��
	char Password1[20] = {"NULL"}, Password2[20] = { "NULL" };
	FILE *fp;

	printf("  -------------------------\n\n ");
	printf(" ����Ҫ�޸�������û����� ");
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
		printf("���������룺");
		scanf("%s",Password1 );

		printf("�ٴ����������룺");
		scanf("%s",Password2 );
		if(strcmp(Password1,Password2)==0)
		{
			strcpy(A.Password,Password1);
			Find=1;
		}
		else 
			printf("�������벻��ͬ�����������룡\n");
	}while(Find=0);			

	fseek(fp,num*sizeof(Admin),SEEK_SET);  
	fwrite(&A,sizeof(Admin),1,fp);
	printf(" �����޸ĳɹ���\n\n");
	fclose(fp);	  
}