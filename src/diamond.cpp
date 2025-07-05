#include "../include/plasma.h"
#include <algorithm>

float diamond_step(int x, int y, int half_width, int half_height, float (&plasma_map)[SIZE][SIZE]) {
    float average = (plasma_map[x][y] + plasma_map[x + half_width][y] +
        plasma_map[x][y + half_height] + plasma_map[x + half_width][y + half_height]) / 4.0f;

    float val = average + displace(half_width + half_height);
    plasma_map[x + half_width][y + half_height] = std::max(0.0f, std::min(1.0f, val));

    return val;
}
