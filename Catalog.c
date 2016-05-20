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
		printf("����:�����ţ������������š�#������\n");
		scanf("%s",C.Key );

		while(strcmp(C.Key,"#")!=0)
		{
			scanf("%s%s",C.Caption,C.Parent );

			fwrite(&C,sizeof(Catalog),1,fp);
			scanf("%s",C.Key);
		}

		fclose(fp);
		printf("�����ɹ���\n");
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
		while(!feof(fp))/*��ȡ�����*/
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
		while(!feof(fp))/*��ȡ�����*/
		{

			i++;
			fread(&C.Node[i], sizeof(Catalog),1,fp);
		}
		C.num=i;
		C.root=0;     //���ڵ�Ĭ����0�ŵ�Ԫ��
		fclose(fp);

	}

	PrintCatalogTree( &C);
}


void PrintCatalogTree(CatalogTree *tree )
{
	int level=1; 
	PreOrder( tree , 0,level );
}


void	PreOrder(  CatalogTree* tree,int k,int level)//k�ǽṹ��������
{
	int i,j,m=0;
	for(i=1;i<level;i++)
		printf("     ");

	printf("|����%s %s\n",tree->Node[k].Caption,tree->Node[k].Key); //������ڵ�
	
	for( j=k+1 ; j<tree->num; j++)   //�ļ��е����ʹ洢��Ĭ���ǰ��ո����������ǰ��
	{
		if(strcmp(tree->Node[j].Parent,tree->Node[k].Key)==0)
		{
			if(m==0)
		 {
			 PreOrder(tree ,j, ++level);  //�����һ�����ӽ�㣬������˫�׵���һ��
			 m++;
			}

			else
				PreOrder(tree ,j, level);  //����������ӽ��
		}	

	}	
}



void AlterCatalog(  )
{
	char Key[20]; //Ҫ�޸ĵķ���ı��
	Catalog C;
	int num=0;//��¼����

	printf("  -------------------------\n\n ");
	printf(" ����Ҫ�޸ĵķ���ı�ţ� ");
	scanf(" %s",Key);

	if((fp=fopen("catalog3.dat","rb+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fread(&C, sizeof(Catalog),1,fp);

		while(!feof(fp))/*��ȡ�����*/
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

	printf(" ��������µ� ��ţ�����������ţ� \n\n");
	scanf(" %s%s%s",C.Key,C.Caption,C.Parent);

	fseek(fp,num*sizeof(Catalog),SEEK_SET);  //����λ���޸Ĳ���

	fwrite(&C,sizeof(Catalog),1,fp);
	printf(" �޸ĳɹ���\n\n");
	fclose(fp);
}