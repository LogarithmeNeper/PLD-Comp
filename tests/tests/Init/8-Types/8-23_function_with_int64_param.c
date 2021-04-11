#include <stdint.h>

int function(int64_t a) {
    int b = a + 5;
    return b;
}

int main() {
    int a;
    int64_t b = 6456;
    a = function(b);
    return a;
}