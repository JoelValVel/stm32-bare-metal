#include "ssd1306.h"

/*===========================================================================
 * Font 5x7 — ASCII 32 (espacio) a 126 (~)
 * Cada carácter = 5 columnas de 8 bits (bit 0 = fila superior)
 *=========================================================================*/
static const uint8_t font5x7[][5] = {
    {0x00,0x00,0x00,0x00,0x00}, /* 32 espacio */
    {0x00,0x00,0x5F,0x00,0x00}, /* 33 !       */
    {0x00,0x07,0x00,0x07,0x00}, /* 34 "       */
    {0x14,0x7F,0x14,0x7F,0x14}, /* 35 #       */
    {0x24,0x2A,0x7F,0x2A,0x12}, /* 36 $       */
    {0x23,0x13,0x08,0x64,0x62}, /* 37 %       */
    {0x36,0x49,0x55,0x22,0x50}, /* 38 &       */
    {0x00,0x05,0x03,0x00,0x00}, /* 39 '       */
    {0x00,0x1C,0x22,0x41,0x00}, /* 40 (       */
    {0x00,0x41,0x22,0x1C,0x00}, /* 41 )       */
    {0x14,0x08,0x3E,0x08,0x14}, /* 42 *       */
    {0x08,0x08,0x3E,0x08,0x08}, /* 43 +       */
    {0x00,0x50,0x30,0x00,0x00}, /* 44 ,       */
    {0x08,0x08,0x08,0x08,0x08}, /* 45 -       */
    {0x00,0x60,0x60,0x00,0x00}, /* 46 .       */
    {0x20,0x10,0x08,0x04,0x02}, /* 47 /       */
    {0x3E,0x51,0x49,0x45,0x3E}, /* 48 0       */
    {0x00,0x42,0x7F,0x40,0x00}, /* 49 1       */
    {0x42,0x61,0x51,0x49,0x46}, /* 50 2       */
    {0x21,0x41,0x45,0x4B,0x31}, /* 51 3       */
    {0x18,0x14,0x12,0x7F,0x10}, /* 52 4       */
    {0x27,0x45,0x45,0x45,0x39}, /* 53 5       */
    {0x3C,0x4A,0x49,0x49,0x30}, /* 54 6       */
    {0x01,0x71,0x09,0x05,0x03}, /* 55 7       */
    {0x36,0x49,0x49,0x49,0x36}, /* 56 8       */
    {0x06,0x49,0x49,0x29,0x1E}, /* 57 9       */
    {0x00,0x36,0x36,0x00,0x00}, /* 58 :       */
    {0x00,0x56,0x36,0x00,0x00}, /* 59 ;       */
    {0x08,0x14,0x22,0x41,0x00}, /* 60 <       */
    {0x14,0x14,0x14,0x14,0x14}, /* 61 =       */
    {0x00,0x41,0x22,0x14,0x08}, /* 62 >       */
    {0x02,0x01,0x51,0x09,0x06}, /* 63 ?       */
    {0x32,0x49,0x79,0x41,0x3E}, /* 64 @       */
    {0x7E,0x11,0x11,0x11,0x7E}, /* 65 A       */
    {0x7F,0x49,0x49,0x49,0x36}, /* 66 B       */
    {0x3E,0x41,0x41,0x41,0x22}, /* 67 C       */
    {0x7F,0x41,0x41,0x22,0x1C}, /* 68 D       */
    {0x7F,0x49,0x49,0x49,0x41}, /* 69 E       */
    {0x7F,0x09,0x09,0x09,0x01}, /* 70 F       */
    {0x3E,0x41,0x49,0x49,0x7A}, /* 71 G       */
    {0x7F,0x08,0x08,0x08,0x7F}, /* 72 H       */
    {0x00,0x41,0x7F,0x41,0x00}, /* 73 I       */
    {0x20,0x40,0x41,0x3F,0x01}, /* 74 J       */
    {0x7F,0x08,0x14,0x22,0x41}, /* 75 K       */
    {0x7F,0x40,0x40,0x40,0x40}, /* 76 L       */
    {0x7F,0x02,0x04,0x02,0x7F}, /* 77 M       */
    {0x7F,0x04,0x08,0x10,0x7F}, /* 78 N       */
    {0x3E,0x41,0x41,0x41,0x3E}, /* 79 O       */
    {0x7F,0x09,0x09,0x09,0x06}, /* 80 P       */
    {0x3E,0x41,0x51,0x21,0x5E}, /* 81 Q       */
    {0x7F,0x09,0x19,0x29,0x46}, /* 82 R       */
    {0x46,0x49,0x49,0x49,0x31}, /* 83 S       */
    {0x01,0x01,0x7F,0x01,0x01}, /* 84 T       */
    {0x3F,0x40,0x40,0x40,0x3F}, /* 85 U       */
    {0x1F,0x20,0x40,0x20,0x1F}, /* 86 V       */
    {0x3F,0x40,0x38,0x40,0x3F}, /* 87 W       */
    {0x63,0x14,0x08,0x14,0x63}, /* 88 X       */
    {0x07,0x08,0x70,0x08,0x07}, /* 89 Y       */
    {0x61,0x51,0x49,0x45,0x43}, /* 90 Z       */
    {0x00,0x7F,0x41,0x41,0x00}, /* 91 [       */
    {0x02,0x04,0x08,0x10,0x20}, /* 92 \       */
    {0x00,0x41,0x41,0x7F,0x00}, /* 93 ]       */
    {0x04,0x02,0x01,0x02,0x04}, /* 94 ^       */
    {0x40,0x40,0x40,0x40,0x40}, /* 95 _       */
    {0x00,0x01,0x02,0x04,0x00}, /* 96 `       */
    {0x20,0x54,0x54,0x54,0x78}, /* 97 a       */
    {0x7F,0x48,0x44,0x44,0x38}, /* 98 b       */
    {0x38,0x44,0x44,0x44,0x20}, /* 99 c       */
    {0x38,0x44,0x44,0x48,0x7F}, /* 100 d      */
    {0x38,0x54,0x54,0x54,0x18}, /* 101 e      */
    {0x08,0x7E,0x09,0x01,0x02}, /* 102 f      */
    {0x0C,0x52,0x52,0x52,0x3E}, /* 103 g      */
    {0x7F,0x08,0x04,0x04,0x78}, /* 104 h      */
    {0x00,0x44,0x7D,0x40,0x00}, /* 105 i      */
    {0x20,0x40,0x44,0x3D,0x00}, /* 106 j      */
    {0x7F,0x10,0x28,0x44,0x00}, /* 107 k      */
    {0x00,0x41,0x7F,0x40,0x00}, /* 108 l      */
    {0x7C,0x04,0x18,0x04,0x78}, /* 109 m      */
    {0x7C,0x08,0x04,0x04,0x78}, /* 110 n      */
    {0x38,0x44,0x44,0x44,0x38}, /* 111 o      */
    {0x7C,0x14,0x14,0x14,0x08}, /* 112 p      */
    {0x08,0x14,0x14,0x18,0x7C}, /* 113 q      */
    {0x7C,0x08,0x04,0x04,0x08}, /* 114 r      */
    {0x48,0x54,0x54,0x54,0x20}, /* 115 s      */
    {0x04,0x3F,0x44,0x40,0x20}, /* 116 t      */
    {0x3C,0x40,0x40,0x20,0x7C}, /* 117 u      */
    {0x1C,0x20,0x40,0x20,0x1C}, /* 118 v      */
    {0x3C,0x40,0x30,0x40,0x3C}, /* 119 w      */
    {0x44,0x28,0x10,0x28,0x44}, /* 120 x      */
    {0x0C,0x50,0x50,0x50,0x3C}, /* 121 y      */
    {0x44,0x64,0x54,0x4C,0x44}, /* 122 z      */
    {0x00,0x08,0x36,0x41,0x00}, /* 123 {      */
    {0x00,0x00,0x7F,0x00,0x00}, /* 124 |      */
    {0x00,0x41,0x36,0x08,0x00}, /* 125 }      */
    {0x10,0x08,0x08,0x10,0x08}, /* 126 ~      */
};

