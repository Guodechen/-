#include "Main.h"
#include "Book.h"

BookLink * InputBook( )
{
	BookLink *p ,*q,*head;       
	char ISBN[50]; 
	int n=0,x;


	printf("\n�밴��Ӧ������ͼ��Ŀ¼��#������\n");
	printf("---------------------------------------------------\n");
	printf("ISBN���������������ߡ��������硪���������ڡ����۸񡪡�������\n\n");
	printf("\n����һ��س���\n");
	head=(BookLink *)malloc(sizeof(BookLink));
	p=head;
	//fflush(stdin);
	getchar();

	printf("����ISBN��");
	gets(ISBN);

	while(1)
	{  
		if(strcmp(ISBN,"#")==0) 
			break;        
		else

		{
			q=(BookLink *)malloc(sizeof(BookLink));
			strcpy(q->ISBN,ISBN);

			printf("����������");     gets(q->Title);  //�����е����������ߵȴ��ո����Բ�����scanf
			printf("�������ߣ�");     gets(q->Author);  
			printf("��������磺");	   gets(q->Publisher);
			printf("����������ڣ�");  gets(q->Date);
			printf("����۸�");	  scanf("%f",&q->Price);
			getchar();
			printf("��������ţ�");	gets(q->CatalogNum);

			p->next=q;
			p=q;
		}

		printf("\n\n����ISBN��");
		gets(ISBN);


	} 

	q->next=NULL;
	printf("ͼ��Ŀ¼���������\n\n");	

	printf("�Ƿ񱣴�ͼ��Ŀ¼����1.��/2.�񣩣�");
	scanf("%d",&x);
	if(x==1)
		SaveBook(head);                 
	else
		printf("\n�ļ�û�б����棡\n");
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
	//��ͼ����Ϣд���ļ� 
	fclose(fp);            


	printf("\nͼ����Ϣ�ѳɹ����浽�ļ� book.txt �У�\n");
	getchar();
}

BookLink *CreatBookLink(  )

{
	BookLink *head,*p,*q;
	char ISBN[50];        //ISBN��
	char Title[200];      //����
	char Author[200];      //����
	char Publisher[100];   //������
	char Date[20];       //��������
	float Price;         //�۸�
	char CatalogNum[200];//������

	if((fp=fopen("books.txt","r"))==NULL) 
	{
		printf("File open error!\n");
		exit(0);
	}

	head=(BookLink *)malloc(sizeof(BookLink));
	q=head;	

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


	printf("\nͼ����Ϣ�ѳɹ����浽�ļ� book.txt �У�\n");
	getchar( );
}


void DeleteBook(  ) 

{
	BookLink *head,*p,*pre;
	char ISBN[50]; 

	head=CreatBookLink(  );
	p=head->next;
	pre=head;

	printf("\n\n����Ҫɾ��ͼ���ISBN��");
	scanf("%s",ISBN);

	while((p!=NULL)&&(strcmp(p->ISBN,ISBN)!=0))
	{	
		pre=p;
		p=p->next;
	}
	if(p==NULL)
		printf("ͼ��Ŀ¼�����ڣ�");

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
	printf("\n\n����Ҫ�޸�ͼ���ISBN��");
	gets(ISBN);

	while((p!=NULL)&&(strcmp(p->ISBN,ISBN)!=0))
	{	
		pre=p;
		p=p->next;
	}
	if(p==NULL)
		printf("ͼ��Ŀ¼�����ڣ�");

	else
	{
		printf("��������ͼ��Ŀ¼��\n\n");
		printf("����ISBN��");	  gets(p->ISBN);
		printf("����������");     gets(p->Title);
		printf("�������ߣ�");     gets(p->Author);
		printf("��������磺");	   gets(p->Publisher);
		printf("����������ڣ�");  gets(p->Date);
		printf("����۸�");	  scanf("%f",&p->Price);
		getchar();
		printf("��������ţ�");	gets(p->CatalogNum);


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
		if (pre == head) /*���ڵ�һ���ڵ�֮ǰ*/
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

