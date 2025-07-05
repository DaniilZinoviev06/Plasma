#include <random>
#include <GLFW/glfw3.h>

#include "../include/plasma.h"


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
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
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

int main() {
    GLFWwindow* window;
    int size = SIZE - 1;

    float plasma_map[SIZE][SIZE] = {0};

    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    plasma_map[0][0] = dist(mt);
    plasma_map[0][SIZE-1] = dist(mt);
    plasma_map[SIZE-1][0] = dist(mt);
    plasma_map[SIZE-1][SIZE-1] = dist(mt);

    divide_func(0, 0, size, size, plasma_map, plasma_map[0][0], plasma_map[0][SIZE - 1],
        plasma_map[SIZE - 1][SIZE - 1], plasma_map[SIZE - 1][0]);

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SIZE, SIZE, "Плазма/Plasma", NULL, NULL);
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
