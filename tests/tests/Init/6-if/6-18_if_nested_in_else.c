int main() {
    int a = 8;
    int b = 1;
    if(a < 10) {
        b = 7;
    } else {
        if(a > 7){
            b = 3;
        } else {
            b = 4;
        }
    }
    return b;
}