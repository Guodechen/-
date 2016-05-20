#ifndef		Lend_H          
#define    Lend_H 
#pragma warning (disable:4996)

#define MAX_BOOK_LEND 4				//����15��
#define MAX_DAY_LEND 90				//�����90��


typedef struct LendInfo
{
	
	char Code[20];					//֤����
	char ISBN[50];
	char LendDate[20] ;				//��������
	char LastDate[20];				//Ӧ������
	char ReturnDate[20];			//�黹����
   	int Tag;						//״̬0;�����1���黹
}LendInfo;

typedef struct LendInfoLink
{
	
	char Code[20];					//֤����
	char ISBN[50];
	char LendDate[20] ;				//��������
	char LastDate[20];				//Ӧ������
	char ReturnDate[20];			//�黹����
    int Tag;						//״̬0;�����1���黹
	struct LendInfoLink *next;

}LendInfoLink;


Reader FindReaderL(char Code[]);			//��ѯ����
LendInfoLink* CreatLendLink();				//����������Ϣ����


void SaveLendInfo	(	LendInfo   );					//���������Ϣ���ļ�
void SaveLendInfoW	(LendInfoLink *);					//���������Ϣ���ļ������Ǿ���Ϣ


int LendBookNum		( char Code[20]);					//�����ѽ豾��

#endif