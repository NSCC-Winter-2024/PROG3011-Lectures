
extern void _print_ch(const char *);

void print_ch(char ch) {
    //_print_ch((const char *)&ch);
}

#define RCC_CR      (volatile unsigned long *)0x40021000
#define RCC_CFGR    (volatile unsigned long *)0x40021008
#define RCC_PLLCFGR (volatile unsigned long *)0x4002100C
#define RCC_IOPENR  (volatile unsigned long *)0x40021034

#define FLASH_ACR   (volatile unsigned long *)0x40022000

#define GPIOA_MODER (volatile unsigned long *)0x50000000
#define GPIOA_ODR   (volatile unsigned long *)0x50000014
#define GPIOA_AFRH  (volatile unsigned long *)0x50000024

#define GPIOC_MODER (volatile unsigned long *)0x50000800
#define GPIOC_IDR   (volatile unsigned long *)0x50000810

#define SYST_CSR    (volatile unsigned long *)0xE000E010
#define SYST_RVR    (volatile unsigned long *)0xE000E014
#define SYST_CVR    (volatile unsigned long *)0xE000E018
#define SYST_CALIB  (volatile unsigned long *)0xE000E01C

int main() {

#ifdef NDEBUG
    // change SYSCLK from 16MHz to 64MHz

    // disable PLLON
    *RCC_CR &= ~0x01000000UL;
    // wait for PLLRDY to be cleared
    while (*RCC_CR & 0x02000000UL);
    // configure PLL
    *RCC_PLLCFGR = 0x20000802UL;
    // enable PLLON
    *RCC_CR |= 0x01000000UL;
    // wait for PLLRDY to be set
    while (!(*RCC_CR & 0x02000000UL));
    // enable PLLRON
    *RCC_PLLCFGR |= 0x10000000UL;

    // configure FLASH wait states (2 wait states)
    *FLASH_ACR |= 0x00000002UL;
    // wait for configuration to complete
    while ((*FLASH_ACR & 0x00000007UL) != 2UL);

    // switch SYSCLK to PLLRCLK
    unsigned long rcc_cfgr = *RCC_CFGR;
    rcc_cfgr |= 0x00000002UL;
    *RCC_CFGR = rcc_cfgr;

    // confirm SYSCLK is PLLRCLK
    while ((*RCC_CFGR & 0x00000038UL) != 0x10UL);
#endif

    unsigned long rcc_cfgr2 = *RCC_CFGR;
    // configure MCO clock
    rcc_cfgr2 |= 0x40000000UL;   // set the MCOPRE to 16 (16MHz -> 1MHz)
    rcc_cfgr2 |= 0x01000000UL;   // select SYSCLK to output
    *RCC_CFGR = rcc_cfgr2;

    // SysTick configuration
    *SYST_RVR = 64000UL;        // set count to 64,000
    *SYST_CVR = 0UL;            // clear the current value and count flag
    *SYST_CSR |= 0x00000005UL;  // enable timer and use processor clock

    // configuration
    *RCC_IOPENR |= 0x00000005UL; // enable GPIOA and GPIOC clock

    // set PA5 as a digital output (User LED)
    *GPIOA_MODER &= ~0x00000800UL;

    // set PA9 as an alternate function (MCO)
    *GPIOA_MODER &= ~0x00040000UL;
    // *GPIOA_AFRH |= ....  // choose alternate function, if required

    // set PC13 as a digital input (User Button)
    *GPIOC_MODER &= ~0x0C000000UL;

    int count = 0;
    while (1) {

        // check for button press
        if (*GPIOC_IDR & 0x2000UL) {
            // set PA5 LOW (LED off)
            //*GPIOA_ODR &= ~0x00000020UL;
        } else {
            // set PA5 HIGH (LED on)
            //*GPIOA_ODR |= 0x00000020UL;
        }

        print_ch('*');

        // check for SysTick timer to expire
        if (*SYST_CSR & 0x00010000UL) {
            count++;
        }
        if (count > 1000) {
            *GPIOA_ODR ^= 0x00000020UL;
            count = 0;
        }
    }
    return 0;
}
