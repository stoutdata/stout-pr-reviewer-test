#include <stdint.h>

#define SPI1_BASE 0x40003000
#define SPI_TXDATA  (*(volatile uint32_t *)(SPI1_BASE + 0x00))
#define SPI_RXDATA  (*(volatile uint32_t *)(SPI1_BASE + 0x04))
#define SPI_STATUS  (*(volatile uint32_t *)(SPI1_BASE + 0x08))

#define SPI_STATUS_BUSY (1 << 0)
#define SPI_STATUS_TXRDY (1 << 1)

#define FLASH_CMD_READ_ID    0x9F
#define FLASH_CMD_READ_STATUS 0x05
#define FLASH_CMD_WRITE_ENABLE 0x06

uint8_t spi_transfer(uint8_t data) {
    while (!(SPI_STATUS & SPI_STATUS_TXRDY));
    SPI_TXDATA = data;
    while (SPI_STATUS & SPI_STATUS_BUSY);
    return (uint8_t)(SPI_RXDATA & 0xFF);
}

uint32_t flash_read_id(void) {
    uint32_t id = 0;
    spi_transfer(FLASH_CMD_READ_ID);
    id |= spi_transfer(0xFF) << 16;
    id |= spi_transfer(0xFF) << 8;
    id |= spi_transfer(0xFF);
    return id;
}
