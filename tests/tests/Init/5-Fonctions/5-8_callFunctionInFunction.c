int incr(int a) {
    return a+1;
}

int twoincr(int a) {
    return incr(a+1);
}

int main() {
    int a=0;
    int b=twoincr(a);
    return b;
}