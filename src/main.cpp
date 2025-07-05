#include <iostream>
#include "../include/plasma.h"
#include <random>
#include <GLFW/glfw3.h>

using namespace std;


void computeColor(float c, float& r, float& g, float& b) {
    c = std::fmod(c, 1.0f);
    if (c < 0) c += 1.0f;

    if (c < 0.5f) {
        r = c * 2;
    } else {
        r = (1.0f - c) * 2;
    }

    if (c >= 0.3f && c < 0.8f) {
        g = (c - 0.3f) * 2;
    } else if (c < 0.3f) {
        g = (0.3f - c) * 2;
    } else {
        g = (1.3f - c) * 2;
    }

    if (c >= 0.5f) {
        b = (c - 0.5f) * 2;
    } else {
        b = (0.5f - c) * 2;
    }

    r = std::max(0.0f, std::min(1.0f, r));
    g = std::max(0.0f, std::min(1.0f, g));
    b = std::max(0.0f, std::min(1.0f, b));
}

void draw_plasma(float (&plasma_map)[SIZE][SIZE]) {
    glBegin(GL_POINTS);
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            float r, g, b;
            computeColor(plasma_map[x][y], r, g, b);
            glColor3f(r, g, b);
            glVertex2i(x, y);
        }
    }
    glEnd();
}

float displace(float num) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(-0.5f, 0.5f);

    float max = num / (SIZE + SIZE) * 3.0f;
    return dist(mt) * max;
}

float random_c() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(mt);
}

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
    divide_func(x, y + half_height, width - half_width, height - half_height, plasma_map, middle, edge_2, c3, edge_3);
    divide_func(x + half_width, y + half_height, half_width, height - half_height, plasma_map, edge_4, middle, edge_3, c4);
}


int main() {
    GLFWwindow* window;
    int size = SIZE - 1;

    float plasma_map[SIZE][SIZE] = {0};

    printf("%f\n", plasma_map[0][0] = random_c());
    printf("%f\n", plasma_map[0][SIZE - 1] = random_c());
    printf("%f\n", plasma_map[SIZE - 1][0] = random_c());
    printf("%f\n", plasma_map[SIZE - 1][SIZE - 1] = random_c());


    divide_func(0, 0, size, size, plasma_map, plasma_map[0][0], plasma_map[0][SIZE - 1],
        plasma_map[SIZE - 1][0], plasma_map[SIZE - 1][SIZE - 1]);

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(SIZE, SIZE, "Плазма", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, SIZE, 0, SIZE, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_plasma(plasma_map);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
