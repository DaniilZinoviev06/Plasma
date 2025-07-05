#include "../include/plasma.h"
#include <algorithm>

void square_step(int x, int y, int size, int half, float (&plasma_map)[SIZE][SIZE]) {

    float edge_1 = (plasma_map[x][y] + plasma_map[x + size][y]) / 2.0f;
    float edge_2 = (plasma_map[x][y] + plasma_map[x][y + size]) / 2.0f;
    float edge_3 = (plasma_map[x + size][y] + plasma_map[x + size][y + size]) / 2.0f;
    float edge_4 = (plasma_map[x][y + size] + plasma_map[x + size][y + size]) / 2.0f;
}