int functionWithIntParam(int a) {
    return a + 7;
}

int main() {
    char a = 'a';
    int b = functionWithIntParam(a);
    return b;
}