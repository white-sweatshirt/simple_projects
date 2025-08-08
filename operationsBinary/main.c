#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Amongst of all document there is convention to use (first , secund, result) -
#define MAX_LENGHT 100
// t - is type of table must be a pointer to its first element
#define freeMemoryFromTable(t, s, n) \
    for (int i = 0; i < (n); i++)    \
    {                                \
        t temp = (s)++;              \
        free(temp);                  \
    }
// text fucntions
void copyAllButNLastCharacters(char *source, char *destination, int n)
{
    int lenght = strlen(source);
    if (lenght > n)
        strncpy(destination, source, lenght - n);
}
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

// end of text functions

// Number to Binary
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
void fillWithZeros(char *number, int max)
{
    // I need to fill it all ummm
    for (int i = 0; i < max - 1; i++)
        *number++ = '0';
    *++number = '\0';
}
char *findFirstOneFromEnd(char *beggingOfstring, char *endOfString)
{

    char *walker = endOfString;
    // Assumes that string s is filled with zeros and ones
    // Assumes that string s is at end of it that is it is in position before ending :'\0'
    while (beggingOfstring < walker && *walker != '1')
        walker--;
    if (beggingOfstring == walker && *beggingOfstring != '1')
        return NULL;
    else
        return walker;
}
char complateLenghtOf2To1(char *number1, char *number2)
{
    // WIP
    if (strlen(number1) > strlen(number2))
    {
        char *walker2 = goToEndString(number2); // at place of '\0'
        reverse(number2);
        int difrence = strlen(number1) - strlen(number2);
        for (int i = 0; i < difrence + 1; i++) //+1 is for '\0'
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
void binaryAdditionNoResultTable(char *unChanging, char *changingOne)
{
    // It assumes that both are string of characters of 1 and 0 and that they are finshed with '\0'
    char *result = (char *)calloc(MAX_LENGHT, sizeof(char));
    binaryAdditionThreeDifrentTables(unChanging, changingOne, result);
    strcpy(changingOne, result);

    *(changingOne + (goToEndString(result) - result + 1)) = '\0';
    free(result);
}
void binaryAddition(char *first, char *secund, char *result)
{
    if (first == result)
        binaryAdditionNoResultTable(secund, first);
    else if (secund == result)
        binaryAdditionNoResultTable(first, secund);
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
    if (*result == '1')
        *result = '0';
    else
        printf("podales liczbe 2>1");
    // gives as result string of characters reperesenting subtraction from first secund
}

void binaryAdditionToPartOfSecund(char *first, char *secund, char *result, int numberOfCharactersToAdd)
{
    // 1.Assumes that secund is pointer to binary number
    // In form of string of charcters ended with '\0'
    // 2.Assumes that endOfPartOfSecund is a pointer to last number from right(from secund)
    // to with we should add numbers from first number(pointed by pointer first)
    // 3. Assumes that result is string filled with zeors and that it is ended with '\0'
    // Its job is to produce addtion of only first few characters from secund combined with the first

    char *tableForNFirstCharacteres = (char *)calloc(MAX_LENGHT, sizeof(char));

    copyAllButNLastCharacters(secund, tableForNFirstCharacteres, numberOfCharactersToAdd);
    binaryAddition(first, tableForNFirstCharacteres, tableForNFirstCharacteres);

    reverse(result);
    reverse(tableForNFirstCharacteres); // reversing tables in order to make addition possiablle

    strcpy(result + numberOfCharactersToAdd, tableForNFirstCharacteres); // first n characters are allready good.
    reverse(result);
    free(tableForNFirstCharacteres);
}

// To Do: Binary Division and Multiplication
void binaryMultiplication(char *first, char *secund, char *result, int max)
{
    // 1.Assumes that result is emty i.e there is no important information on it
    // 2.Assumes that first and secund are binary numbers in form of string with ending of '\0'
    char *end2, *walker2;
    end2 = walker2 = goToEndString(secund);
    fillWithZeros(result, max); // takes care of postions ommited because lack need of addtion.
    while ((walker2 = findFirstOneFromEnd(secund, walker2)) != NULL && secund <= walker2)
    {
        binaryAdditionToPartOfSecund(first, result, result, end2 - walker2);
        walker2--;
    }
}

void drawNiceLine()
{
    for (int i = 0; i < 13; i++)
        printf("-");
    puts("");
}
int main()
{
    char number1[MAX_LENGHT], number2[MAX_LENGHT], result[MAX_LENGHT] = {'\0'};
    int a = 12;
    int b = 200, c = 0;

    conversionToBinary(number1, a, MAX_LENGHT);
    conversionToBinary(number2, b, MAX_LENGHT);

    printf("%13s\n*%12s\n", number1, number2);
    drawNiceLine();

    binaryMultiplication(number1, number2, result, MAX_LENGHT);
    printf("%13s\n", result);
    converstionToDecimal(result, &c);
    converstionToDecimal(number2, &b);
    printf("%d * %d = %d\n", a, b, c);
    return 0;
}