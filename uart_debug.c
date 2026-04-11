#include <stdint.h>

#define USART2_BASE 0x40004400
#define USART_SR  (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART_DR  (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART_BRR (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART_CR1 (*(volatile uint32_t *)(USART2_BASE + 0x0C))

#define USART_SR_TXE  (1 << 7)
#define USART_SR_RXNE (1 << 5)
#define USART_CR1_UE  (1 << 13)
#define USART_CR1_TE  (1 << 3)
#define USART_CR1_RE  (1 << 2)

void uart_init(uint32_t baudrate) {
    // Configure USART2 at given baudrate (assuming 16MHz clock)
    USART_BRR = 16000000 / baudrate;
    USART_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void uart_send_char(char c) {
    while (!(USART_SR & USART_SR_TXE));
    USART_DR = c;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}

char uart_receive_char(void) {
    while (!(USART_SR & USART_SR_RXNE));
    return (char)(USART_DR & 0xFF);
}

void uart_send_hex(uint32_t value) {
    const char hex[] = "0123456789ABCDEF";
    uart_send_string("0x");
    for (int i = 28; i >= 0; i -= 4) {
        uart_send_char(hex[(value >> i) & 0xF]);
    }
}
