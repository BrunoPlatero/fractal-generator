#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "fractal.h"

#define COLUMNS 1080
#define ROWS 1080

#define MOTION 0.06;

void user_instructions() {
		printf("\n\n\n");
		for (int i = 0; i < 65; i++){
			printf("*");
		}
		printf("\n");
		printf("Welcome to the Mandelbrot Fractal.\nControls:\n\n");
		printf("	    W:move up			I:zoom in\n");
		printf("A:move left 		D:move right \n");
		printf("	    S:move down			O:zoom out\n\n");
		printf("Enter: take a screenshot of your favourite Mandelbrot spots\n\nPress Start\n");
		for (int i = 0; i < 65; i++){
			printf("*");
		}
		printf("\n");
		getchar();
	}

int main() {
	// Init
	size_t datasize = ROWS * COLUMNS * 4;
	char *frame = malloc(datasize);
	// Quit if memory is not available
	if (frame == NULL){
		return 1;
	}
	
	struct world_coordinates world;
	world.set_left = -2.5;
	world.set_right = 1.5;
	world.set_down = -2.0;
	world.set_up = 2.0;

	user_instructions();

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Create the window
	SDL_Window* window = SDL_CreateWindow("Fractal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, COLUMNS, ROWS, 0);
	if (window == NULL) {
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 2;
	}

	// Create the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}

	// Create a texture from the memory array
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, COLUMNS, ROWS);
	if (texture == NULL) {
		fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 4;
	}
 	
	SDL_Event event;
	int is_running = 1;
	while(is_running) {
		// Handle user input
		int need_new_frame = 0;
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) {
				is_running = 0;
			}
			// Update values of the world struct
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_a) {
					world.set_left -= (world.set_right - world.set_left) * MOTION;
					world.set_right -= (world.set_right - world.set_left) * MOTION;
				}
				else if (event.key.keysym.sym == SDLK_d) {
					world.set_left += (world.set_right - world.set_left) * MOTION;
					world.set_right += (world.set_right - world.set_left) * MOTION;					
				}
				else if (event.key.keysym.sym == SDLK_w) {
					world.set_down -= (world.set_up - world.set_down) * MOTION;
					world.set_up -= (world.set_up - world.set_down) * MOTION;				
				}
				else if (event.key.keysym.sym == SDLK_s) {
					world.set_down += (world.set_up - world.set_down) * MOTION;
					world.set_up += (world.set_up - world.set_down) * MOTION;						
				}
				else if (event.key.keysym.sym == SDLK_i) {
					// Calculate the center of the object
					double center_x = (world.set_left + world.set_right) / 2;
					double center_y = (world.set_down + world.set_up) / 2;

					// Translate the object so that its center is at the origin
					world.set_left -= center_x;
					world.set_right -= center_x;
					world.set_down -= center_y;
					world.set_up -= center_y;

					// Scale the object
					world.set_left *= 1 - MOTION;
					world.set_right *= 1 - MOTION;
					world.set_down *= 1 - MOTION;
					world.set_up *= 1 - MOTION;

					// Translate the object back to its original position
					world.set_left += center_x;
					world.set_right += center_x;
					world.set_down += center_y;
					world.set_up += center_y;
				}
				else if (event.key.keysym.sym == SDLK_o) {
					// Calculate the center of the object
					double center_x = (world.set_left + world.set_right) / 2;
					double center_y = (world.set_down + world.set_up) / 2;

					// Translate the object so that its center is at the origin
					world.set_left -= center_x;
					world.set_right -= center_x;
					world.set_down -= center_y;
					world.set_up -= center_y;

					// Scale the object
					world.set_left *= 1 + MOTION;
					world.set_right *= 1 + MOTION;
					world.set_down *= 1 + MOTION;
					world.set_up *= 1 + MOTION;

					// Translate the object back to its original position
					world.set_left += center_x;
					world.set_right += center_x;
					world.set_down += center_y;
					world.set_up += center_y;
				}
				// Take a screenshot
				else if (event.key.keysym.sym == SDLK_RETURN) {
					write_bmp("screenshot", frame, COLUMNS, ROWS);
				}
			}
			need_new_frame = 1;
		}	
		// Generate fractal memory
		if (need_new_frame) {
			set_mandelbot(COLUMNS, ROWS, frame, world);
			// Update texture
			SDL_UpdateTexture(texture, NULL, frame, COLUMNS * sizeof(unsigned char) * 4);
		}
		// Copy the texture to the renderer and present it
		SDL_RenderCopy(renderer, texture, NULL, NULL);
  		SDL_RenderPresent(renderer);
	}
	// Clean up
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	free(frame);
}