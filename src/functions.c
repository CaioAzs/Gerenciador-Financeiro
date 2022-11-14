#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char name[40], filename_aux[30], filename[30];
typedef struct // Receipt/Expense class
{
    int identifier; // This identifier defines if this is struct is being used for transactions or tranfers. (1)TRANSACTION (2)MONEY TRANSFER
    double money;
    char description[100], categorie[40];
    int day, month, year;
    int time; // Used only in saving function.
} data;

void new_transaction() // If it exists, ads a new transaction (struct) in the binary file, on the contrary, the function creates a new binary file.
{
    system("cls");
    printf("<=============================>\n");
    printf("<------ New Transaction ------>\n");
    printf("<=============================>\n");

    data new_transaction;
    new_transaction.identifier = 1; // Identifies a transaction struct.

    fflush(stdin);
    printf("First of all, please type your first and last name: ");
    scanf("%40[^\n]s", name);
    printf("Okay %s, now you can add your new transaction.\n\n", name);

    int expense_receipt;
    fflush(stdin);
    printf("Now, is this transaction an expense(1), or a receipt(2)? (1/2) ");
    scanf("%d", &expense_receipt);

    fflush(stdin);
    printf("Type the name of your binary file(max 20 characters): ");
    scanf("%30[^\n]s", filename_aux);
    sprintf(filename, "./Files/%s.txt", filename_aux);

    fflush(stdin);
    printf("Please, type the categorie of the transaction: ");
    scanf("%40[^\n]", new_transaction.categorie);

    fflush(stdin);
    printf("Please, type the description of the transaction: ");
    scanf("%100[^\n]", new_transaction.description);

    fflush(stdin);
    printf("Please, type the DATE of the expense (dd mm yyyy): ");
    scanf("%d %d %d", &new_transaction.day, &new_transaction.month, &new_transaction.year);

    double money;
    fflush(stdin);
    printf("Please, type the amount of money spent on the transaction: ");
    scanf("%lf", &money);
    if (expense_receipt == 1)
    {
        new_transaction.money = money * -1;
    }
    else
    {
        new_transaction.money = money;
    }

    FILE *file;
    if (file = fopen(filename, "ab"))
    {
        fwrite(&new_transaction, sizeof(data), 1, file);
        fclose(file);
        printf("\n\033[0;32mYour transaction has been saved!\033[0m");
    }
    else
    {
        fopen(filename, "wb");
        fwrite(&new_transaction, sizeof(data), 1, file);
        fclose(file);
        printf("\n\033[0;32mYour transaction has been saved!\033[0m");
    }
}

void transfer()
{
    system("cls");
    printf("<==============================>\n");
    printf("<------- Money transfer ------->\n");
    printf("<==============================>\n");

    data new_transfer;
    new_transfer.identifier = 2; // Identifies the transfers struct.

    fflush(stdin);
    printf("Type the name of your binary file(max 20 characters): ");
    scanf("%30[^\n]s", filename_aux);
    sprintf(filename, "./Files/%s.txt", filename_aux);

    fflush(stdin);
    printf("\nPlease, type the who you want to transfer the money (Full name): ");
    scanf("%40[^\n]", new_transfer.categorie);

    fflush(stdin);
    printf("Please, type the description of the transaction: ");
    scanf("%100[^\n]", new_transfer.description);

    fflush(stdin);
    printf("Please, type the DATE of the expense (dd mm yyyy): ");
    scanf("%d %d %d", &new_transfer.day, &new_transfer.month, &new_transfer.year);

    fflush(stdin);
    printf("Please, enter how much money you want to transfer ($): ");
    scanf("%lf", &new_transfer.money);

    FILE *file;
    if (file = fopen(filename, "ab"))
    {
        fwrite(&new_transfer, sizeof(data), 1, file);
        fclose(file);
        printf("\n\033[0;32mYour transfer has been saved!\033[0m");
    }
    else
    {
        fopen(filename, "wb");
        fwrite(&new_transfer, sizeof(data), 1, file);
        fclose(file);
        printf("\n\033[0;32mYour transfer has been saved!\033[0m");
    }
}

