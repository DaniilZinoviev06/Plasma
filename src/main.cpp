#include <iostream>
#include "../include/plasma.h"

using namespace std;

int random_c() {
    return rand() % 256;
}


int main() {
    int roughness;
    cout << "Шероховатость/roughness: ";
    cin >> roughness;

    int plasma_map[SIZE][SIZE] = {0};

    printf("%d\n", plasma_map[0][0] = random_c());
    printf("%d\n", plasma_map[0][SIZE - 1] = random_c());
    printf("%d\n", plasma_map[SIZE - 1][0] = random_c());
    printf("%d\n", plasma_map[SIZE - 1][SIZE - 1] = random_c());


    diamond_step(plasma_map);

    return 0;
}
