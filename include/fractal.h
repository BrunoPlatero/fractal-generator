#ifndef FRACTAL_H
#define FRACTAL_H

struct world_coordinates {
    long double set_left;
    long double set_right;
    long double set_down;
    long double set_up;
};

void set_mandelbot(int world_x, int world_y, char *rgb, struct world_coordinates world);

#endif // FRACTAL_H