void savings_account()
{
    system("cls");
    printf("<=============================>\n");
    printf("<------ Savings Account ------>\n");
    printf("<=============================>\n");
    printf("<-------- '13.08*AA' --------->\n");
    printf("<=============================>\n");
    char filename_savings[40], filename_open[40];
    float final_amount, initial_deposit;
    int time;

    fflush(stdin);
    printf("Type the name of your savings file(max 20 characters): ");
    scanf("%40[^\n]s", filename_aux);
    sprintf(filename_savings, "./savings_%s.txt", filename_aux);
    sprintf(filename_open, "savings_%s.txt", filename_aux);

    fflush(stdin);
    printf("\nEnter the amount you want to invest: ");
    scanf("%f", &initial_deposit);

    fflush(stdin);
    printf("\nFor how much time do you want to keep this amount invested (months)? ");
    scanf("%d", &time);

    FILE *file_savings;
    file_savings = fopen(filename_savings, "a");
    if (filename_savings == NULL)
    {
        printf("\033[31m\n The savings file could not be opened\033[0m");
        exit(1);
    }

    final_amount = initial_deposit;
    for (int i = 0; i < time; i++)
    {
        final_amount += final_amount * 0.0109;
    }
    fprintf(file_savings, "Saving: \n    Money invested: %.2lf\n", initial_deposit);
    fprintf(file_savings, "    For: %d months\n", time);
    fprintf(file_savings, "Rendimento Final: %.2lf\n", final_amount);

    fclose(file_savings);
    system(filename_open);
}

int verify_date(int num, int dia, int mes, int ano) // This function verifies if a date is either 1 month or a year past.
{
    int aux;
    time_t horario;
    horario = time(NULL);
    struct tm tm = *localtime(&horario);
    if (num == 12)
    {
        if ((tm.tm_mday + ((tm.tm_mon + 1) * 30) + ((tm.tm_year + 1900) * 12 * 30)) - (dia + (mes * 30) + (ano * 12 * 30)) <= 360)
        {
            aux = 1;
        }
        else
        {
            aux = 0;
        }
    }
    else if (num == 1)
    {
        if ((tm.tm_mday + ((tm.tm_mon + 1) * 30) + ((tm.tm_year + 1900) * 12 * 30)) - (dia + (mes * 30) + (ano * 12 * 30)) <= 30)
        {
            aux = 1;
        }
        else
        {
            aux = 0;
        }
    }
    return aux;
}

void report_12() // Prints the last 12 months transactions and creates a txt for the user.
{
    system("cls");
    printf("<=================================>\n");
    printf("<----- Last 12 Months Report ----->\n");
    printf("<=================================>\n");

    char filename_report_12_aux[50], filename_report_12[50], filename[50], filename_open[50];
    printf("Type the name of your binary file: ");
    fflush(stdin);
    scanf("%50[^\n]s", filename_report_12_aux);

    sprintf(filename, "./Files/%s.txt", filename_report_12_aux);
    sprintf(filename_report_12, "./report_12_%s.txt", filename_report_12_aux);
    sprintf(filename_open, "report_12_%s.txt", filename_report_12_aux);

    FILE *file;
    FILE *file_2;

    file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("\033[31m\n The binary file could not be opened\033[0m");
        exit(1);
    }
    file_2 = fopen(filename_report_12, "w");
    if (file_2 == NULL)
    {
        printf("\033[31m\n The file could not be opened\033[0m");
        exit(1);
    }

    data new_transaction;
    fread(&new_transaction, sizeof(data), 1, file);
    do // This structure prints in the txt the struct received in data new_transaction;
    {
        if (verify_date(12, new_transaction.day, new_transaction.month, new_transaction.year) == 1)
        {
            if (new_transaction.identifier == 1) // Transaction case.
            {
                if (new_transaction.money > 0)
                {
                    fprintf(file_2, "Receipt: \n    Categorie: %s\n", new_transaction.categorie);
                    fprintf(file_2, "    Money received: $%.2lf\n", new_transaction.money);
                }
                else
                {
                    fprintf(file_2, "Expense: \n    Categorie: %s\n", new_transaction.categorie);
                    fprintf(file_2, "    Money spent: $%.2lf\n", new_transaction.money);
                }
                fprintf(file_2, "    Description: %s\n", new_transaction.description);
                fprintf(file_2, "    Date: %d/%d/%d\n", new_transaction.day, new_transaction.month, new_transaction.year);
            }
            else if (new_transaction.identifier == 2) // Transfer case.
            {
                fprintf(file_2, "Money Transfer: \n    To: %s\n", new_transaction.categorie);
                fprintf(file_2, "    Transfered: $%.2lf\n", new_transaction.money);
                fprintf(file_2, "    Description: %s\n", new_transaction.description);
                fprintf(file_2, "    Date: %d/%d/%d\n", new_transaction.day, new_transaction.month, new_transaction.year);
            }
        }
        fread(&new_transaction, sizeof(data), 1, file);
    } while (!feof(file));

    printf("\n<========================================================>\n");
    printf("\033[0;32mYour year report was created as: %s\033[0m\n", filename_report_12);
    printf("<========================================================>\n");

    fclose(file);
    fclose(file_2);

    system(filename_open);
}

