#include "../include/plasma.h"

void divide_func(int x, int y, int width, int height, float (&plasma_map)[SIZE][SIZE],
    float c1, float c2, float c3, float c4) {

    if (width < 2 || height < 2)
        return;

    int half_width = width / 2;
    int half_height = height / 2;

    float middle = (c1 + c2 + c3 + c4) / 4.0f + displace(width + height);
    middle = std::max(0.0f, std::min(1.0f, middle));

    float edge_1 = (c1 + c2) / 2.0f;
    float edge_2 = (c2 + c3) / 2.0f;
    float edge_3 = (c3 + c4) / 2.0f;
    float edge_4 = (c4 + c1) / 2.0f;


    if (x + half_width < SIZE && y + half_height < SIZE) {
        plasma_map[x + half_width][y + half_height] = middle;
    }

    std::cout << "=====================" << std::endl;
    std::cout << "=" << plasma_map[x + half_width][y + half_height] << std::endl;
    std::cout << "=====================" << std::endl;

    divide_func(x, y, half_width, half_height, plasma_map, c1, edge_1, middle, edge_4);
    divide_func(x + half_width, y, width - half_width, half_height, plasma_map, edge_1, c2, edge_2, middle);
    divide_func(x + half_width, y + half_height, width - half_width, height - half_height, plasma_map, middle, edge_2, c3, edge_3);
    divide_func(x, y + half_height, half_width, height - half_height, plasma_map, edge_4, middle, edge_3, c4);
}
