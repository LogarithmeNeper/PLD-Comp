int a=5;

int main() {
    if(a==0) {
        return 0;
    }
    else {
        a--;
        main();
    }
}