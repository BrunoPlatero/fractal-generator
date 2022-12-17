#include "fractal.h"

void set_mandelbot(int world_x, int world_y, char *rgb, struct world_coordinates world){    

    // Define pixel size to acording to defined parameters
    const double pixel_width = (world.set_right - world.set_left) / world_x;
    const double pixel_height = (world.set_up - world.set_down) / world_y;

    // Radius of circle around set
    const double radius = 2;
    const double radius_2d = radius * radius;

    // Number of iterations to perform on n
    const int iterations = 255;

    // Mandelbrot function variables f(z) = z^2 + c
    for (int row = 0; row < world_y; row++){
        double cy = world.set_down + row * pixel_height;
        for (int col = 0; col < world_x; col++){
            double zx = 0.0;
            double zy = 0.0;
            double cx = world.set_left + col * pixel_width;
            for (int iteration = 0; iteration <= iterations; iteration++){ 
                double z2x = zx * zx - zy * zy;
                double z2y = 2 * zx * zy;
                double fx = z2x + cx;
                double fy = z2y + cy;
                zx = fx;
                zy = fy;
                // Complex number tends to infinite
                if ((zx * zx + zy * zy) > radius_2d){
                    rgb[3*(row * world_x + col) + 0] = (iteration + 29) % iterations;
                    rgb[3*(row * world_x + col) + 1] = iteration;
                    rgb[3*(row * world_x + col) + 2] = (iteration + 47) % iterations;                    
                }
                // Complex number remains stable
                else if (iteration == iterations && (zx * zx + zy * zy) < radius_2d) {
                    rgb[3*(row * world_x + col) + 0] = 0x00;
                    rgb[3*(row * world_x + col) + 1] = 0x00;
                    rgb[3*(row * world_x + col) + 2] = 0x00;
                }             
            }
        }
    }
}

