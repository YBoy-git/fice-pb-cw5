#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

const int MAX_STRING_LENGTH = 100;
const int MAX_STRINGS_QUANTITY = 100;

const char inputTypes[] = {'u', 'r', '\0'};
const char sortingTypes[] = {'a', 'd', '\0'};

void clearIB()
{
    while (getchar() != '\n')
        ;
}

void getInput(void *input, char *format, const char *prompt)
{
    char temp = 0;

    do
    {
        printf("%s", prompt);
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

bool wasMemoryAllocated(void *pointer)
{
    if (pointer == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    return true;
}

void swapStrings(char string1[], char string2[])
{
    size_t string1Length = strlen(string1);
    size_t string2Length = strlen(string2);
    size_t maxLength = fmax(string1Length, string2Length);

    char *temp = malloc((maxLength + 1) * sizeof(char));
    wasMemoryAllocated(temp);

    string1 = realloc(string1, (string2Length + 1) * sizeof(char));
    wasMemoryAllocated(string1);
    string2 = realloc(string2, (string1Length + 1) * sizeof(char));
    wasMemoryAllocated(string2);

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

bool isOptionValid(char choice, const char *options)
{
    if (!strchr(options, choice))
    {
        printf("Invalid option, try again\n");
        return false;
    }
    return true;
}

void getOption(char *choice, const char *options, const char *prompt)
{
    do
    {
        getInput(choice, "%c", prompt);
    } while (!isOptionValid(*choice, options));
}

bool isStringValid(char *input, size_t maxLength)
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
    } while (!isStringValid(input, maxInputLength));

    input[strlen(input) - 1] = '\0';
    strcpy(string, input);

    return;
}

// Returns quantity of input strings
size_t getStringsFromUser(char **strings)
{
    size_t stringsQuantity = 0;
    char *input = malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
    wasMemoryAllocated(input);

    do
    {
        if (stringsQuantity > 0)
        {
            printf("You've entered %zu string(s)\n", stringsQuantity);
        }
        printf("Enter up to %d strings (with max length %d) or press ENTER to stop input \n", MAX_STRINGS_QUANTITY, MAX_STRING_LENGTH);

        getString(input, MAX_STRING_LENGTH);
        printf("\n");

        if (strlen(input) != 0)
        {
            strings[stringsQuantity] = malloc((strlen(input) + 1) * sizeof(char));
            wasMemoryAllocated(strings[stringsQuantity]);

            strcpy(strings[stringsQuantity], input);
            stringsQuantity++;
        }

        if (strlen(input) == 0 && stringsQuantity == 0)
        {
            printf("Please, pass at least 1 string\n");
            continue;
        }
    } while ((strlen(input) != 0 && stringsQuantity < MAX_STRINGS_QUANTITY) || stringsQuantity == 0);

    free(input);

    return stringsQuantity;
}

bool isStringsLengthValid(size_t stringsLength)
{
    if (stringsLength == 0)
    {
        printf("Can't generate 0-length strings\n");
        return false;
    }
    if (stringsLength > MAX_STRING_LENGTH)
    {
        printf("Too big string length\n");
        return false;
    }

    return true;
}

void getStringsLength(size_t *stringsLength)
{
    char prompt[40];
    sprintf(prompt, "Enter string length (max %d): ", MAX_STRING_LENGTH);

    do
    {
        getInput(stringsLength, "%zu", prompt);
    } while (!isStringsLengthValid(*stringsLength));

    return;
}

bool isStringsQuantityValid(size_t stringsQuantity)
{
    if (stringsQuantity == 0)
    {
        printf("Can't generate 0 strings\n");
        return false;
    }
    if (stringsQuantity > MAX_STRINGS_QUANTITY)
    {
        printf("Too many strings\n");
        return false;
    }

    return true;
}

void getStringsQuantity(size_t *stringsQuantity)
{
    char prompt[70];
    sprintf(prompt, "How many strings would you like to generate? (max %d): ", MAX_STRINGS_QUANTITY);
    do
    {
        getInput(stringsQuantity, "%zu", prompt);
    } while (!isStringsQuantityValid(*stringsQuantity));

    return;
}

char getRandomChar()
{
    const int min = 32;
    const int max = 126;
    const int range = max - min + 1;
    return rand() % range + min;
}

void generateRandomString(char *string, size_t stringLength)
{
    for (int i = 0; i < stringLength; i++)
    {
        string[i] = getRandomChar();
    }
    string[stringLength] = '\0';

    return;
}

size_t getRandomStrings(char **strings, size_t stringsLength, size_t stringsQuantity)
{
    for (int i = 0; i < stringsQuantity; i++)
    {
        strings[i] = malloc((stringsLength + 1) * sizeof(char));
        wasMemoryAllocated(strings[i]);

        generateRandomString(strings[i], stringsLength);
    }

    return stringsQuantity;
}

size_t getStrings(char ***strings, char input)
{
    switch (input)
    {
    case 'u':
        *strings = malloc(MAX_STRINGS_QUANTITY * sizeof(char *));
        wasMemoryAllocated(*strings);

        return getStringsFromUser(*strings);
    case 'r':
        size_t stringsQuantity = 0;
        getStringsQuantity(&stringsQuantity);
        *strings = malloc(stringsQuantity * sizeof(char *));
        wasMemoryAllocated(*strings);

        size_t stringsLength = 0;
        getStringsLength(&stringsLength);

        return getRandomStrings(*strings, stringsLength, stringsQuantity);
    default:
        printf("Invalid input type\n");
        return 0;
    }
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
    char inputType = 0;
    getOption(&inputType, inputTypes, "Enter input type (u - user input, r - random): ");

    char **strings = NULL;
    size_t stringsQuantity = getStrings(&strings, inputType);

    printf("--- Input strings:\n");
    printStrings(strings, stringsQuantity);
    printf("\n");

    char sortingType = 0;
    getOption(&sortingType, sortingTypes, "Enter sorting type (a - ascending, d - descending): ");

    sortStrings(strings, stringsQuantity, (sortingType == 'a') ? 1 : -1);

    printf("--- Sorted strings:\n");
    printStrings(strings, stringsQuantity);
    printf("\n");

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

void test_swapStrings()
{
    char *str1 = malloc(10 * sizeof(char));
    char *str2 = malloc(5 * sizeof(char));
    strcpy(str1, "123456789");
    strcpy(str2, "1234");
    swapStrings(str1, str2);
    printf("%s\n", str1);
    printf("%s\n", str2);
    free(str1);
    free(str2);
    return;
}

void test_getString()
{
    char *string = malloc(11 * sizeof(char));
    getString(string, 10);
    printf("%s\n", string);
    free(string);
    return;
}

void test_getStringsFromUser()
{
    char **strings = malloc(MAX_STRINGS_QUANTITY * sizeof(char *));

    size_t stringsQuantity = getStringsFromUser(strings);
    printStrings(strings, stringsQuantity);
    freeStrings(strings, stringsQuantity);
    return;
}

int main()
{
    srand(time(NULL));

    endless(UI);

    // test_swapStrings();
    // test_getString();
    // test_getStringsFromUser();

    return 0;
}
