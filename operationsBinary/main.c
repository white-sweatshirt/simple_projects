#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGHT 100
// Number to Binary
char *goToEndString(char *s)
{
    // Assumptions: this pointer is to string of characters
    // Ended with '\0'
    while (*s++ != '\0')
        ;
    return s - 2;
}
void reverse(char *s)
{
    // Assumptions: this pointer is to string of characters
    // Ended with '\0'
    char *walker = s;
    while (*walker++ != '\0')
        ;
    char temp = 0;
    walker--;
    while (walker > s)
    {
        temp = *s;
        *s++ = *(--walker);
        *walker = temp;
    } // protection from going to far i.e changing charater before with one later
}
void conversionToBinary(char *s, int number, int max)
{
    // Asumption s is intilaized with '\0' on first position
    int i = 0;
    char stack[MAX_LENGHT];
    char *walker = s;
    while (number && i < max)
    {
        *(s + i++) = number % 2 + '0';
        number >>= 1;
    }
    *(s + i + 1) = '\0';
    reverse(s);
}
void converstionToDecimal(char *s, int *number)
{
    *number = 0;
    while (*s != '\0')
        *number = *number * 2 + (*s++ - '0');
}

void complementNumber(char *number)
{
    // Assumptions: those pointers are to string of characters
    // Ended with '\0'
    while (*number != '\0')
        if (*number == '0')
            *number++ = '1';
        else
            *number++ = '0';
}
char *findFirstOneInString(char *s)
{
    // Assumes that string s is filled with zeros and ones
    while (*s != '\0' && *s != '1')
        *s++;
    if (!s)
        return NULL;
    else
        return s;
}
char complateLenghtOf2To1(char *number1, char *number2)
{
    // WIP
    if (strlen(number1) > strlen(number2))
    {
        char *walker2 = goToEndString(number2); // at place of '\0'
        reverse(number2);
        int difrence = strlen(number1) - strlen(number2);
        for (int i = 0; i < difrence+1; i++)//+1 is for '\0'
            *++walker2 = '0';
        *walker2 = '\0';
        reverse(number2);
    }
}
// End of functions for conversions to and from binary!
// i.e  switch zeors with ones
void binaryAdditionThreeDifrentTables(char *first, char *secund, char *result)
{
    // Assumptions: those pointers are to string of characters
    // Ended with '\0'
    int offset = 0;
    char *walker1 = first;
    char *walker2 = secund;
    char *walkerResult = result;
    walker1 = goToEndString(first);
    walker2 = goToEndString(secund);
    while (first <= walker1 && secund <= walker2)
    {
        *walkerResult++ = (*walker1 - '0' + *walker2 - '0' + offset) % 2 + '0';
        offset = ((*walker1-- - '0') + (*walker2-- - '0') + offset >= 2) ? 1 : 0;
    }
    if (first > walker1 && secund > walker2 && offset > 0)
        *walkerResult++ = offset + '0';
    while (first <= walker1)
    {
        *walkerResult++ = (((*walker1 - '0') + offset) % 2) + '0';
        offset = ((*walker1-- - '0') + offset >= 2 ? 1 : 0);
    }
    while (secund <= walker2)
    {
        *walkerResult++ = (((*walker2 - '0') + offset) % 2) + '0';
        offset = ((*walker2-- - '0') + offset >= 2 ? 1 : 0);
    }
    *walkerResult = '\0';
    reverse(result);
}
void binaryAdditionCommonTablesForResoultAndData(char *first, char *unchangedOne)
{

    // Assumptions: those pointers are to string of characters
    // Ended with '\0'
    int offset = 0;
    char *walker1 = first;
    char *result;

    char *walkerToUnchanged = unchangedOne;
    walker1 = goToEndString(first);
    result = calloc(walker1 - first + 1, sizeof(char));
    char *walkerResult = result;

    if (!result)
    {
        printf("brak pamieci!");
        exit(1);
    }
    walkerToUnchanged = goToEndString(unchangedOne);
    while (first <= walker1 && unchangedOne <= walkerToUnchanged)
    {
        *walkerResult++ = (*walker1 - '0' + *walkerToUnchanged - '0' + offset) % 2 + '0';
        offset = ((*walker1-- - '0') + (*walkerToUnchanged-- - '0') + offset >= 2) ? 1 : 0;
    }
    if (first > walker1 && unchangedOne > walkerToUnchanged && offset > 0)
        *walkerResult++ = offset + '0';
    while (first <= walker1)
    {
        *walkerResult++ = (((*walker1 - '0') + offset) % 2) + '0';
        offset = ((*walker1-- - '0') + offset >= 2 ? 1 : 0);
    }
    while (unchangedOne <= walkerToUnchanged)
    {
        *walkerResult++ = (((*walkerToUnchanged - '0') + offset) % 2) + '0';
        offset = ((*walkerToUnchanged-- - '0') + offset >= 2 ? 1 : 0);
    }
    *walkerResult = '\0';
    reverse(result);
    strcpy(first, result);
    for (int i = 0; i < walker1 - first + 1; i++)
    {
        char *temp = result++;
        free(temp);
    }
}

void binaryAddition(char *first, char *secund, char *result)
{
    if (first == result)
        binaryAdditionCommonTablesForResoultAndData(first, secund);
    else if (secund == result)
        binaryAdditionCommonTablesForResoultAndData(secund, first);
    else
        binaryAdditionThreeDifrentTables(first, secund, result);
}
void binarySubtraction(char *first, char *secund, char *result)
{
    // Function assumes that all pointers lead to strings ended with '\0' on last position
    // Also assumes that first>secund
    char resultOfCompletion[MAX_LENGHT], oneInBinary[] = "1"; // represents one in binary... its to easy to convert
    strcpy(resultOfCompletion, secund);

    complateLenghtOf2To1(first, resultOfCompletion);
    complementNumber(resultOfCompletion); // complements number according to algorithm

    binaryAddition(resultOfCompletion, oneInBinary, resultOfCompletion); // adds one binary to complemented value

    binaryAddition(first, resultOfCompletion, result); // adds first and prepered CompletentionString
    char *s = findFirstOneInString(result);
    if (*result == '1')
        *result = '0';
    else
        printf("podales liczbe 2>1");
    // gives as result string of characters reperesenting subtraction from first secund
}
// To Do: Binary Multiplication and division
void drawNiceLine()
{
    for (int i = 0; i < 13; i++)
        printf("-");
    puts("");
}
int main()
{
    char number1[MAX_LENGHT], number2[MAX_LENGHT], result[MAX_LENGHT] = {'\0'};
    int a = 90;
    int b = 7, c = 0;

    conversionToBinary(number1, a, MAX_LENGHT);
    conversionToBinary(number2, b, MAX_LENGHT);

    printf("%13s\n-%12s\n", number1, number2);
    drawNiceLine();

    binarySubtraction(number1, number2, result);
    printf("%13s\n", result);
    converstionToDecimal(result, &c);
    converstionToDecimal(number2, &b);
    printf("%d - %d = %d\n", a, b, c);
    return 0;
}