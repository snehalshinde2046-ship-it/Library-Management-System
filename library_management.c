#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
    int id;
    char name[100];
    char author[100];
    int quantity;
    
};

void addBook();
void displayBooks();
void searchBook();
void issueBook();
void returnBook();

int main()
{
    int choice;

    while (1)
    {
        printf("\n========== LIBRARY MANAGEMENT SYSTEM ==========\n");

        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                printf("\nExiting Program...\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

void displayBooks()
{
FILE *fp;
struct Book b;
fp = fopen("books.csv", "r");
if (fp == NULL)
{
printf("\nNo records found!\n");
return;
}
printf("\n================ BOOK RECORDS 
================\n");
printf("\n%-10s %-25s %-25s %-10s\n",
"ID",
"BOOK NAME",
"AUTHOR",
"QTY");
printf("--------------------------------------------------------------------------\n");
while (fscanf(fp,
"%d,%99[^,],%99[^,],%d\n",
&b.id
,
b.name
,
b.author
,
&b.quantity) == 4)
{
printf("%-10d %-25s %-25s %-10d\n",
b.id
,
b.name
,
b.author
,
b.quantity);
}
fclose(fp);
}
void searchBook()
{
FILE *fp;
struct Book b;
char searchName[100];
int found = 0;
fp = fopen("books.csv", "r");
if (fp == NULL)
{
printf("\nFile not found!\n");
return;
}
printf("\nEnter Book Name to Search: ");
scanf(" %[^\n]", searchName);
while (fscanf(fp,
"%d,%99[^,],%99[^,],%d\n",
&b.id
,
b.name
,
b.author
,
&b.quantity) == 4)
{
if (strcmp(b.name
, searchName) == 0)
{
printf("\n========== BOOK FOUND 
==========\n");
printf("Book ID : %d\n", b.id
);
printf("Book Name : %s\n", b.name
);
printf("Author : %s\n", b.author
);
printf("Quantity : %d\n", b.quantity);
found = 1;
break;
}
}
if (!found)
{
printf("\nBook not found!\n");
}
fclose(fp);
}


void issueBook()
{
    FILE *fp, *temp;
    struct Book b;

    char issueBookName[100];
    char studentName[100];

    int found = 0;

    fp = fopen("books.csv", "r");
    temp = fopen("temp.csv", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Book Name to Issue: ");
    scanf(" %[^\n]", issueBookName);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", studentName);

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%d\n",
                  &b.id,
                  b.name,
                  b.author,
                  &b.quantity) == 4)
    {
        if (strcmp(b.name, issueBookName) == 0)
        {
            found = 1;

            if (b.quantity > 0)
            {
                b.quantity--;

                printf("\n========== BOOK ISSUED ==========\n");

                printf("Student Name : %s\n", studentName);
                printf("Book Name    : %s\n", b.name);
                printf("Remaining Qty: %d\n", b.quantity);
            }
            else
            {
                printf("\nBook Out of Stock!\n");
            }
        }

        fprintf(temp,
                "%d,%s,%s,%d\n",
                b.id,
                b.name,
                b.author,
                b.quantity);
    }

    fclose(fp);
    fclose(temp);

    remove("books.csv");
    rename("temp.csv", "books.csv");

    if (!found)
    {
        printf("\nBook not found!\n");
    }
}

void returnBook()
{
    FILE *fp, *temp;
    struct Book b;

    char returnBookName[100];
    char studentName[100];

    int found = 0;

    fp = fopen("books.csv", "r");
    temp = fopen("temp.csv", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Book Name to Return: ");
    scanf(" %[^\n]", returnBookName);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", studentName);

    while (fscanf(fp,
                  "%d,%99[^,],%99[^,],%d\n",
                  &b.id,
                  b.name,
                  b.author,
                  &b.quantity) == 4)
    {
        if (strcmp(b.name, returnBookName) == 0)
        {
            b.quantity++;
            found = 1;

            printf("\n========== BOOK RETURNED ==========\n");

            printf("Student Name : %s\n", studentName);
            printf("Book Name    : %s\n", b.name);
            printf("Updated Qty  : %d\n", b.quantity);
        }

        fprintf(temp,
                "%d,%s,%s,%d\n",
                b.id,
                b.name,
                b.author,
                b.quantity);
    }

    fclose(fp);
    fclose(temp);

    remove("books.csv");
    rename("temp.csv", "books.csv");

    if (!found)
    {
        printf("\nBook not found!\n");
    }
}
