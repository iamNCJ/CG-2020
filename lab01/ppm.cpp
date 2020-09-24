#define _CRT_SECURE_NO_WARNINGS

#include "ppm.h"

void ppmRead(char *filename, unsigned char *data, int *w, int *h) {
    char header[1024];
    FILE *fp = nullptr;
    int line = 0;

    fp = fopen(filename, "rb");
    while (line < 2) {
        fgets(header, 1024, fp);
        if (header[0] != '#') {
            ++line;
        }
    }
    sscanf(header, "%d %d\n", w, h);
    fgets(header, 20, fp);
    fread(data, (*w) * (*h) * 3, 1, fp);

    fclose(fp);
}

void ppmWrite(const char *filename, unsigned char *data, int w, int h) {
    FILE *fp;
    fp = fopen(filename, "wb");

    fprintf(fp, "P6\n%d %d\n255\n", w, h);
    fwrite(data, w * h * 3, 1, fp);

    fclose(fp);
}