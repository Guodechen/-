#ifndef		Reader_H          
#define    Reader_H 
#pragma warning (disable:4996)

typedef struct Reader
{
  char Code[20];						//证件号
  char Name[30];						//姓名
  char Sex[5];							//性别
  char Dept[50];						//工作单位
  int  Tag;								//状态： 0-正常， 1-挂失 
    
}Reader;

typedef struct ReaderLink
{
  char Code[20];						//证件号
  char Name[30];						//姓名
  char Sex[5];							//性别
  char Dept[50];						//工作单位
  int  Tag;								//状态： 0-正常， 1-挂失  
  struct ReaderLink *next;
}ReaderLink;


void BrowseReader	(	) ;					//浏览所有读者信息

void FindReader_Code(	);					//从文件中按照证件号查找
void FindReader_Name(	);					//从文件中按照姓名查找
 
void AlterReader	(	);					//修改读者信息，从文件中读取信息
void LostReader		(	);							//证件挂失
void SaveReaderW	(ReaderLink *);			//读者信息写入文件，删除旧信息浏览
void SaveReader		(ReaderLink *);			//保存读者链表到文件
ReaderLink * InputReader	(	);			//输入读者信息，建立链表
ReaderLink * CreatReaderLink( );			//从文件读取读者信息并创建链表

#endif