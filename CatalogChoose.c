#include"Catalog.h"

void CatalogChoose()
{
	int MenuNum;

	printf("���������ѡ��0-4 �� ");
	scanf("%d",&MenuNum);
	switch(MenuNum)
	{
	case 1:
		AddCatalog( );
		break;   
	case 2:
		PrintCatalog( );
		break;   
	case 3: 
		CreatCatalogTree();
		break;    
	case 4: AlterCatalog(  );
		break;     
	case 0: ;break;              
	}
}