#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearIB()
{
    while (getchar() != '\n')
        ;
}

void getInput(void *input, char *format, const char *message)
{
    char temp = 0;

    do
    {
        printf("%s", message);
        int status = scanf(format, input);
        if (*((char *)input) == '\n')
        {
            continue;
        }
        if (status != 1)
        {
            printf("Invalid input, the format is %s, try again\n", format);
            clearIB();
            continue;
        }
        status = scanf("%c", &temp);
        if (temp != '\n')
        {
            printf("Invalid input, the format is %s, try again\n", format);
            clearIB();
        }
    } while (temp != '\n');
}

void swapStrings(char *string1, char *string2)
{
    size_t string1Length = strlen(string1);
    size_t string2Length = strlen(string2);
    size_t maxLength = (string1Length > string2Length) ? string1Length : string2Length;
    char *temp = malloc(maxLength + 1);
    strcpy(temp, string1);
    strcpy(string1, string2);
    strcpy(string2, temp);

    free(temp);
    return;
}

// order = 1 for ascending, order = -1 for descending
int sortStrings(char **strings, size_t stringsQuantity, int order)
{
    if (order == 0)
        return order;

    for (int i = 0; i < stringsQuantity - 1; i++)
    {
        for (int j = i + 1; j < stringsQuantity; j++)
        {
            const int compareResult = strcmp(strings[i], strings[j]);
            if (compareResult * order > 0)
            {
                swapStrings(strings[i], strings[j]);
            }
        }
    }

    return order;
}

void printStrings(char **strings, size_t stringsQuantity)
{
    for (int i = 0; i < stringsQuantity; i++)
    {
        printf("%s\n", strings[i]);
    }

    return;
}

void test()
{
    size_t maxStringLength = 10;
    size_t stringsQuantity = 3;
    char **strings = malloc(stringsQuantity);
    for (int i = 0; i < stringsQuantity; i++)
    {
        strings[i] = malloc(maxStringLength + 1);
    }
    strcpy(strings[0], "Привіт!");
    strcpy(strings[1], "Байбай.");
    strcpy(strings[2], "Хелло))");

    sortStrings(strings, stringsQuantity, 1);

    printStrings(strings, stringsQuantity);

    for (int i = 0; i < stringsQuantity; i++)
    {
        free(strings[i]);
        printf("freed\n");
    }
    printf("freed every string\n");

    free(strings);

    return;
}

int main()
{
    test();
    return 0;
}