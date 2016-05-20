#include "Main.h"
#include "Book.h"
#include "Reader.h"
#include "Lend.h"
#include <time.h>

void LendBook()
{
	char Code[20];					//֤����
	char ISBN[50];
	Reader R;
	BookList B;
	LendInfo L;
	int i;
	char LendDate[20] ;				//��������
	char LastDate[20];				//Ӧ������
	int BookNum=0;

	time_t   t ;					//time_tʱ������
	t= time(NULL);

	strftime(LendDate,sizeof(LendDate),"%Y-%m-%d",localtime(&t));



	t +=MAX_DAY_LEND*86400;			//24*60*60  ��90���Ӧ������

	strftime(LastDate,sizeof(LastDate),"%Y-%m-%d",localtime(&t));


	printf("-------------------ͼ�����,��#����-------------------\n\n");
	printf("������֤���ţ�");
	scanf("%s",Code);

	R=FindReaderL(Code);

	printf("%s\t%s\t%s\t%s\t%d\n\n",R.Code,R.Name,R.Sex,R.Dept,R.Tag);
	BookNum=LendBookNum(R.Code);

	if (R.Tag==1)
		printf("֤���ѹ�ʧ����ֹ���ģ�");

	else  if(BookNum>=4)
		printf("�Ѿ�����4���������ٽ裡");

	else  		
	{
		printf("������ISBN��");
		scanf("%s",ISBN); 

		while(strcmp(ISBN,"#")!=0 && BookNum<MAX_BOOK_LEND)
		{

			B=CreatBookList(  ) ;
			B=BubbleSort(B);  
			i=BinSearchISBN(B,ISBN) ;
			if(i==0)
			{
				printf("\n\nû���ҵ�ͼ�飡");
				break;
			}
			else
			{

				//���ļ�¼
				strcpy(L.Code,R.Code);
				strcpy(L.ISBN, ISBN);
				strcpy(L.LendDate,LendDate);
				strcpy(L.ReturnDate,"NULL");
				strcpy(L.LastDate,LastDate);
				L.Tag=0;

				printf("%s\t%s\t%s\t%s\t%s\t���\n\n",L.ISBN,B.Node[i].Title,B.Node[i].Author,L.LendDate,L.LastDate);

				SaveLendInfo(L);
				BookNum++;
				printf("������ISBN��");
				scanf("%s",ISBN);

			}
		}
		if(BookNum>=4)
			printf("�Ѿ�����4���������ٽ裡");
	}

	printf("\n������ϣ�\n");



}

Reader FindReaderL(char Code[])
{
	Reader R;
	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s\t%s\t%s\t%s\t%d\n",R.Code,R.Name,R.Sex,R.Dept,&R.Tag);
		if (strcmp(R.Code,Code)==0)
		{
			return R;
			break;
		}
	}

	printf("û���ҵ�����!\n");
	fclose(fp);

	return (R);
}


int LendBookNum(char Code[20])
{
	LendInfo L;
	int BookNum=0;

	if((fp=fopen("lend.txt","r"))==NULL)
	{
		printf("�ļ��򿪴���!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%d\n",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,&L.Tag);
		if (strcmp(L.Code,Code)==0 && L.Tag==0)       
		{
			BookNum++;

		}		

	}                

	fclose(fp);
	return BookNum;
}


void SaveLendInfo(LendInfo L)
{  


	if((fp=fopen("lend.txt","a+"))==NULL)
	{
		printf("�ļ���ʧ��!\n");
		exit(0);
	}

	fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%d\n",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,L.Tag);
	//��������Ϣд���ļ� 
	fclose(fp);            

	getchar();
}

void ReturnBook( ) 
{
	char Code[20];  //֤����
	char ISBN[50];
	BookList B;
	LendInfoLink *head,*p;
	char ReturnDate[20];  //�黹����
	int i; 
	time_t   t ;

	//���㻹������
	t= time(NULL);

	strftime(ReturnDate,sizeof(ReturnDate),"%Y-%m-%d",localtime(&t));

	head=CreatLendLink();


	printf("-------------------����,��#����-------------------\n\n");
	printf("������֤���ţ�");
	scanf("%s",Code);


	printf("������ISBN��");
	scanf("%s",ISBN);

	while(strcmp(ISBN,"#")!=0 )
	{

		B=CreatBookList(  ) ;
		B=BubbleSort(B);  
		i=BinSearchISBN(B,ISBN) ;


		p=head->next;
		while( p!=NULL )
		{
			if (strcmp(p->Code,Code)==0 && strcmp(p->ISBN,ISBN)==0)
				break;
			else
				p=p->next;
		}

		strcpy(p->ReturnDate,ReturnDate);
		p->Tag=1;


		printf("%s\t%s\t%s\t%s\t%s\t�ѻ�\n\n",p->ISBN,B.Node[i].Title,B.Node[i].Author,p->LendDate,p->ReturnDate);

		printf("������ISBN��");
		scanf("%s",ISBN);
	}
	SaveLendInfoW(head);
	printf("\n������ϣ�\n");

}


