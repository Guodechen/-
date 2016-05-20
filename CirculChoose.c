#include"Menu.h"
#include"Book.h"

void CirculChoose()
{
	int MenuNum; 
	int num;

	printf("请输入你的选择！0-5 ： ");
	scanf("%d",&MenuNum);
	switch(MenuNum)
	{
	case 1:
		BookBrowseCatalog( );
		break;   
	case 2:
		 printf("\n输入选择（ISBN 1,书名2,作者3,出版社4）：");
             scanf("%d",&num);
			 switch(num)
			 {
			 case 1:
				 FindISBN_BubbleSort();break;
			 case 2:
			      FindTitle();break;
			 case 3:
				 FindAuthor();break;

			 case 4:
				 FindPublisher();break;
			 }
			 break;
		 
	case 3: 
		LendBook( );
		break;   
	case 4: 
		ReturnBook();
		break;   
	case 5: 
		FindLendInfo();
		break;   

   case 0: ;break;              
	}
}