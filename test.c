#include <stdio.h>

void changeStrings(char strings[][100])
{
    printf("%s\n", strings[0]);
    printf("%s\n", strings[1]);
    strings[0][0] = '1';
    strings[1][0] = '2';
    return;
}

int main()
{
    char str[] = {"Hello"};
    changeStrings(strings);

    printf("after\n");
    printf("%s\n", strings[0]);
    printf("%s\n", strings[1]);
}