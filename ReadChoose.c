#include"Reader.h"

void ReaderChoose()
{
	int MenuNum; 
	int num;
   
	printf("���������ѡ��0-5 �� ");
	scanf("%d",&MenuNum);
	switch(MenuNum)
	{
		  case 1:
			  BrowseReader(  );
			  break;   
		  case 2:InputReader( );
			  break;   
		  case 3: 
			  printf("\n����ѡ��֤����:1,������2����");
             scanf("%d",&num);
			  if(num==1)
				  FindReader_Code	(	);
			  else
			      FindReader_Name	(	);
			  break;    
		  case 4: AlterReader		(	);
			  break;  
		  case 5: LostReader		(	);
			  break;     
  		  case 0: ;
			  break;              
	}






}