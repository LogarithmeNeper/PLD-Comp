int threeParams(int a, int b, int c) {
    return a+b*c;
}

int main() {
    int a,b,c;
    a=5;
    b=3;
    c=9;
    int d=threeParams(a,b,c);
    return d;
}