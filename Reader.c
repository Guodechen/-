#include "Main.h"
#include "Reader.h"

void BrowseReader(  ) 
{
	char Code[20];  //֤����
	char Name[30];  //����
	char Sex[5];  
	char Dept[50];//������λ
	int  Tag; 



	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}
	printf("\n\n---------------------------------------------------\n");
	printf("֤����           ����        �Ա�     ��λ    \n");
	printf("\n---------------------------------------------------\n");


	fscanf(fp,"%s %s %s %s %d",Code,Name,Sex,Dept,&Tag);   //�ȶ����������ֹ���һ��������
	while(!feof(fp))
	{
		printf(" %s\t%s\t%s\t%s\t\n",Code,Name,Sex,Dept);     
		fscanf(fp,"%s %s %s %s %d",Code,Name,Sex,Dept,&Tag);
	}


	if(fclose(fp))
	{
		printf("���ܹر��ļ�!\n");
		exit(0);
	}
}



ReaderLink * InputReader( )
{
	ReaderLink *p ,*q,*head;       
	char Code[20];
	int n=0,x;


	printf("\n\n---------------------------------------------------\n");
	printf("֤���ţ��������Ա�(F,M)����λ����ʧ״̬��0,1������#����\n");
	printf("\n-----------------------------------------------------\n");


	head=(ReaderLink *)malloc(sizeof(ReaderLink));
	p=head;

	scanf("%s",Code);
	while(1)
	{  
	if(strcmp(Code,"#") == 0)
		break;       
		else

		{
			q=(ReaderLink *)malloc(sizeof(ReaderLink));
			strcpy(q->Code,Code);

			scanf("%s %s %s %d",q->Name,q->Sex,q->Dept,&q->Tag);
			p->next=q;
			p=q;
		}

		scanf("%s",Code);
	} 
	q->next=NULL;
	printf("������Ϣ���������\n");	
	getchar();                       
	printf("�Ƿ񱣴������Ϣ����1.��/2.�񣩣�");
	scanf("%d",&x);
	if(x==1)
		SaveReader(head);                /*���ú����������ļ�*/
	else
		printf("\n�ļ�û�б����棡\n");
	return head;                    /*����ͷָ��*/
}


void  SaveReader(ReaderLink *head)

{  

	ReaderLink *p;
	if((fp=fopen("reader.txt","a"))==NULL)
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}

	for(p=head->next ; p!=NULL ; p=p->next)    
		fprintf(fp,"%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept,p->Tag);
													//��ͼ����Ϣд���ļ� 
	fclose(fp);            


	printf("\nͼ����Ϣ�ѳɹ����浽�ļ� reader.txt �У�\n");
	getchar();
}



void FindReader_Code()
{
	char Code[20]; 
	Reader R;
	int flag=0;  //�ҵ�Ϊ1��û�ҵ�Ϊ0

	printf("\n����Ҫ��ѯ���ߵ�֤���ţ�");
	scanf("%s",Code);

	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %s %d",R.Code,R.Name,R.Sex,R.Dept,&R.Tag);//��һ����¼
		if (strcmp(R.Code,Code)==0)       //�Ƚ�
		{
			printf("\n%s\t%s\t%s\t%s\t%d\n",R.Code,R.Name,R.Sex,R.Dept,R.Tag);
			flag=1;
			break;
		}		
			
	}
	if (flag==0)
		printf("û���ҵ����߼�¼!\n");

	getchar();                       

	fclose(fp);
}


void FindReader_Name()
{
	char Name[30]; 
	Reader R;
	int flag=0; //�ҵ�Ϊ1��û�ҵ�Ϊ0

	printf("\n����Ҫ��ѯ���ߵ�������");
	scanf("%s",Name);

	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}
	 
	while(!feof(fp))
	{
			fscanf(fp,"%s %s %s %s %d",R.Code,R.Name,R.Sex,R.Dept,&R.Tag);
			
			if (strcmp(R.Name,Name)==0)
		{
			printf("\n%s\t%s\t%s\t%s\t%d\n",R.Code,R.Name,R.Sex,R.Dept,R.Tag);
			flag=1;  //�ҵ��޸ı��
			break;

		}		

	}
	if (flag==0)
		printf("û���ҵ����߼�¼!\n");

	fclose(fp);


}


void AlterReader(  )
{
	char Code[20];  
	ReaderLink *head,*p;
	head=CreatReaderLink( ); 


	printf("����Ҫ�޸ĵĶ��ߵ�֤���ţ�  ");
	scanf("%s",Code);

	//�������в��Ҷ���

	p=head->next;
	for(p; p!=NULL&&strcmp(p->Code,Code)!=0; p=p->next);

	printf("�ҵ�Ҫ�޸ĵĶ��ߣ�  ");
	printf("%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept,p->Tag);


	printf("��������µ���Ϣ��֤���ţ��������Ա𣬹�����λ��״̬��\n");
	scanf("%s %s %s %s %d",p->Code,p->Name,p->Sex,p->Dept,&p->Tag);

	printf( "%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept, p->Tag);

	SaveReaderW( head);

	printf("�޸ĳɹ���");

}


ReaderLink *CreatReaderLink(  )

{
	ReaderLink *head,*p,*q;
	if((fp=fopen("reader.txt","r"))==NULL) 
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}

	head=(ReaderLink *)malloc(sizeof(ReaderLink));
	p=head;	
	while(!feof(fp))   
	{

		q=(ReaderLink *)malloc(sizeof(ReaderLink));
		fscanf(fp,"%s\t%s\t%s\t%s\t%d\n",q->Code,q->Name,q->Sex,q->Dept,&q->Tag);

		p->next=q;
		p=q;

	}
	p->next=NULL;

	fclose(fp);

	return head;
}



void  SaveReaderW(ReaderLink *head)

{  

	ReaderLink *p;
	if((fp=fopen("reader.txt","w"))==NULL)
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}
	for( p=head->next; p!=NULL; p=p->next )    
		fprintf(fp,"%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept,p->Tag);

	fclose(fp);           


	printf("\n������Ϣ�ѳɹ����浽�ļ� reader.txt �У�\n");
	getchar( );
}



void LostReader(  )
{
	char Code[20];			//֤����
	ReaderLink *head,*p;
	head=CreatReaderLink( ); //��������

	printf("�����ʧ֤���ţ�  ");
	scanf("%s",Code);

	p=head->next;
	for(p; p!=NULL&&strcmp(p->Code,Code)!=0; p=p->next);

	printf("\n�ҵ�Ҫ��ʧ�Ķ��ߣ�  ");
	printf("%s\t%s\t%s\t%s\n",p->Code,p->Name,p->Sex,p->Dept);

	p->Tag=1;

	SaveReaderW(head);

	printf("\n��ʧ�ɹ���\n\n");

}