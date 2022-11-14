#include <stdio.h>
#include <stdlib.h>
#include "functions.c"
void menu() // Loops the menu on the terminal.
{
    int i;
    typedef void (*def)();
    def menus[] = {new_transaction, transfer, savings_account, report_12, report_1};
    while (i != 0)
    {
        printf("\n\n");
        printf("\033[0;36m<=============================>\n");
        printf("<----- Financial Manager ----->\n");
        printf("<=============================>\n");
        printf("<= 1. New transaction        =>\n");
        printf("<= 2. Transfer               =>\n");
        printf("<= 3. Savings Account        =>\n");
        printf("<= 4. Last year report       =>\n");
        printf("<= 5. Last month report      =>\n");
        printf("<= 0. Leave                  =>\n");
        printf("<=============================>\033[0m\n");
        scanf("%d", &i);
        if (i != 1 || i!=2 || i!=3 || i!=4 || i!=5 || i!=0){
            printf("\033[31mPlease, enter a valid option.\033[0m");
        }
        menus[i - 1]();
    }
}

void main()
{
    menu();
}