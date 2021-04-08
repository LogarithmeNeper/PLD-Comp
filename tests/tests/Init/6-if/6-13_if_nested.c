int main() {
    int a = 4,b;
    if(a > 3) {
        b = 1;
        if(a > 5) {
            b = 2;
        }
        a = 3;
    }
    return b;
}