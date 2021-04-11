int myFunction(int a, int b) {
    return a + b;
}

int myFunction(int a) {
    return a + 2;
}

int main() {
    int a = 1, b = 1, c, d;
    c = myFunction(a, b);
    d = myFunction(a);
    return c + d;
}