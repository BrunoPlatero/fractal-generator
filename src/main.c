#include <stdlib.h>
#include "bmp.h"

int main() {
	int h = 1080;
	int w = 1920;

	char *bmp = malloc(h * w * 3);
	for (int index = 0; index < h * w * 3; index = index + 3){
		bmp[index] = 0x00;
		bmp[index + 1] = 0x00;
		bmp[index + 2] = 0xff;
	}
    write_bmp("pixel.bmp", bmp, h * w * 3 , w);
}


	