#define FONT_WIDTH   5
#define FONT_HEIGHT  7
#define FONT_SPACING 1  /* píxeles entre caracteres */

/*===========================================================================
 * Funciones privadas
 *=========================================================================*/
static void SSD1306_WriteCmd(SSD1306_Handle_t *dev, uint8_t cmd)
{
    uint8_t buf[2] = {0x00, cmd};  /* 0x00 = byte de control → comando */
    I2C_SendData(dev->pI2C, buf, 2, SSD1306_I2C_ADDR, I2C_STOP_ENABLE);
}

/*===========================================================================
 * Inicialización
 *=========================================================================*/
void SSD1306_Init(SSD1306_Handle_t *dev, I2C_Handle_t *pI2C)
{
    dev->pI2C     = pI2C;
    dev->cursor_x = 0;
    dev->cursor_y = 0;
    memset(dev->buffer, 0, SSD1306_BUFFER_SIZE);

    /* Secuencia de inicialización estándar SSD1306 128x64 */
    SSD1306_WriteCmd(dev, 0xAE); /* display OFF                        */
    SSD1306_WriteCmd(dev, 0xD5); /* set display clock divide           */
    SSD1306_WriteCmd(dev, 0x80); /* ratio recomendado                  */
    SSD1306_WriteCmd(dev, 0xA8); /* set multiplex ratio                */
    SSD1306_WriteCmd(dev, 0x3F); /* 64 líneas (0x3F = 63)              */
    SSD1306_WriteCmd(dev, 0xD3); /* set display offset                 */
    SSD1306_WriteCmd(dev, 0x00); /* sin offset                         */
    SSD1306_WriteCmd(dev, 0x40); /* set start line = 0                 */
    SSD1306_WriteCmd(dev, 0x8D); /* charge pump                        */
    SSD1306_WriteCmd(dev, 0x14); /* habilitar charge pump              */
    SSD1306_WriteCmd(dev, 0x20); /* memory addressing mode             */
    SSD1306_WriteCmd(dev, 0x00); /* horizontal addressing              */
    SSD1306_WriteCmd(dev, 0xA1); /* segment remap (columna 127 = SEG0) */
    SSD1306_WriteCmd(dev, 0xC8); /* COM scan direction remapped        */
    SSD1306_WriteCmd(dev, 0xDA); /* set COM pins                       */
    SSD1306_WriteCmd(dev, 0x12); /* configuración alternada            */
    SSD1306_WriteCmd(dev, 0x81); /* set contrast                       */
    SSD1306_WriteCmd(dev, 0xCF); /* contraste alto                     */
    SSD1306_WriteCmd(dev, 0xD9); /* set pre-charge period              */
    SSD1306_WriteCmd(dev, 0xF1); /* fase 1=1, fase 2=15                */
    SSD1306_WriteCmd(dev, 0xDB); /* set VCOMH deselect level           */
    SSD1306_WriteCmd(dev, 0x40);
    SSD1306_WriteCmd(dev, 0xA4); /* output sigue RAM                   */
    SSD1306_WriteCmd(dev, 0xA6); /* display normal (no invertido)      */
    SSD1306_WriteCmd(dev, 0xAF); /* display ON                         */

    SSD1306_Clear(dev);
    SSD1306_UpdateScreen(dev);
}

