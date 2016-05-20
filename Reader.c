#include "Main.h"
#include "Reader.h"

void BrowseReader(  ) 
{
	char Code[20];  //证件号
	char Name[30];  //姓名
	char Sex[5];  
	char Dept[50];//工作单位
	int  Tag; 



	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("文件打开错误!\n");
		exit(0);
	}
	printf("\n\n---------------------------------------------------\n");
	printf("证件号           姓名        性别     单位    \n");
	printf("\n---------------------------------------------------\n");


	fscanf(fp,"%s %s %s %s %d",Code,Name,Sex,Dept,&Tag);   //先读后输出，防止最后一个读两遍
	while(!feof(fp))
	{
		printf(" %s\t%s\t%s\t%s\t\n",Code,Name,Sex,Dept);     
		fscanf(fp,"%s %s %s %s %d",Code,Name,Sex,Dept,&Tag);
	}


	if(fclose(fp))
	{
		printf("不能关闭文件!\n");
		exit(0);
	}
}



ReaderLink * InputReader( )
{
	ReaderLink *p ,*q,*head;       
	char Code[20];
	int n=0,x;


	printf("\n\n---------------------------------------------------\n");
	printf("证件号，姓名，性别(F,M)，单位，挂失状态（0,1）。以#结束\n");
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
	printf("读者信息输入结束！\n");	
	getchar();                       
	printf("是否保存读者信息？（1.是/2.否）：");
	scanf("%d",&x);
	if(x==1)
		SaveReader(head);                /*调用函数保存至文件*/
	else
		printf("\n文件没有被保存！\n");
	return head;                    /*返回头指针*/
}


void  SaveReader(ReaderLink *head)

{  

	ReaderLink *p;
	if((fp=fopen("reader.txt","a"))==NULL)
	{
		printf("文件打开错误!\n");
		exit(0);
	}

	for(p=head->next ; p!=NULL ; p=p->next)    
		fprintf(fp,"%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept,p->Tag);
													//将图书信息写入文件 
	fclose(fp);            


	printf("\n图书信息已成功保存到文件 reader.txt 中！\n");
	getchar();
}



void FindReader_Code()
{
	char Code[20]; 
	Reader R;
	int flag=0;  //找到为1，没找到为0

	printf("\n输入要查询读者的证件号：");
	scanf("%s",Code);

	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("文件打开错误!\n");
		exit(0);
	}
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %s %d",R.Code,R.Name,R.Sex,R.Dept,&R.Tag);//读一条记录
		if (strcmp(R.Code,Code)==0)       //比较
		{
			printf("\n%s\t%s\t%s\t%s\t%d\n",R.Code,R.Name,R.Sex,R.Dept,R.Tag);
			flag=1;
			break;
		}		
			
	}
	if (flag==0)
		printf("没有找到读者记录!\n");

	getchar();                       

	fclose(fp);
}


void FindReader_Name()
{
	char Name[30]; 
	Reader R;
	int flag=0; //找到为1，没找到为0

	printf("\n输入要查询读者的姓名：");
	scanf("%s",Name);

	if((fp=fopen("reader.txt","r"))==NULL)
	{
		printf("文件打开错误!\n");
		exit(0);
	}
	 
	while(!feof(fp))
	{
			fscanf(fp,"%s %s %s %s %d",R.Code,R.Name,R.Sex,R.Dept,&R.Tag);
			
			if (strcmp(R.Name,Name)==0)
		{
			printf("\n%s\t%s\t%s\t%s\t%d\n",R.Code,R.Name,R.Sex,R.Dept,R.Tag);
			flag=1;  //找到修改标记
			break;

		}		

	}
	if (flag==0)
		printf("没有找到读者记录!\n");

	fclose(fp);


}


void AlterReader(  )
{
	char Code[20];  
	ReaderLink *head,*p;
	head=CreatReaderLink( ); 


	printf("输入要修改的读者的证件号：  ");
	scanf("%s",Code);

	//在链表中查找读者

	p=head->next;
	for(p; p!=NULL&&strcmp(p->Code,Code)!=0; p=p->next);

	printf("找到要修改的读者：  ");
	printf("%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept,p->Tag);


	printf("输入读者新的信息：证件号，姓名，性别，工作单位，状态：\n");
	scanf("%s %s %s %s %d",p->Code,p->Name,p->Sex,p->Dept,&p->Tag);

	printf( "%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept, p->Tag);

	SaveReaderW( head);

	printf("修改成功！");

}


ReaderLink *CreatReaderLink(  )

{
	ReaderLink *head,*p,*q;
	if((fp=fopen("reader.txt","r"))==NULL) 
	{
		printf("文件打开错误!\n");
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
		printf("文件打开错误!\n");
		exit(0);
	}
	for( p=head->next; p!=NULL; p=p->next )    
		fprintf(fp,"%s\t%s\t%s\t%s\t%d\n",p->Code,p->Name,p->Sex,p->Dept,p->Tag);

	fclose(fp);           


	printf("\n读者信息已成功保存到文件 reader.txt 中！\n");
	getchar( );
}



void LostReader(  )
{
	char Code[20];			//证件号
	ReaderLink *head,*p;
	head=CreatReaderLink( ); //建立链表

	printf("输入挂失证件号：  ");
	scanf("%s",Code);

	p=head->next;
	for(p; p!=NULL&&strcmp(p->Code,Code)!=0; p=p->next);

	printf("\n找到要挂失的读者：  ");
	printf("%s\t%s\t%s\t%s\n",p->Code,p->Name,p->Sex,p->Dept);

	p->Tag=1;

	SaveReaderW(head);

	printf("\n挂失成功！\n\n");

}