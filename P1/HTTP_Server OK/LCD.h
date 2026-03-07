/**
  ******************************************************************************
  * @file    lcd.h
  * @author  
  * @brief   Cabecera del driver para el display LCD gráfico (SPI).
  * Define la interfaz pública y la estructura de mensajes para la cola.
  ******************************************************************************
  */

#ifndef lcd_h
#define lcd_h

#include "stm32f4xx_hal.h"
#include "Driver_SPI.h"
#include "cmsis_os2.h" 

/* --- Definiciones de Hardware y Timing --- */
// Comandos básicos del controlador (p.ej. ST7565 o similar)
#define LCD_CMD_DISPLAY_OFF 0xAE
#define LCD_CMD_DISPLAY_ON  0xAF

/* --- Estructura del Mensaje (IPC) --- */
/**
  * @brief Objeto de mensaje para la cola del LCD.
  * Permite enviar texto y comandos gráficos desde cualquier hilo.
  */
typedef struct {
    char Lin1[50];     /*!< Texto para la Línea 1 (Superior) */
    char Lin2[50];     /*!< Texto para la Línea 2 (Inferior) */
    uint8_t barra;     /*!< Selector de cursor (1:Horas, 2:Min, 3:Seg) para modo Reloj */
    uint8_t amplitud;  /*!< Valor (0-100) para dibujar una barra gráfica pixel a pixel */
} MSGQUEUE_OBJ_LCD_t;

/* --- Variables Externas --- */
extern osMessageQueueId_t mid_messageQueueLCD; /*!< Cola de entrada del LCD */

/* --- Funciones de Bajo Nivel (Hardware) --- */
void LCD_reset(void);
void LCD_wr_data(unsigned char data);
void LCD_wr_cmd(unsigned char cmd);
void delay (uint32_t n_microsegundos);
void LCD_init(void);
void LCD_update(void);

/* --- Funciones de Alto Nivel (Gráficos) --- */
void LCD_symbolToLocalBuffer_L1(uint8_t symbol);
void LCD_symbolToLocalBuffer_L2(uint8_t symbol);
void symbolToLocalBuffer(uint8_t line, uint8_t symbol);
void LCD_ClearBuffer(void);
void LCD_StrigToBuffer(char str[]);
void LCD_StrigToBuffer2(char str[]);
void LCD_SelectBar(uint8_t posicionHorizontal);
void LCD_DrawAudioBar(uint8_t amplitude);

/* --- Funciones RTOS --- */
int Init_ThLCD (void);

#endif /* lcd_h */
