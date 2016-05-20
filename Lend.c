#include "Main.h"
#include "Book.h"
#include "Reader.h"
#include "Lend.h"
#include <time.h>

void LendBook()
{
	char Code[20];					//证件号
	char ISBN[50];
	Reader R;
	BookList B;
	LendInfo L;
	int i;
	char LendDate[20] ;				//借书日期
	char LastDate[20];				//应还日期
	int BookNum=0;

	time_t   t ;					//time_t时间类型
	t= time(NULL);

	strftime(LendDate,sizeof(LendDate),"%Y-%m-%d",localtime(&t));



	t +=MAX_DAY_LEND*86400;			//24*60*60  ，90天后应还日期

	strftime(LastDate,sizeof(LastDate),"%Y-%m-%d",localtime(&t));


	printf("-------------------图书借阅,按#结束-------------------\n\n");
	printf("请输入证件号：");
	scanf("%s",Code);

	R=FindReaderL(Code);

	printf("%s\t%s\t%s\t%s\t%d\n\n",R.Code,R.Name,R.Sex,R.Dept,R.Tag);
	BookNum=LendBookNum(R.Code);

	if (R.Tag==1)
		printf("证件已挂失，禁止借阅！");

	else  if(BookNum>=4)
		printf("已经借满4本，不能再借！");

	else  		
	{
		printf("请输入ISBN：");
		scanf("%s",ISBN); 

		while(strcmp(ISBN,"#")!=0 && BookNum<MAX_BOOK_LEND)
		{

			B=CreatBookList(  ) ;
			B=BubbleSort(B);  
			i=BinSearchISBN(B,ISBN) ;
			if(i==0)
			{
				printf("\n\n没有找到图书！");
				break;
			}
			else
			{

				//借阅记录
				strcpy(L.Code,R.Code);
				strcpy(L.ISBN, ISBN);
				strcpy(L.LendDate,LendDate);
				strcpy(L.ReturnDate,"NULL");
				strcpy(L.LastDate,LastDate);
				L.Tag=0;

				printf("%s\t%s\t%s\t%s\t%s\t借出\n\n",L.ISBN,B.Node[i].Title,B.Node[i].Author,L.LendDate,L.LastDate);

				SaveLendInfo(L);
				BookNum++;
				printf("请输入ISBN：");
				scanf("%s",ISBN);

			}
		}
		if(BookNum>=4)
			printf("已经借满4本，不能再借！");
	}

	printf("\n借阅完毕！\n");



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

	printf("没有找到读者!\n");
	fclose(fp);

	return (R);
}


int LendBookNum(char Code[20])
{
	LendInfo L;
	int BookNum=0;

	if((fp=fopen("lend.txt","r"))==NULL)
	{
		printf("文件打开错误!\n");
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
		printf("文件打开失败!\n");
		exit(0);
	}

	fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%d\n",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,L.Tag);
	//将借阅信息写入文件 
	fclose(fp);            

	getchar();
}

void ReturnBook( ) 
{
	char Code[20];  //证件号
	char ISBN[50];
	BookList B;
	LendInfoLink *head,*p;
	char ReturnDate[20];  //归还日期
	int i; 
	time_t   t ;

	//计算还书日期
	t= time(NULL);

	strftime(ReturnDate,sizeof(ReturnDate),"%Y-%m-%d",localtime(&t));

	head=CreatLendLink();


	printf("-------------------还书,按#结束-------------------\n\n");
	printf("请输入证件号：");
	scanf("%s",Code);


	printf("请输入ISBN：");
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


		printf("%s\t%s\t%s\t%s\t%s\t已还\n\n",p->ISBN,B.Node[i].Title,B.Node[i].Author,p->LendDate,p->ReturnDate);

		printf("请输入ISBN：");
		scanf("%s",ISBN);
	}
	SaveLendInfoW(head);
	printf("\n还书完毕！\n");

}


LendInfoLink* CreatLendLink()
{
	char Code[20];				//证件号
	char ISBN[50];
	char LendDate[20] ;			//借书日期
	char LastDate[20];			//应还日期
	char ReturnDate[20];		//归还日期
	int Tag;					//状态0;借出，1：归还

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

		fscanf(fp,"%[^\t]",Code);  //先读，再判断feof(fp)，防止文件尾多读一次数据
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
		printf("文件打不开!\n");
		exit(0);
	}
	for( p=head->next; p!=NULL; p=p->next )    
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%d\n",p->Code,p->ISBN,p->LendDate,p->LastDate,p->ReturnDate,p->Tag);
	fclose(fp);           

	printf("\n图书信息已成功保存到文件 lend.txt 中！\n");
	getchar( );
}


void FindLendInfo( ) 
{
	char Code[20];		//证件号
	int i;				//图书数组编号
	LendInfo L;
	BookList B;
	B=CreatBookList(  ) ;
	B=BubbleSort(B);  
    printf("\n----------------------------------------------------\n\n");
	printf("输入要查询读者的code：");
	scanf("%s",Code);
	printf("\n\n");
	
	if((fp=fopen("lend.txt","r"))==NULL)
	{
		printf("文件打不开!\n");
		exit(0);
	}
	
	while(strcmp(Code,"#")!=0)
	{
		rewind(fp);								//定位fp到文件开头，feof值恢复为0
		fscanf(fp,"%s %s %s %s %s %d",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,&L.Tag);

		while(!feof(fp))
		{
			if (strcmp(L.Code,Code)==0)			//找到借阅记录
			{
				i=BinSearchISBN(B,L.ISBN) ;		//查找图书信息

				if(L.Tag==0)
					printf("%s\t%s\t%s\t%s\t%s\t%s\t借出\n\n",L.ISBN,B.Node[i].Title,B.Node[i].Author,L.LendDate,L.LastDate,L.ReturnDate);
				else
					printf("%s\t%s\t%s\t%s\t%s\t%s\t已还\n\n",L.ISBN,B.Node[i].Title,B.Node[i].Author,L.LendDate,L.LastDate,L.ReturnDate);

			}

			fscanf(fp,"%s %s %s %s %s %d",L.Code,L.ISBN,L.LendDate,L.LastDate,L.ReturnDate,&L.Tag);

		}
		printf("\n----------------------------------------------------\n\n");
		printf("输入要查询读者的code：");
		scanf("%s",Code);
		printf("\n\n");
	}
	fclose(fp);
}