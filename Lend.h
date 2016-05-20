#ifndef		Lend_H          
#define    Lend_H 
#pragma warning (disable:4996)

#define MAX_BOOK_LEND 4				//最多借15本
#define MAX_DAY_LEND 90				//最长借期90天


typedef struct LendInfo
{
	
	char Code[20];					//证件号
	char ISBN[50];
	char LendDate[20] ;				//借书日期
	char LastDate[20];				//应还日期
	char ReturnDate[20];			//归还日期
   	int Tag;						//状态0;借出，1：归还
}LendInfo;

typedef struct LendInfoLink
{
	
	char Code[20];					//证件号
	char ISBN[50];
	char LendDate[20] ;				//借书日期
	char LastDate[20];				//应还日期
	char ReturnDate[20];			//归还日期
    int Tag;						//状态0;借出，1：归还
	struct LendInfoLink *next;

}LendInfoLink;


Reader FindReaderL(char Code[]);			//查询读者
LendInfoLink* CreatLendLink();				//建立借阅信息链表


void SaveLendInfo	(	LendInfo   );					//保存借阅信息到文件
void SaveLendInfoW	(LendInfoLink *);					//保存借阅信息到文件，覆盖旧信息


int LendBookNum		( char Code[20]);					//计算已借本数

#endif