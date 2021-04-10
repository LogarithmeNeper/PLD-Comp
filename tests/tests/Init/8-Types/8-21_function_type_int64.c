#include <stdint.h>

int64_t function(int a) {
    int64_t b = a + 98;
    return b;
}

int main() {
    int a = 5;
    int64_t b;
    b = function(a);
    return b;
}