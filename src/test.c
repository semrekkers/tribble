#define TEST(t) _Generic(t, \
    int: "int" \
    default: "default")

#include <stdio.h>

int main() {
    printf(TEST(int));
    printf(TEST(1));
    return 0;
}
