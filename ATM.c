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
		int PinCode;
		if (scanf("%d", &PinCode)) {
			clearBuffer();
			//TODO #3 : Add a menu.
			if (PinCode == 9999)
			{
				printf("WIP\n");
			}
			else if (PinCode < 0)
			{
				printf("You have entered a valid input, but it was below zero. Please, make sure that you have entered a positive numeric value.\n");
			}
			else
			{
				printf("Welcome => NoName.\n");
				printf("0- Exit.\n");
				printf("1- Exit.\n");
				printf("2- Exit.\n");
				printf("3- Exit.\n");
			}
		}
		else
		{
			printf("Please, enter a numeric value.\n"); clearBuffer(); continue;
		}

	}
}