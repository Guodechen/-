#ifndef		Reader_H          
#define    Reader_H 
#pragma warning (disable:4996)

typedef struct Reader
{
  char Code[20];						//֤����
  char Name[30];						//����
  char Sex[5];							//�Ա�
  char Dept[50];						//������λ
  int  Tag;								//״̬�� 0-������ 1-��ʧ 
    
}Reader;

typedef struct ReaderLink
{
  char Code[20];						//֤����
  char Name[30];						//����
  char Sex[5];							//�Ա�
  char Dept[50];						//������λ
  int  Tag;								//״̬�� 0-������ 1-��ʧ  
  struct ReaderLink *next;
}ReaderLink;


void BrowseReader	(	) ;					//������ж�����Ϣ

void FindReader_Code(	);					//���ļ��а���֤���Ų���
void FindReader_Name(	);					//���ļ��а�����������
 
void AlterReader	(	);					//�޸Ķ�����Ϣ�����ļ��ж�ȡ��Ϣ
void LostReader		(	);							//֤����ʧ
void SaveReaderW	(ReaderLink *);			//������Ϣд���ļ���ɾ������Ϣ���
void SaveReader		(ReaderLink *);			//������������ļ�
ReaderLink * InputReader	(	);			//���������Ϣ����������
ReaderLink * CreatReaderLink( );			//���ļ���ȡ������Ϣ����������

#endif