LendInfoLink* CreatLendLink()
{
	char Code[20];				//֤����
	char ISBN[50];
	char LendDate[20] ;			//��������
	char LastDate[20];			//Ӧ������
	char ReturnDate[20];		//�黹����
	int Tag;					//״̬0;�����1���黹

	LendInfoLink* head,*p,*q;
	if((fp=fopen("lend.txt","r"))==NULL) 
	{
		printf("File open error!\n");
		exit(0);
	}

	head=(LendInfoLink *)malloc(sizeof(LendInfoLink));
	q=head;	

	fscanf(fp,"%[^\t]",Code);  
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",ISBN);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",LendDate);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",LastDate);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",ReturnDate);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%d",&Tag);   
	fscanf(fp,"%*c"); 


	while(!feof(fp))   
	{

		p=(LendInfoLink *)malloc(sizeof(LendInfoLink));
		strcpy(p->Code,Code);
		strcpy(p->ISBN,ISBN);

		strcpy(p->LendDate,LendDate);
		strcpy(p->LastDate,LastDate);	
		strcpy(p->ReturnDate,ReturnDate);
		p->Tag=Tag;


		q->next=p;
		q=p;

		fscanf(fp,"%[^\t]",Code);  //�ȶ������ж�feof(fp)����ֹ�ļ�β���һ������
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",ISBN);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",LendDate);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",LastDate);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",ReturnDate);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%d",&Tag);   //int
		fscanf(fp,"%*c"); 


	}
	p->next=NULL;
	fclose(fp);


	return head;
}

void SaveLendInfoW(LendInfoLink *head)
{
	LendInfoLink *p;
	if((fp=fopen("lend.txt","w"))==NULL)
	{
		printf("�ļ��򲻿�!\n");
		exit(0);
	}
	for( p=head->next; p!=NULL; p=p->next )    
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%d\n",p->Code,p->ISBN,p->LendDate,p->LastDate,p->ReturnDate,p->Tag);
	fclose(fp);           

	printf("\nͼ����Ϣ�ѳɹ����浽�ļ� lend.txt �У�\n");
	getchar( );
}


void FindLendInfo( ) 
{
	char Code[20];		//֤����
	int i;				//ͼ��������
	LendInfo L;
	BookList B;
	B=CreatBookList(  ) ;
	B=BubbleSort(B);  
    printf("\n----------------------------------------------------\n\n");
	printf("����Ҫ��ѯ���ߵ�code��");
	scanf("%s",Code);
	printf("\n\n");
	
	if((fp=fopen("lend.txt","r"))==NULL)
	{
		printf("�ļ��򲻿�!\n");
		exit(0);
	}
	
	while(strcmp(Code,"#")!=0)
	{
		rewind(fp);								//��λfp���ļ���ͷ��feofֵ�ָ�Ϊ0
		fscanf(fp,"%s %s %s %s %s %d",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,&L.Tag);

		while(!feof(fp))
		{
			if (strcmp(L.Code,Code)==0)			//�ҵ����ļ�¼
			{
				i=BinSearchISBN(B,L.ISBN) ;		//����ͼ����Ϣ

				if(L.Tag==0)
					printf("%s\t%s\t%s\t%s\t%s\t%s\t���\n\n",L.ISBN,B.Node[i].Title,B.Node[i].Author,L.LendDate,L.LastDate,L.ReturnDate);
				else
					printf("%s\t%s\t%s\t%s\t%s\t%s\t�ѻ�\n\n",L.ISBN,B.Node[i].Title,B.Node[i].Author,L.LendDate,L.LastDate,L.ReturnDate);

			}

			fscanf(fp,"%s %s %s %s %s %d",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,&L.Tag);

		}
		printf("\n----------------------------------------------------\n\n");
		printf("����Ҫ��ѯ���ߵ�code��");
		scanf("%s",Code);
		printf("\n\n");
	}
	fclose(fp);
}