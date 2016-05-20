#include "Main.h"
#include "Book.h"

BookLink * InputBook( )
{
	BookLink *p ,*q,*head;       
	char ISBN[50]; 
	int n=0,x;


	printf("\n请按对应项输入图书目录以#结束：\n");
	printf("---------------------------------------------------\n");
	printf("ISBN——书名——作者——出版社——出版日期——价格——分类编号\n\n");
	printf("\n输入一项回车：\n");
	head=(BookLink *)malloc(sizeof(BookLink));
	p=head;
	//fflush(stdin);
	getchar();

	printf("输入ISBN：");
	gets(ISBN);

	while(1)
	{  
		if(strcmp(ISBN,"#")==0) 
			break;        
		else

		{
			q=(BookLink *)malloc(sizeof(BookLink));
			strcpy(q->ISBN,ISBN);

			printf("输入书名：");     gets(q->Title);  //由于有的书名、作者等带空格，所以不能用scanf
			printf("输入作者：");     gets(q->Author);  
			printf("输入出版社：");	   gets(q->Publisher);
			printf("输入出版日期：");  gets(q->Date);
			printf("输入价格：");	  scanf("%f",&q->Price);
			getchar();
			printf("输入分类编号：");	gets(q->CatalogNum);

			p->next=q;
			p=q;
		}

		printf("\n\n输入ISBN：");
		gets(ISBN);


	} 

	q->next=NULL;
	printf("图书目录输入结束！\n\n");	

	printf("是否保存图书目录？（1.是/2.否）：");
	scanf("%d",&x);
	if(x==1)
		SaveBook(head);                 
	else
		printf("\n文件没有被保存！\n");
	return head;  
}



void  SaveBook(BookLink *head)

{  

	BookLink *p;
	if((fp=fopen("books.txt","a"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	for(p=head->next;p!=NULL;p=p->next)    
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n",p->ISBN,p->Title,p->Author,p->Publisher,p->Date,p->Price,p->CatalogNum);
	//将图书信息写入文件 
	fclose(fp);            


	printf("\n图书信息已成功保存到文件 book.txt 中！\n");
	getchar();
}

BookLink *CreatBookLink(  )

{
	BookLink *head,*p,*q;
	char ISBN[50];        //ISBN号
	char Title[200];      //书名
	char Author[200];      //作者
	char Publisher[100];   //出版社
	char Date[20];       //出版日期
	float Price;         //价格
	char CatalogNum[200];//分类编号

	if((fp=fopen("books.txt","r"))==NULL) 
	{
		printf("File open error!\n");
		exit(0);
	}

	head=(BookLink *)malloc(sizeof(BookLink));
	q=head;	

	fscanf(fp,"%[^\t]",ISBN);  //先读，再判断feof(fp)，防止文件尾多读一次数据
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",Title);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",Author);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",Publisher);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",Date);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%f",&Price);   //float
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\n]",CatalogNum);
	fscanf(fp,"%*c"); 

	while(!feof(fp))   
	{

		p=(BookLink *)malloc(sizeof(BookLink));
		strcpy(p->ISBN,ISBN);
		strcpy(p->Title,Title);
		strcpy(p->Author,Author);
		strcpy(p->Publisher,Publisher);	
		strcpy(p->Date,Date);
		p->Price=Price;
		strcpy(p->CatalogNum,CatalogNum);	

		q->next=p;
		q=p;

		fscanf(fp,"%[^\t]",ISBN);  //先读，再判断feof(fp)，防止文件尾多读一次数据
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Title);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Author);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Publisher);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Date);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%f",&Price);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\n]",CatalogNum);
		fscanf(fp,"%*c");	


	}
	p->next=NULL;

	fclose(fp);

	return head;
}



void  SaveBookW(BookLink *head)

{  

	BookLink *p;
	if((fp=fopen("books.txt","w"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	for( p=head->next; p!=NULL; p=p->next )    
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n",p->ISBN,p->Title,p->Author,p->Publisher,p->Date,p->Price,p->CatalogNum);
	fclose(fp);           


	printf("\n图书信息已成功保存到文件 book.txt 中！\n");
	getchar( );
}


void DeleteBook(  ) 

{
	BookLink *head,*p,*pre;
	char ISBN[50]; 

	head=CreatBookLink(  );
	p=head->next;
	pre=head;

	printf("\n\n输入要删除图书的ISBN：");
	scanf("%s",ISBN);

	while((p!=NULL)&&(strcmp(p->ISBN,ISBN)!=0))
	{	
		pre=p;
		p=p->next;
	}
	if(p==NULL)
		printf("图书目录不存在！");

	else
	{
		pre->next=p->next;
		free(p);	
	}

	SaveBookW( head);

}


void AlterBook(  ) 

{
	BookLink *head,*p,*pre;
	char ISBN[50]; 

	head=CreatBookLink(  );
	p=head->next;
	pre=head;
	getchar() ;
	printf("\n\n输入要修改图书的ISBN：");
	gets(ISBN);

	while((p!=NULL)&&(strcmp(p->ISBN,ISBN)!=0))
	{	
		pre=p;
		p=p->next;
	}
	if(p==NULL)
		printf("图书目录不存在！");

	else
	{
		printf("重新输入图书目录！\n\n");
		printf("输入ISBN：");	  gets(p->ISBN);
		printf("输入书名：");     gets(p->Title);
		printf("输入作者：");     gets(p->Author);
		printf("输入出版社：");	   gets(p->Publisher);
		printf("输入出版日期：");  gets(p->Date);
		printf("输入价格：");	  scanf("%f",&p->Price);
		getchar();
		printf("输入分类编号：");	gets(p->CatalogNum);


	}

	SaveBookW( head);

}

BookLink *InsertSortBook( BookLink *head )
{
	BookLink *first,*t,*p,*pre; 

	p = head->next;
	first=p->next;
	pre=head;
	p->next = NULL;

	while (first != NULL)
	{
		p = head->next;
		pre=head;
		for (t=first ; ((p!=NULL) && (p->ISBN < t->ISBN)); pre=p, p=p->next); 

		first = first->next; 
		if (pre == head) /*插在第一个节点之前*/
		{
			head->next = t;    
		}
		else 
		{
			pre->next = t;   
		}
		t->next = p;  

	}
	return head;
}

