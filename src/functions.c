#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char name[40], filename_aux[21], filename[30];
typedef struct // Receipt class
{
    double money;
    char description[100], categorie[20];
    int day, month, year;
} data;

void new_receipt() // If it exists, ads a new receipt (struct) in the binary file, on the contrary, the function creates a new binary file.
{
    system("cls");
    printf("<=============================>\n");
    printf("<-------- New Receipt -------->\n");
    printf("<=============================>\n");

    data new_receipt;
    fflush(stdin);
    printf("First of all, please type your first and last name: ");
    scanf("%40[^\n]s", name);
    printf("Okay %s, now you can add your new receipt.\n\n", name);

    fflush(stdin);
    printf("Type the name of your binary file(max 20 characters): ");
    scanf("%20[^\n]s", filename_aux);
    sprintf(filename, "./Files/%s.txt", filename_aux);

    fflush(stdin);
    printf("\nPlease, type the categorie of the receipt: ");
    scanf("%20[^\n]", new_receipt.categorie);

    fflush(stdin);
    printf("Please, type the description of the receipt: ");
    scanf("%100[^\n]", new_receipt.description);

    printf("Please, type the amount of money spent on the receipt: ");
    scanf("%lf", &new_receipt.money);

    fflush(stdin);
    printf("Please, type the DATE of the receipt (dd mm yyyy): ");
    scanf("%d %d %d", &new_receipt.day, &new_receipt.month, &new_receipt.year);

    FILE *file;
    if (file = fopen(filename, "ab"))
    {
        fwrite(&new_receipt, sizeof(data), 1, file);
        fclose(file);
    }
    else
    {
        fopen(filename, "wb");
        fwrite(&new_receipt, sizeof(data), 1, file);
        fclose(file);
    }
}

int verify_date(int num, int dia, int mes, int ano) // This function verifies if a date is either 1 month or 12 months past.
{
    int aux;
    time_t horario;
    horario = time(NULL);
    struct tm tm = *localtime(&horario);
    if (num == 12)
    {
        if ((tm.tm_mday + ((tm.tm_mon + 1) * 30) + ((tm.tm_year + 1900) * 12 * 30)) - (dia + (mes * 30) + (ano * 12 * 30)) <= 365)
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

void report_12() // Prints the last 12 months receipts and creates a txt for the user.
{
    system("cls");
    printf("<=================================>\n");
    printf("<----- Last 12 Months Report ----->\n");
    printf("<=================================>\n");

    char filename_report_12_aux[30], filename_report_12[30], filename[30];
    printf("Type the name of your binary file: ");
    fflush(stdin);
    scanf("%20[^\n]s", filename_report_12_aux);

    sprintf(filename, "./Files/%s.txt", filename_report_12_aux);
    sprintf(filename_report_12, "./Files/report_12_%s.txt", filename_report_12_aux);

    FILE *file;
    FILE *file_2;

    file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("\n The file could not be opened");
        exit(1);
    }
    file_2 = fopen(filename_report_12, "w");
    if (file_2 == NULL)
    {
        printf("\n The file could not be opened");
        exit(1);
    }

    data new_receipt;
    fread(&new_receipt, sizeof(data), 1, file);
    do // This structure prints in the txt the struct received in data new_receipt;
    {
        if (verify_date(12, new_receipt.day, new_receipt.month, new_receipt.year) == 1)
        {
            fprintf(file_2, "Receipt: \n    Categorie: %s\n", new_receipt.categorie);
            fprintf(file_2, "    Money spent: $%.2lf\n", new_receipt.money);
            fprintf(file_2, "    Description: %s\n", new_receipt.description);
            fprintf(file_2, "    Date: %d/%d/%d\n", new_receipt.day, new_receipt.month, new_receipt.year);
            printf("\nSpent: $%.2lf\nCategorie: %s\nDescription: %s\nDate: %d/%d/%d\n", new_receipt.money, new_receipt.categorie, new_receipt.description, new_receipt.day, new_receipt.month, new_receipt.year);
        }
        fread(&new_receipt, sizeof(data), 1, file);
    } while (!feof(file));
    printf("<============================>\n");
    printf("Your 12 month report was created as: %s\n", filename_report_12);

    fclose(file);
    fclose(file_2);
}

void report_1() // Prints the last month receipts and creates a txt for the user.
{
    system("cls");
    printf("<=================================>\n");
    printf("<------- Last Month Report ------->\n");
    printf("<=================================>\n");

    char filename_report_1_aux[30], filename_report_1[30], filename[30];
    printf("Type the name of your binary file: ");
    fflush(stdin);
    scanf("%20[^\n]s", filename_report_1_aux);

    sprintf(filename, "./Files/%s.txt", filename_report_1_aux);
    sprintf(filename_report_1, "./Files/report_1_%s.txt", filename_report_1_aux);
    printf("\nYour last month report was created as: %s\n", filename_report_1);
    printf("<============================>\n");

    FILE *file;
    FILE *file_2;

    file = fopen(filename, "rb"); // Reading the binary

    if (file == NULL)
    {
        printf("\n The file could not be opened");
        exit(1);
    }

    file_2 = fopen(filename_report_1, "w"); // Opening the txt to receive information from the binary

    if (file_2 == NULL)
    {
        printf("\n The file could not be opened");
        exit(1);
    }

    data new_receipt;
    fread(&new_receipt, sizeof(data), 1, file);
    do
    {
        if (verify_date(1, new_receipt.day, new_receipt.month, new_receipt.year) == 1)
        {
            fprintf(file_2, "Receipt: \n    Categorie: %s\n", new_receipt.categorie);
            fprintf(file_2, "    Money spent: $%.2lf\n", new_receipt.money);
            fprintf(file_2, "    Description: %s\n", new_receipt.description);
            fprintf(file_2, "    Date: %d/%d/%d\n", new_receipt.day, new_receipt.month, new_receipt.year);
            printf("\nSpent: $%.2lf\nCategorie: %s\nDescription: %s\nDate: %d/%d/%d\n", new_receipt.money, new_receipt.categorie, new_receipt.description, new_receipt.day, new_receipt.month, new_receipt.year);
        }
        fread(&new_receipt, sizeof(data), 1, file);
    } while (!feof(file));

    fclose(file);
    fclose(file_2);
}