void report_1() // Prints the last month transactions and creates a txt for the user.
{
    system("cls");
    printf("<=================================>\n");
    printf("<------- Last Month Report ------->\n");
    printf("<=================================>\n");

    char filename_report_1_aux[50], filename_report_1[50], filename[50], filename_open[50];

    printf("Type the name of your binary file: ");
    fflush(stdin);
    scanf("%50[^\n]s", filename_report_1_aux);

    sprintf(filename, "./Files/%s.txt", filename_report_1_aux);
    sprintf(filename_report_1, "./report_1_%s.txt", filename_report_1_aux);
    sprintf(filename_open, "report_1_%s.txt", filename_report_1_aux);
    FILE *file;
    FILE *file_2;

    file = fopen(filename, "rb"); // Reading the binary

    if (file == NULL)
    {
        printf("\033[31m\n The binary file could not be opened\033[0m");
        exit(1);
    }

    file_2 = fopen(filename_report_1, "w"); // Opening the txt to receive information from the binary

    if (file_2 == NULL)
    {
        printf("\033[31m\n The file could not be opened\033[0m");
        exit(1);
    }

    data new_transaction;
    fread(&new_transaction, sizeof(data), 1, file);
    do // This structure prints in the txt the struct received in data new_transaction;
    {
        if (verify_date(1, new_transaction.day, new_transaction.month, new_transaction.year) == 1)
        {
            if (new_transaction.identifier == 1) // Transaction case.
            {
                if (new_transaction.money > 0)
                {
                    fprintf(file_2, "Receipt: \n    Categorie: %s\n", new_transaction.categorie);
                    fprintf(file_2, "    Money received: $%.2lf\n", new_transaction.money);
                }
                else
                {
                    fprintf(file_2, "Expense: \n    Categorie: %s\n", new_transaction.categorie);
                    fprintf(file_2, "    Money spent: $%.2lf\n", new_transaction.money);
                }
                fprintf(file_2, "    Description: %s\n", new_transaction.description);
                fprintf(file_2, "    Date: %d/%d/%d\n", new_transaction.day, new_transaction.month, new_transaction.year);
            }
            else if (new_transaction.identifier == 2) // Transfer case.
            {
                fprintf(file_2, "Money Transfer: \n    To: %s\n", new_transaction.categorie);
                fprintf(file_2, "    Transfered: $%.2lf\n", new_transaction.money);
                fprintf(file_2, "    Description: %s\n", new_transaction.description);
                fprintf(file_2, "    Date: %d/%d/%d\n", new_transaction.day, new_transaction.month, new_transaction.year);
            }
        }
        fread(&new_transaction, sizeof(data), 1, file);
    } while (!feof(file));

    printf("\n<========================================================>\n");
    printf("\033[0;32mYour year report was created as: %s\033[0m\n", filename_report_1);
    printf("<========================================================>\n");

    fclose(file);
    fclose(file_2);
    system(filename_open);
}