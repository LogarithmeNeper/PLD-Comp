int myFunction(int a) {
    return a + 2;
}

char myFunction(int a) {
    char b = a;
    return b;
}

int main() {
    int a = 2, b;
    b = myFunction(a);
    return b;
}