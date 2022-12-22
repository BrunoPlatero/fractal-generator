#include "fractal.h"

void set_mandelbot(int world_x, int world_y, char *rgb, struct world_coordinates world){    

    // Define pixel size to acording to defined parameters
    const double pixel_width = (world.set_right - world.set_left) / world_x;
    const double pixel_height = (world.set_up - world.set_down) / world_y;

    // Radius of circle around set
    const double radius = 2;
    const double escape_area = radius * radius;

    // Number of iterations to perform on n
    const int iterations = 1000;

    // Parallelise the outer for loop
    #pragma omp parallel for
    for (int row = 0; row < world_y; row++){
        double cy = world.set_down + row * pixel_height;
        for (int col = 0; col < world_x; col++){
            double zx = 0.0;
            double zy = 0.0;
            double cx = world.set_left + col * pixel_width;
            int iteration = 0.0;
            while (iteration < iterations && (zx * zx + zy * zy) < escape_area){ 
                // Mandelbrot recursive formula f(z) = z^2 + c
                double z2x = zx * zx - zy * zy;
                double z2y = 2 * zx * zy;
                double fx = z2x + cx;
                double fy = z2y + cy;
                zx = fx;
                zy = fy;
                iteration ++;
            }
            // Complex number tends to infinite
            char *pixel = rgb + 4 * (row * world_x + col);
            if (iteration == iterations) {
                pixel[0] = 0x00;
                pixel[1] = 0x00;
                pixel[2] = 0x00;
                pixel[3] = 0x00;
            }
            // Complex number remains stable
            else {
                pixel[0] = 0x00; // Alpha
                pixel[1] = (int)(iteration * 5.5) % 256; // Blue
                pixel[2] = (int)(iteration * 0.25) % 256; // Green 
                pixel[3] = (int)(iteration * 1.25) % 256; // Red                
            }
        }
    }
}

