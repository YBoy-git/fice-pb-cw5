#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100
#define MAX_STRINGS_QUANTITY 100

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
    char *temp = malloc((maxLength + 1) * sizeof(char));
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

bool isInputValid(char *input, size_t maxLength)
{
    size_t inputLength = strlen(input);
    if (inputLength >= maxLength - 1)
    {
        char *lastCharacter = &(input[inputLength - 1]);
        if (*lastCharacter != '\n')
        {
            printf("The input is too big, try again.\n");
            clearIB();
            return false;
        }
    }
    return true;
}

void getString(char *string, size_t maxInputLength)
{
    // to include \n and \0
    maxInputLength += 2;

    char input[maxInputLength];
    do
    {
        // max string length + \n + \0 in ideal string
        fgets(input, maxInputLength, stdin);
    } while (!isInputValid(input, maxInputLength));

    input[strlen(input) - 1] = '\0';
    strcpy(string, input);

    return;
}

// Returns quantity of input strings
size_t getStrings(char **strings)
{
    size_t stringsQuantity = 0;
    char *input = malloc((MAX_STRING_LENGTH) * sizeof(char));

    do
    {
        if (stringsQuantity > 0)
        {
            printf("You've entered %zu string(s)\n", stringsQuantity);
        }
        printf("Enter a string or press ENTER to stop input\n");

        getString(input, MAX_STRING_LENGTH);
        printf("\n");

        if (strlen(input) != 0)
        {
            strings[stringsQuantity] = malloc((strlen(input) + 1) * sizeof(char));
            strcpy(strings[stringsQuantity], input);
            stringsQuantity++;
        }
    } while (strlen(input) != 0 && stringsQuantity < 100);

    return stringsQuantity;
}

void freeStrings(char **strings, size_t stringsQuantity)
{
    for (int i = 0; i < stringsQuantity; i++)
    {
        free(strings[i]);
    }
    free(strings);
}

void UI()
{
    char **strings = malloc(MAX_STRINGS_QUANTITY * sizeof(char *));
    size_t stringsQuantity = getStrings(strings);
    if (stringsQuantity == 0)
    {
        printf("I can't work with empty arrays\n");
        return;
    }
    sortStrings(strings, stringsQuantity, 1);
    printStrings(strings, stringsQuantity);
    freeStrings(strings, stringsQuantity);
    return;
}

void endless(void (*function)())
{
    do
    {
        function();
        printf("Press ENTER to continue and type any key to exit\n");
    } while (getchar() == '\n');

    return;
}

int main()
{
    endless(UI);    

    return 0;
}