void delay_ms(unsigned int ms) {
    unsigned int i;
    while (ms--) {
        for (i = 0; i < 1000; i++) {
            // Adjust this loop depending on your clock frequency
            // This loop generates roughly 1ms delay at 20MHz clock
            _delay_us(1);
        }
    }
}
