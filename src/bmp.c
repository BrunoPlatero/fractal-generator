#include <stdio.h>
#include "bmp.h"

int round4(int x) {
    return x % 4 == 0 ? x : x - x % 4 + 4;
}

void write_bmp(char *filename, char rgb[], int length, int width) {
    
    int height = (length / 3) / width;
    int bitmap_size = height * round4(width * 3);

	// Allocate a buffer to store the bitmap data. Fill it with zeros so
	// we don't leave any traces of our memory in unused spaces.
    char *bitmap = (char *) malloc(bitmap_size * sizeof(char));
    for (int i = 0; i < bitmap_size; i++) bitmap[i] = 0;

    for (int row = 0; row < height; row++) {
		
        // Copy pixel data in BGR order, padding each row to the
		// next multiple of 4 bytes.
        for (int col = 0; col < width; col++) {
            for (int color = 0; color < 3; color++) {
                bitmap[row * round4(width * 3) + col * 3 + color]
                = rgb[3*(row * width + col) + (2 - color)];
            }
        }
    }
}