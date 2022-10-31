#include <stdio.h>
#include <stdlib.h>
#include "functions.c"
void menu() // Loops the menu on the terminal.
{
    int i;
    typedef void (*def)();
    def menus[] = {new_receipt, report_12, report_1};
    printf("\n\n<=Personal Financial Manager=>\n\n");
    while (i != 0)
    {
        printf("<============================>\n");
        printf("<--------- Receipts --------->\n");
        printf("<============================>\n");
        printf("<= 1. Insert a new receipt  =>\n");
        printf("<= 2. Last 12 months report =>\n");
        printf("<= 3. Last month report     =>\n");
        printf("<= 0. Leave                 =>\n");
        printf("<============================>\n");
        scanf("%d", &i);
        menus[i - 1]();
    }
}
int main(void)
{
    menu();
    return 0;
}