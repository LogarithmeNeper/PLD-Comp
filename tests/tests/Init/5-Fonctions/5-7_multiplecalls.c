int myFunction(int a) {
    return a+1;
}

int main() {
    int a=4;
    int b=myFunction(myFunction(a));
    int c=myFunction(myFunction(myFunction(b)));
    return c;
}