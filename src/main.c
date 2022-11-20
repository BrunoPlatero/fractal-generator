#include "bmp.h"

int main(void){
	char fr[] = {
		0, 0, 0,   
		0, 0, 0,
		0, 0, 0,  
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
	};
	write_bmp("pixel.bmp", fr, sizeof(fr) / sizeof(char), 6);   
}