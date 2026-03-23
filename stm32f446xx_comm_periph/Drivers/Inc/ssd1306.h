#ifndef SSD1306_H
#define SSD1306_H

#include "stm32f446xx_i2c.h"
#include <string.h>

/*---------------------------------------------------------------------------
 * Configuración
 *--------------------------------------------------------------------------*/
#define SSD1306_I2C_ADDR     0x3C
#define SSD1306_WIDTH        128
#define SSD1306_HEIGHT       64
#define SSD1306_BUFFER_SIZE  (SSD1306_WIDTH * SSD1306_HEIGHT / 8)  // 1024 bytes

/*---------------------------------------------------------------------------
 * Colores
 *--------------------------------------------------------------------------*/
typedef enum {
    SSD1306_BLACK = 0,
    SSD1306_WHITE = 1,
} SSD1306_Color_t;

/*---------------------------------------------------------------------------
 * Handle
 *--------------------------------------------------------------------------*/
typedef struct {
    I2C_Handle_t *pI2C;
    uint8_t       buffer[SSD1306_BUFFER_SIZE];
    uint8_t       cursor_x;
    uint8_t       cursor_y;
} SSD1306_Handle_t;

/*---------------------------------------------------------------------------
 * API pública
 *--------------------------------------------------------------------------*/

/* Inicialización */
void SSD1306_Init(SSD1306_Handle_t *dev, I2C_Handle_t *pI2C);

/* Buffer → pantalla */
void SSD1306_UpdateScreen(SSD1306_Handle_t *dev);

/* Limpiar buffer (negro) */
void SSD1306_Clear(SSD1306_Handle_t *dev);

/* Dibujar píxel */
void SSD1306_DrawPixel(SSD1306_Handle_t *dev, uint8_t x, uint8_t y, SSD1306_Color_t color);

/* Texto */
void SSD1306_SetCursor(SSD1306_Handle_t *dev, uint8_t x, uint8_t y);
void SSD1306_WriteChar(SSD1306_Handle_t *dev, char c, SSD1306_Color_t color);
void SSD1306_WriteString(SSD1306_Handle_t *dev, const char *str, SSD1306_Color_t color);

#endif /* SSD1306_H */