/*===========================================================================
 * Volcar buffer a pantalla
 *=========================================================================*/
void SSD1306_UpdateScreen(SSD1306_Handle_t *dev)
{
    /* Establecer rango de columnas y páginas */
    SSD1306_WriteCmd(dev, 0x21); /* column address */
    SSD1306_WriteCmd(dev, 0x00); /* inicio = 0     */
    SSD1306_WriteCmd(dev, 0x7F); /* fin   = 127    */

    SSD1306_WriteCmd(dev, 0x22); /* page address */
    SSD1306_WriteCmd(dev, 0x00); /* inicio = 0   */
    SSD1306_WriteCmd(dev, 0x07); /* fin   = 7    */

    /* Enviar buffer — primer byte es 0x40 (control byte: datos) */
    uint8_t tx[SSD1306_BUFFER_SIZE + 1];
    tx[0] = 0x40;
    memcpy(&tx[1], dev->buffer, SSD1306_BUFFER_SIZE);
    I2C_SendData(dev->pI2C, tx, sizeof(tx), SSD1306_I2C_ADDR, I2C_STOP_ENABLE);
}

/*===========================================================================
 * Limpiar buffer
 *=========================================================================*/
void SSD1306_Clear(SSD1306_Handle_t *dev)
{
    memset(dev->buffer, 0, SSD1306_BUFFER_SIZE);
    dev->cursor_x = 0;
    dev->cursor_y = 0;
}

