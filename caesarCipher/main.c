#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "caesarCipher.h"

char* caesarEncode(char* text, int displacement); 
const char* abcdary = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    char textInput[100]; 
    const unsigned int displacement = 5; //de momento esto será una variable constante a la que dejaremos como 3

    printf("\nDesplazamiento establecido: %d\n", displacement);

    printf("\nIntroduce un texto a cifrar: ");
    fgets(textInput, sizeof(textInput), stdin); // permite espacios y símbolos


    printf("El resultado cifrado en Cesar es: %s\n", caesarEncode(textInput, displacement));

    return 0;
}