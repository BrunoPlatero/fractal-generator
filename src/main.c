#include <stdlib.h>
#include "bmp.h"


int main() {
	int h = 1080;
	int w = 1920;
    char *bmp = malloc(h * w * 3);

	for (int i = 0; i < w; i++){
		for (int j = 0; j < h; j++){
			bmp[i] = 10;
		}
	}

    write_bmp("pixel.bmp", bmp, h * w * 3 , w);
}