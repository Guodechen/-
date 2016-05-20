#include "Menu.h"
#include "Main.h"

void main()
{
	int MenuNum; 

	do
	{
		MainMenu();

		printf("«Î ‰»Îƒ„µƒ—°‘Ò£°0-5 £∫ ");
		scanf("%d",&MenuNum);
		switch(MenuNum)
		{
		  case 1:
			  ReaderMenu( );
	   	      ReaderChoose();
			  getch( );
			 system("cls");
			  break;   
		  case 2:
			  CatalogMenu( );
			  CatalogChoose();
			  getch( );
			 system("cls");
			  break;   
		  case 3:
			  BookMenu();
			  BookChoose();
			  getch( );
			 system("cls");			  
			  break;    
		  case 4:
			  CirculMenu();
			  CirculChoose();
			  getch( );
			 system("cls");	
			  break;
		  case 5:
			  AdminMenu();
			  AdminChoose();
			  getch();
			  system("cls");
			  break;
  		  case 0: ;
			  break;              
		}
	}while(MenuNum!=0);
	
	
}