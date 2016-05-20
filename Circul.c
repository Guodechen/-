#include "Main.h"
#include "Book.h"
#include "Catalog.h"
void BookBrowseCatalog(  )
{

	BookList B;
	char Key[20];      //编号
	int i;
	int size;
	int r;
	int flag=0; //找到=1，没有找到=0


	B=CreatBookList(  );    //读文件，建立顺序表

	CreatCatalogTree(  );    //输出分类目录树
	printf("\n\n输入要查询的图书分类编号：	");

	scanf(" %s",Key);
	size=strlen(Key);


	printf("\n\n");
	for(i=1;i<=B.Num;i++)
	{

		r=memcmp(B.Node[i].CatalogNum ,Key,size); //比较开头size个字符
		if(r==0)	
		{
			printf("%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
			flag=1;
		}
	}

	if(flag==0)
		printf("\n没有找到这种类型图书！\n");

}

BookList CreatBookList(  ) 
{
	BookList B;
	int i=0;					//图书记录个数；
	char ISBN[50];				//ISBN号
	char Title[200];			//书名
	char Author[200];			//作者
	char Publisher[100];		//出版社
	char Date[20];				//出版日期
	float Price;				//价格
	char CatalogNum[200];		//分类编号

	B.Node=(Book *)malloc(sizeof(Book)*MAX_BOOK_SIZE);

	if((fp=fopen("books.txt","r"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
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


		while(!feof(fp))   
		{

			i++;                       //从B.Node[1]开始存放
			strcpy(B.Node[i].ISBN,ISBN);
			strcpy(B.Node[i].Title,Title);
			strcpy(B.Node[i].Author,Author);
			strcpy(B.Node[i].Publisher,Publisher);	
			strcpy(B.Node[i].Date,Date);
			B.Node[i].Price=Price;
			strcpy(B.Node[i].CatalogNum,CatalogNum);	


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
		B.Num=i; //图书个数

		fclose(fp);

		return (B);

	}
}


void FindISBN_BubbleSort( )
{
	BookList B;
	char ISBN[50];
	int i;

	B=CreatBookList(  ) ;
	printf("\n\n输入要查询的图书ISBN: ");

	scanf("%s",ISBN);

	B=BubbleSort(B);  
	i=BinSearchISBN(B,ISBN) ;
	if(i!=0)
		printf("\n\n%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
	else
		printf("\n\n没有找到记录！");
}


BookList BubbleSort(BookList B)  
{  
	int i,j,n;  
	bool change;  
	Book temp; 

	n = B.Num;  
	change = true;  

	for (i = n; i>=1&&change; --i) 
	{
		change=false;
		for(j=1;j<i;++j)

			if (strcmp(B.Node[j].ISBN,B.Node[j+1].ISBN)>0)
			{  
				temp=B.Node[j+1];

				B.Node[j+1]=B.Node[j];
				B.Node[j]=temp;
				change = true;  
			}  

	}  
	return (B);
}

int  BinSearchISBN(BookList B,char ISBN[ ])      //二分查找
{	
	int mid,low=1,high=B.Num;	
	while(low<=high)	
	{	
		mid=(low+high)/2;	
		if(strcmp(ISBN,B.Node[mid].ISBN)==0)		
			return mid;		
		else if(strcmp(ISBN,B.Node[mid].ISBN)<0)		
			high=mid-1;	
		else		
			low=mid+1;	
	}
	return 0;   //没有找到
}


void FindISBN_SelectSort( )
{
	BookList B;
	char ISBN[50];
	int i;

	B=CreatBookList(  ) ;
	printf("\n\n输入要查询的图书ISBN: ");

	scanf("%s",ISBN);

	B=SelectSort(B);  
	i=BinSearchISBN(B,ISBN) ;
	if(i!=0)
		printf("\n\n%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
	else
		printf("\n\n没有找到记录！");
}


BookList SelectSort(BookList B)
{
	int i,j,k;
	Book temp;
	for(i=1;i<B.Num;++i)
	{ 
		k=i;
		for(j=i+1;j<=B.Num;++j)
		{ 
			if(strcmp(B.Node[k].ISBN,B.Node[j].ISBN)>0)//找到最小的
				k=j;
		}

		if(k!=i) 
		{
			temp=B.Node[i];
			B.Node[i]=B.Node[k];
			B.Node[k]=temp;
		}
	}
	return B;
}



void FindISBN_InsertSort( )
{
	BookList B;
	char ISBN[50];
	int i;

	B=CreatBookList(  ) ;
	printf("\n\n输入要查询的图书ISBN: ");

	scanf("%s",ISBN);

	B=InsertSort(B);  
	i=BinSearchISBN(B,ISBN) ;
	if(i!=0)
		printf("\n\n%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
	else
		printf("\n\n没有找到记录！");
}

BookList InsertSort(BookList B)
{
	int i,j;
	for (i = 2; i <=B.Num; ++i)

		if(strcmp(B.Node[i].ISBN,B.Node[i-1].ISBN)<0)
		{
			B.Node[0]=B.Node[i];
			B.Node[i]=B.Node[i-1];
			for(j=i-2; strcmp(B.Node[0].ISBN,B.Node[j].ISBN)<0; --j)
				B.Node[j+1]=B.Node[j];
			B.Node[j+1]=B.Node[0];


		}
		return B;
}


void FindTitle( )
{
	BookList B;
	char Title[200]; 
	int i;
	int flag=0; //找到图书flag=1，没找到为0.

	B=CreatBookList(  ) ;
	printf("\n\n输入要查询的图书Title: ");
	fflush(stdin);
	gets(Title);

		for(i=1;i<=B.Num; ++i)
	if(strstr(B.Node[i].Title,Title)!=NULL)  
	{
		printf("%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
		printf("\n\n");
		flag=1;
	}
	if(flag==0)
		printf("\n\n没有找到记录！");
}



void FindAuthor( )
{
	BookList B;
	char Author[200]; 
	int i;
	int flag=0; //找到图书flag=1，没找到为0.


	B=CreatBookList(  ) ;
	printf("\n\n输入要查询的图书Author: ");
	fflush(stdin);
	gets(Author);

	for(i=1;i<=B.Num; ++i)
	if(strstr(B.Node[i].Author,Author)!=NULL)  
	{
		printf("%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
		printf("\n\n");
		flag=1;
	}
	if(flag==0)
		printf("\n\n没有找到记录！");

}


void FindPublisher( )
{
	BookList B;
	char Publisher[100]; 
	int i;
	int flag=0; //找到图书flag=1，没找到为0.

	B=CreatBookList(  ) ;
	printf("\n\n输入要查询的图书Publisher: ");
	fflush(stdin);
	gets(Publisher);
	printf("\n\n");
	
	for(i=1;i<=B.Num; ++i)
	if(strstr(B.Node[i].Publisher,Publisher)!=NULL)  
	{
		printf("%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
		printf("\n\n");
		flag=1;
	}
	if(flag==0)
		printf("\n\n没有找到记录！");

}