/*===========================================================================
 * Dibujar píxel
 *=========================================================================*/
void SSD1306_DrawPixel(SSD1306_Handle_t *dev, uint8_t x, uint8_t y, SSD1306_Color_t color)
{
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;

    if(color == SSD1306_WHITE)
        dev->buffer[x + (y / 8) * SSD1306_WIDTH] |=  (1U << (y % 8));
    else
        dev->buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1U << (y % 8));
}

/*===========================================================================
 * Cursor
 *=========================================================================*/
void SSD1306_SetCursor(SSD1306_Handle_t *dev, uint8_t x, uint8_t y)
{
    dev->cursor_x = x;
    dev->cursor_y = y;
}

/*===========================================================================
 * Escribir un carácter
 *=========================================================================*/
void SSD1306_WriteChar(SSD1306_Handle_t *dev, char c, SSD1306_Color_t color)
{
	/* Salto de línea */
	if(c == '\n') {
		dev->cursor_x  = 0;
		dev->cursor_y += FONT_HEIGHT + FONT_SPACING;
		return;
	}
	if(c < 32 || c > 126) return;


    /* Sin espacio para el carácter — nueva línea */
    if(dev->cursor_x + FONT_WIDTH >= SSD1306_WIDTH) {
        dev->cursor_x  = 0;
        dev->cursor_y += FONT_HEIGHT + FONT_SPACING;
    }

    /* Sin espacio vertical */
    if(dev->cursor_y + FONT_HEIGHT > SSD1306_HEIGHT) return;

    const uint8_t *glyph = font5x7[c - 32];

    for(uint8_t col = 0; col < FONT_WIDTH; col++) {
        uint8_t line = glyph[col];
        for(uint8_t row = 0; row < FONT_HEIGHT; row++) {
            if(line & (1U << row))
                SSD1306_DrawPixel(dev, dev->cursor_x + col, dev->cursor_y + row, color);
            else
                SSD1306_DrawPixel(dev, dev->cursor_x + col, dev->cursor_y + row,
                                  (color == SSD1306_WHITE) ? SSD1306_BLACK : SSD1306_WHITE);
        }
    }

    /* Columna de separación */
    for(uint8_t row = 0; row < FONT_HEIGHT; row++)
        SSD1306_DrawPixel(dev, dev->cursor_x + FONT_WIDTH, dev->cursor_y + row, SSD1306_BLACK);

    dev->cursor_x += FONT_WIDTH + FONT_SPACING;
}

/*===========================================================================
 * Escribir cadena
 *=========================================================================*/
void SSD1306_WriteString(SSD1306_Handle_t *dev, const char *str, SSD1306_Color_t color)
{
    while(*str)
        SSD1306_WriteChar(dev, *str++, color);
}
