#include <iostream>

using namespace std;


int random_c(int min = 0, int max = 255)
{
    return min + (rand() % static_cast<int>(max - min + 1));
}


int main() {
    const int img_size = 257;
    int roughness;
    cout << "Шероховатость/roughness: ";
    cin >> roughness;

    int plasma_map[img_size][img_size];

    printf("%d\n", plasma_map[0][0] = random_c());
    printf("%d\n", plasma_map[0][img_size - 1] = random_c());
    printf("%d\n", plasma_map[img_size - 1][0] = random_c());
    printf("%d\n", plasma_map[img_size - 1][img_size - 1] = random_c());

}
