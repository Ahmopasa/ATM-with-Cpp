#include "ATM.h"

void clearBuffer(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
		;
}

void ui_screen()
{
	printf("Welcome to the ATM Machine. Please, enter your name and PIN code to proceed.\n");
	printf("< If you do not have any PIN code, or it is not reachable, please press 9999. >\n");

	while (1)
	{
		printf("PinCode : ");
		int PinCode = 0;
		if (scanf("%d", &PinCode)) {
			clearBuffer();
			//TODO #3 : Add a menu.
			switch (PinCode)
			{
			case 1:
			{
				printf("Hello. Please, you choose 1.\n"); break; //TODO #4 : Add more information after choosing from a menu.
			}
			case 2:
			{
				printf("Hello. Please, you choose 2.\n"); break; //TODO #5 : Add more information after choosing from a menu.
			}
			default:
			{
				printf("Invalid Input. Please, try again.\n"); break;
			}
			}
		}
		else
		{
			printf("Please, enter a numeric value.\n"); clearBuffer(); continue;
		}

	}
}