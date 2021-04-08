int fourParams(int a, int b, int c, int d) {
    return a+b*c+d;
}

int main() {
    int a,b,c,d;
    a=4;
    b=6;
    c=9;
    d=3;
    int e=fourParams(a,b,c,d);
    return e;
}