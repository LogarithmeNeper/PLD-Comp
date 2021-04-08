int incr(int a) {
    return a+1;
}

int twoincr(int a) {
    int f = incr(a+1);
    return f;
}

int main() {
    int a=0;
    int b=twoincr(a);
    return b;
}