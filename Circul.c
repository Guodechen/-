#include "Main.h"
#include "Book.h"
#include "Catalog.h"
void BookBrowseCatalog(  )
{

	BookList B;
	char Key[20];      //���
	int i;
	int size;
	int r;
	int flag=0; //�ҵ�=1��û���ҵ�=0


	B=CreatBookList(  );    //���ļ�������˳���

	CreatCatalogTree(  );    //�������Ŀ¼��
	printf("\n\n����Ҫ��ѯ��ͼ������ţ�	");

	scanf(" %s",Key);
	size=strlen(Key);


	printf("\n\n");
	for(i=1;i<=B.Num;i++)
	{

		r=memcmp(B.Node[i].CatalogNum ,Key,size); //�ȽϿ�ͷsize���ַ�
		if(r==0)	
		{
			printf("%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
			flag=1;
		}
	}

	if(flag==0)
		printf("\nû���ҵ���������ͼ�飡\n");

}

BookList CreatBookList(  ) 
{
	BookList B;
	int i=0;					//ͼ���¼������
	char ISBN[50];				//ISBN��
	char Title[200];			//����
	char Author[200];			//����
	char Publisher[100];		//������
	char Date[20];				//��������
	float Price;				//�۸�
	char CatalogNum[200];		//������

	B.Node=(Book *)malloc(sizeof(Book)*MAX_BOOK_SIZE);

	if((fp=fopen("books.txt","r"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fscanf(fp,"%[^\t]",ISBN);  //�ȶ������ж�feof(fp)����ֹ�ļ�β���һ������
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

			i++;                       //��B.Node[1]��ʼ���
			strcpy(B.Node[i].ISBN,ISBN);
			strcpy(B.Node[i].Title,Title);
			strcpy(B.Node[i].Author,Author);
			strcpy(B.Node[i].Publisher,Publisher);	
			strcpy(B.Node[i].Date,Date);
			B.Node[i].Price=Price;
			strcpy(B.Node[i].CatalogNum,CatalogNum);	


			fscanf(fp,"%[^\t]",ISBN);  //�ȶ������ж�feof(fp)����ֹ�ļ�β���һ������
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
		B.Num=i; //ͼ�����

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
	printf("\n\n����Ҫ��ѯ��ͼ��ISBN: ");

	scanf("%s",ISBN);

	B=BubbleSort(B);  
	i=BinSearchISBN(B,ISBN) ;
	if(i!=0)
		printf("\n\n%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
	else
		printf("\n\nû���ҵ���¼��");
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

int  BinSearchISBN(BookList B,char ISBN[ ])      //���ֲ���
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
	return 0;   //û���ҵ�
}


void FindISBN_SelectSort( )
{
	BookList B;
	char ISBN[50];
	int i;

	B=CreatBookList(  ) ;
	printf("\n\n����Ҫ��ѯ��ͼ��ISBN: ");

	scanf("%s",ISBN);

	B=SelectSort(B);  
	i=BinSearchISBN(B,ISBN) ;
	if(i!=0)
		printf("\n\n%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
	else
		printf("\n\nû���ҵ���¼��");
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
			if(strcmp(B.Node[k].ISBN,B.Node[j].ISBN)>0)//�ҵ���С��
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
	printf("\n\n����Ҫ��ѯ��ͼ��ISBN: ");

	scanf("%s",ISBN);

	B=InsertSort(B);  
	i=BinSearchISBN(B,ISBN) ;
	if(i!=0)
		printf("\n\n%s\t%s\t%s\t%s\t%s\t%.2f\t%s\n\n\n",B.Node[i].ISBN,B.Node[i].Title,B.Node[i].Author,B.Node[i].Publisher,B.Node[i].Date,B.Node[i].Price,B.Node[i].CatalogNum);
	else
		printf("\n\nû���ҵ���¼��");
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
	int flag=0; //�ҵ�ͼ��flag=1��û�ҵ�Ϊ0.

	B=CreatBookList(  ) ;
	printf("\n\n����Ҫ��ѯ��ͼ��Title: ");
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
		printf("\n\nû���ҵ���¼��");
}



void FindAuthor( )
{
	BookList B;
	char Author[200]; 
	int i;
	int flag=0; //�ҵ�ͼ��flag=1��û�ҵ�Ϊ0.


	B=CreatBookList(  ) ;
	printf("\n\n����Ҫ��ѯ��ͼ��Author: ");
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
		printf("\n\nû���ҵ���¼��");

}


void FindPublisher( )
{
	BookList B;
	char Publisher[100]; 
	int i;
	int flag=0; //�ҵ�ͼ��flag=1��û�ҵ�Ϊ0.

	B=CreatBookList(  ) ;
	printf("\n\n����Ҫ��ѯ��ͼ��Publisher: ");
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
		printf("\n\nû���ҵ���¼��");

}






