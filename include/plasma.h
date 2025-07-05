#pragma once

const int SIZE = 1025;

float displace(float num);

float diamond_step(int x, int y, int half_width, int half_height, float (&plasma_map)[SIZE][SIZE]);

void square_step(int x, int y, int size, int half, float (&plasma_map)[SIZE][SIZE]);

