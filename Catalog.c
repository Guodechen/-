#include "Main.h"
#include "Catalog.h"


void AddCatalog( ) 
{
	Catalog C;

	if((fp=fopen("catalog3.dat","ab"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		printf("输入:分类编号，类名，父类编号。#结束：\n");
		scanf("%s",C.Key );

		while(strcmp(C.Key,"#")!=0)
		{
			scanf("%s%s",C.Caption,C.Parent );

			fwrite(&C,sizeof(Catalog),1,fp);
			scanf("%s",C.Key);
		}

		fclose(fp);
		printf("操作成功！\n");
	}


}

void PrintCatalog( )
{
	Catalog C;
	if((fp=fopen("catalog3.dat","rb"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&C, sizeof(Catalog),1,fp);
		while(!feof(fp))/*读取并输出*/
		{

			printf(" %s\t%s\t%s\n",C.Key,C.Caption,C.Parent );
			fread(&C, sizeof(Catalog),1,fp);
		}
	}
}


void CreatCatalogTree(  )//0
{
	CatalogTree C;
	int i=0;

	if((fp=fopen("catalog3.dat","rb"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&C.Node[i], sizeof(Catalog),1,fp);
		while(!feof(fp))/*读取并输出*/
		{

			i++;
			fread(&C.Node[i], sizeof(Catalog),1,fp);
		}
		C.num=i;
		C.root=0;     //根节点默认在0号单元；
		fclose(fp);

	}

	PrintCatalogTree( &C);
}


void PrintCatalogTree(CatalogTree *tree )
{
	int level=1; 
	PreOrder( tree , 0,level );
}


void	PreOrder(  CatalogTree* tree,int k,int level)//k是结构体数组编号
{
	int i,j,m=0;
	for(i=1;i<level;i++)
		printf("     ");

	printf("|——%s %s\n",tree->Node[k].Caption,tree->Node[k].Key); //输出父节点
	
	for( j=k+1 ; j<tree->num; j++)   //文件中的类型存储，默认是按照父类在子类的前面
	{
		if(strcmp(tree->Node[j].Parent,tree->Node[k].Key)==0)
		{
			if(m==0)
		 {
			 PreOrder(tree ,j, ++level);  //输出第一个孩子结点，孩子在双亲的下一层
			 m++;
			}

			else
				PreOrder(tree ,j, level);  //输出其他孩子结点
		}	

	}	
}



void AlterCatalog(  )
{
	char Key[20]; //要修改的分类的编号
	Catalog C;
	int num=0;//记录个数

	printf("  -------------------------\n\n ");
	printf(" 输入要修改的分类的编号： ");
	scanf(" %s",Key);

	if((fp=fopen("catalog3.dat","rb+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&C, sizeof(Catalog),1,fp);

		while(!feof(fp))/*读取并输出*/
		{
			
			if(strcmp(C.Key ,Key)==0)
			{	
				printf(" %s\t%s\t%s\n\n",C.Key,C.Caption,C.Parent );
			   break;
			}
			
			fread(&C, sizeof(Catalog),1,fp);
			num++;
		}
	}

	printf(" 输入分类新的 编号，类名，父类号： \n\n");
	scanf(" %s%s%s",C.Key,C.Caption,C.Parent);

	fseek(fp,num*sizeof(Catalog),SEEK_SET);  //不定位，修改不了

	fwrite(&C,sizeof(Catalog),1,fp);
	printf(" 修改成功！\n\n");
	fclose(fp);
}