#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "fractal.h"

typedef unsigned long long PIXEL;
 
int main() {
	PIXEL h = 4000;
	PIXEL w = 4000;
	PIXEL datasize = h * w * 3;
	char *bmp = malloc(datasize);
	
	// Quit if memory is not available
	if (bmp == NULL){
		return 1;
	}
	
	struct world_coordinates world;

	world.set_left = -0.864;
    world.set_right = -0.860;
    world.set_down = 0.230;
    world.set_up = 0.234;

	set_mandelbot(h, w, bmp, world);
	write_bmp("test.bmp", bmp, datasize, w);
}