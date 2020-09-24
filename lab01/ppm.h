#ifndef LAB01_PPM_H
#define LAB01_PPM_H

#include <iostream>

void ppmRead(char *filename, unsigned char *data, int *w, int *h);

void ppmWrite(const char *filename, unsigned char *data, int w, int h);

#endif //LAB01_PPM_H
