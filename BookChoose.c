#include"Book.h"

void BookChoose()
{
	int MenuNum;

	printf("«Î ‰»Îƒ„µƒ—°‘Ò£°0-4 £∫ ");
	scanf("%d",&MenuNum);

	switch(MenuNum)
	{
	case 1:
		InputBook			( );
		break;   
	case 2:
		DeleteBook			( );
		break;   
	case 3: 
		AlterBook			( );
		break;    
    case 4: 
		FindISBN_BubbleSort	( );
		break; 
	case 0: 
		break;              
	}
}