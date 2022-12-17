#ifndef FRACTAL_H
#define FRACTAL_H

struct world_coordinates {
    double set_left;
    double set_right;
    double set_down;
    double set_up;
};

void set_mandelbot(int world_x, int world_y, char *rgb, struct world_coordinates world);

#endif // FRACTAL_H