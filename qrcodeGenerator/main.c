#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <png.h>
#include "qrcodegen.h"

#define MAX_INPUT_SIZE 100 // Tamaño máximo para la entrada del usuario

// Imprimir el código QR en la consola
static void printQr(const uint8_t qrcode[])
{
    int size = qrcodegen_getSize(qrcode);
    int border = 4;
    for (int y = -border; y < size + border; y++)
    {
        for (int x = -border; x < size + border; x++)
        {
            fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
        }
        fputs("\n", stdout);
    }
    fputs("\n", stdout);
}

// Exportar el código QR a un archivo PNG
void exportarPNG(const uint8_t *qrcode, int size, const char *filename, int scale)
{
    int width = (size + 8) * scale; // Incluir borde de 4 módulos
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        perror("No se pudo abrir el archivo para escribir");
        exit(1);
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    if (setjmp(png_jmpbuf(png)))
    {
        perror("Error durante la creación del PNG");
        fclose(fp);
        exit(1);
    }

    png_init_io(png, fp);
    png_set_IHDR(
        png, info, width, width,
        8, PNG_COLOR_TYPE_GRAY,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    png_bytep row = (png_bytep)malloc(width * sizeof(png_byte));
    if (!row)
    {
        perror("Error al asignar memoria para la fila");
        fclose(fp);
        png_destroy_write_struct(&png, &info);
        exit(1);
    }

    // Generar la imagen con borde y escalado
    for (int y = -4; y < size + 4; y++) // Borde de 4 módulos
    {
        for (int x = -4; x < size + 4; x++)
        {
            uint8_t pixel = (x >= 0 && x < size && y >= 0 && y < size && qrcodegen_getModule(qrcode, x, y)) ? 0 : 255; // 0: negro, 255: blanco
            for (int dx = 0; dx < scale; dx++)
            {
                for (int dy = 0; dy < scale; dy++)
                {
                    row[(x + 4) * scale + dx] = pixel;
                }
            }
        }
        for (int dy = 0; dy < scale; dy++)
        {
            png_write_row(png, row);
        }
    }

    png_write_end(png, NULL);
    fclose(fp);
    free(row);
    png_destroy_write_struct(&png, &info);
}

void createQRCode(const char *text)
{
    // Eliminamos el uso innecesario de buffer
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW; // Error correction level
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_FOR_VERSION(qrcodegen_VERSION_MAX)];
    uint8_t qrcode[qrcodegen_BUFFER_LEN_FOR_VERSION(qrcodegen_VERSION_MAX)];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (ok)
    {
        // printQr(qrcode);
        int size = qrcodegen_getSize(qrcode);
        exportarPNG(qrcode, size, "qr.png", 10); // 10 píxeles por "módulo"
    }
    else
        fprintf(stderr, "Failed to generate QR code\n");
}

int main()
{
    printf("QR Code Generator\n");

    char text[MAX_INPUT_SIZE];
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Eliminar el salto de línea al final de la entrada
    text[strcspn(text, "\n")] = '\0';

    createQRCode(text);

    return 0;
}