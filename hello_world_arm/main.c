
extern void _print_ch(const char *);

void print_ch(char ch) {
    _print_ch((const char *)&ch);
}

int main() {
    while (1) {
        print_ch('*');
    }
    return 0;
}
