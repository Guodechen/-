
#ifndef		Catalog_H          
#define    Catalog_H 

#pragma warning (disable:4996)
#define MAX_TREE_SIZE 100

typedef struct Catalog    //Ŀ¼�ṹ����
    {
        char Key[20];      //���
        char Caption[80];  //���⣬���� 
        char Parent[20];   //������
    }Catalog;  

typedef struct CatalogTree		//Ŀ¼˳��洢�ṹ����
{
	Catalog Node[MAX_TREE_SIZE];
	int root;						//���ڵ�λ�ã����ڵ�Ĭ����0�ŵ�Ԫ��
	int num;						//���һ������������
}CatalogTree;

void AddCatalog			(	);							//���ӷ���
void PrintCatalog		(   );							//���Ŀ¼������ţ�����������ţ�
void CreatCatalogTree	(   );							//��������Ŀ¼��������PrintCatalogTree( )
void AlterCatalog		(	);							//�޸ķ���
void PrintCatalogTree	(CatalogTree *tree );			//�������Ŀ¼��������PreOrder( );
void PreOrder(CatalogTree* tree, int k, int level);	//�ݹ�����ṹ�����������

#endif
