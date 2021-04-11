int main() {
    int a = 7, b = 1;
    if (a > 2) {
        b = 2;
        if (a > 4) {
            b = 3;
            if (a < 6) {
                b = 4;
            }
        }
    }
    return b;
}