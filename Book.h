#ifndef		Book_H
#pragma warning (disable:4996)
#define    Book_H 
#define MAX_BOOK_SIZE 5000


#define true 1
#define false 0
typedef int  bool ;
typedef struct Book
{
	char ISBN[50];				//ISBN��
	char Title[200];			//����
	char Author[200];			//����
	char Publisher[100];		//������
	char Date[20];				//��������
	char CatalogNum[200];		//������
	float Price;				//�۸�
}Book;
 
typedef struct BookLink			//ͼ�鵥����洢�ṹ����
{
	char ISBN[50];				//ISBN��
	char Date[20];				//��������
	char Title[200];			//����
	char Author[200];			//����
	char Publisher[100];		//������
	char CatalogNum[200];		//������
	float Price;				//�۸�
	struct BookLink *next;
}BookLink;

typedef struct BookList			//ͼ��˳��洢�ṹ����
{
   Book *Node;
   int Num;						//ͼ�����
}BookList;



BookLink *InputBook			(	);						//������ͼ��Ŀ¼����������
BookLink *CreatBookLink		(	);						//��ȡ�ļ���Ϣ������ͼ��Ŀ¼����
BookLink *InsertSortBook	(BookLink *head);			//ͼ��Ŀ¼ֱ�Ӳ�������

BookList CreatBookList		(	);						//����ͼ��ṹ������
BookList BubbleSort			(BookList);
BookList BInsertSort		(BookList);
BookList SelectSort			(BookList);
BookList InsertSort			(BookList);

int  BinSearchISBN			(BookList B, char[]);

void SaveBook				(BookLink *);				//����ͼ�������ļ�
void SaveBookW				(BookLink *);				//���������ļ�����д

void DeleteBook				(	);						//ɾ��ͼ��Ŀ¼
void AlterBook				(	);						//�޸�ͼ��Ŀ¼
void BookBrowseCatalog		(	);						//ͼ��������
void FindTitle				(	);
void LendBook				(	);						//����ͼ��
void ReturnBook				(	);						//����
void FindLendInfo			(	);						//��ѯ���˽��ļ�¼
void FindAuthor				(	);
void FindPublisher			(	);
void  FindISBN_BubbleSort	(	);
void FindISBN_SelectSort	(	);
void FindISBN_InsertSort	(	);

#endif
