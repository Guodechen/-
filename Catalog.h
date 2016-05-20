
#ifndef		Catalog_H          
#define    Catalog_H 

#pragma warning (disable:4996)
#define MAX_TREE_SIZE 100

typedef struct Catalog    //目录结构类型
    {
        char Key[20];      //编号
        char Caption[80];  //标题，类名 
        char Parent[20];   //父类编号
    }Catalog;  

typedef struct CatalogTree		//目录顺序存储结构类型
{
	Catalog Node[MAX_TREE_SIZE];
	int root;						//根节点位置，根节点默认在0号单元；
	int num;						//最后一个结点的数组编号
}CatalogTree;

void AddCatalog			(	);							//增加分类
void PrintCatalog		(   );							//输出目录，（编号，类名，父类号）
void CreatCatalogTree	(   );							//建立分类目录树，调用PrintCatalogTree( )
void AlterCatalog		(	);							//修改分类
void PrintCatalogTree	(CatalogTree *tree );			//输出分类目录树，调用PreOrder( );
void PreOrder(CatalogTree* tree, int k, int level);	//递归遍历结构体数组输出树

#endif
