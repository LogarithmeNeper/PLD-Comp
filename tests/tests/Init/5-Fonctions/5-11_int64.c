#include <stdint.h>

int64_t func(int64_t a) {
    return a+1;
}

int main () {
    int64_t a=3;
    int64_t b=func(a);
    return b;
}