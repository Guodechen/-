#ifndef		Book_H
#pragma warning (disable:4996)
#define    Book_H 
#define MAX_BOOK_SIZE 5000


#define true 1
#define false 0
typedef int  bool ;
typedef struct Book
{
	char ISBN[50];				//ISBN号
	char Title[200];			//书名
	char Author[200];			//作者
	char Publisher[100];		//出版社
	char Date[20];				//出版日期
	char CatalogNum[200];		//分类编号
	float Price;				//价格
}Book;
 
typedef struct BookLink			//图书单链表存储结构类型
{
	char ISBN[50];				//ISBN号
	char Date[20];				//出版日期
	char Title[200];			//书名
	char Author[200];			//作者
	char Publisher[100];		//出版社
	char CatalogNum[200];		//分类编号
	float Price;				//价格
	struct BookLink *next;
}BookLink;

typedef struct BookList			//图书顺序存储结构类型
{
   Book *Node;
   int Num;						//图书个数
}BookList;



BookLink *InputBook			(	);						//输入多个图书目录，建立链表
BookLink *CreatBookLink		(	);						//读取文件信息，建立图书目录链表
BookLink *InsertSortBook	(BookLink *head);			//图书目录直接插入排序

BookList CreatBookList		(	);						//建立图书结构体数组
BookList BubbleSort			(BookList);
BookList BInsertSort		(BookList);
BookList SelectSort			(BookList);
BookList InsertSort			(BookList);

int  BinSearchISBN			(BookList B, char[]);

void SaveBook				(BookLink *);				//保存图书链表到文件
void SaveBookW				(BookLink *);				//保存链表到文件，重写

void DeleteBook				(	);						//删除图书目录
void AlterBook				(	);						//修改图书目录
void BookBrowseCatalog		(	);						//图书分类浏览
void FindTitle				(	);
void LendBook				(	);						//借阅图书
void ReturnBook				(	);						//还书
void FindLendInfo			(	);						//查询个人借阅记录
void FindAuthor				(	);
void FindPublisher			(	);
void  FindISBN_BubbleSort	(	);
void FindISBN_SelectSort	(	);
void FindISBN_InsertSort	(	);

#endif
