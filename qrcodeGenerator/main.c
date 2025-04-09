#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "qrcodegen.h"

#define MAX_INPUT_SIZE 100  // Tamaño máximo para la entrada del usuario

static void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
}

void createQRCode(const char *text)
{
    // Eliminamos el uso innecesario de buffer
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_FOR_VERSION(qrcodegen_VERSION_MAX)];
    uint8_t qrcode[qrcodegen_BUFFER_LEN_FOR_VERSION(qrcodegen_VERSION_MAX)];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (ok)
        printQr(qrcode);
    else
        fprintf(stderr, "Failed to generate QR code\n");
}

int main()
{
    printf("QR Code Generator\n");

    char text[MAX_INPUT_SIZE];
    if (fgets(text, sizeof(text), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Eliminar el salto de línea al final de la entrada
    text[strcspn(text, "\n")] = '\0';

    createQRCode(text);

    return 0;
}