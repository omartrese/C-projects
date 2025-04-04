#include <ctype.h>
#include <string.h>
#include "caesarCipher.h"

char* caesarEncode(char* text, int displacement)
{
    static char result[100]; // static para que el puntero no apunte a memoria local
    int length = strlen(text);
    displacement = displacement % 26; 

    memset(result, 0, sizeof(result)); 

    for (int i = 0; i < length; i++)
    {
        char ch = text[i];
        char encodedChar;

        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            encodedChar = (ch - base + displacement) % 26 + base;
        } else {
           encodedChar = ch;           
        }

        result[i] = encodedChar;
    }

    return result;
}