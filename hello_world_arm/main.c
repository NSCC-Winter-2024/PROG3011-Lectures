
extern void _print_ch(const char *);

void print_ch(char ch) {
    //_print_ch((const char *)&ch);
}

#define RCC_IOPENR  (unsigned long *)0x40021034

#define GPIOA_MODER (unsigned long *)0x50000000
#define GPIOA_ODR   (unsigned long *)0x50000014

#define GPIOC_MODER (unsigned long *)0x50000800
#define GPIOC_IDR   (unsigned long *)0x50000810

int main() {

    // configuration
    *RCC_IOPENR |= 0x00000005UL; // enable GPIOA and GPIOC clock

    // set PA5 as a digital output (User LED)
    *GPIOA_MODER &= ~0x00000800UL;

    // set PC13 as a digital input (User Button)
    *GPIOC_MODER &= ~0x0C000000UL;

    while (1) {

        // check for button press
        if (*GPIOC_IDR & 0x2000UL) {
            // set PA5 LOW (LED off)
            *GPIOA_ODR &= ~0x00000020UL;
        } else {
            // set PA5 HIGH (LED on)
            *GPIOA_ODR |= 0x00000020UL;
        }

        print_ch('*');
    }
    return 0;
}
