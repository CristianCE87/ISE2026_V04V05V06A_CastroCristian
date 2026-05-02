#ifndef RGB_H_
#define RGB_H_

#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "stm32f4xx_hal.h"
#include <stdint.h>

/* ------------------------------
   Definiciones generales
   ------------------------------ */
#define RGB_NUM_RINGS      4
#define RGB_LEDS_PER_RING  8

/* ------------------------------
   Tipos de comandos
   ------------------------------ */
typedef enum {
    RGB_CMD_SET_COLOR,
    RGB_CMD_OFF
} rgb_cmd_t;

/* ------------------------------
   Estructura de color
   ------------------------------ */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

/* ------------------------------
   Mensaje enviado por la cola
   ------------------------------ */
typedef struct {
    rgb_cmd_t cmd;
    uint8_t ring_id;       // 0..3
    rgb_color_t color;     // usado en SET_COLOR
} rgb_msg_t;

/* ------------------------------
   API pública
   ------------------------------ */
int Init_Th_rgb(void);          // Inicializa el hilo
osMessageQueueId_t rgb_get_queue(void);  // Devuelve la cola


/* Handle del timer y DMA */
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_tim4_ch1;


void Init_pin_tim(void);


/********************/
int Init_Th_test_rgb(void);
/********************/


#endif
