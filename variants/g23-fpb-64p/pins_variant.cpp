#include "pins_variant.h"
#include "wiring_private.h"
#include "wiring_private_tone.h"
#include "r_smc_entry.h"

/*
 * Pins descriptions
 */

const uint8_t SS   = PIN_SPI_SS;
const uint8_t MOSI = PIN_SPI_MOSI;
const uint8_t MISO = PIN_SPI_MISO;
const uint8_t SCK  = PIN_SPI_SCK;

const uint8_t SDA  = PIN_WIRE_SDA;
const uint8_t SCL  = PIN_WIRE_SCL;

const uint8_t A0 = PIN_A0;
const uint8_t A1 = PIN_A1;
const uint8_t A2 = PIN_A2;
const uint8_t A3 = PIN_A3;
const uint8_t A4 = PIN_A4;
const uint8_t A5 = PIN_A5;

/* tone pin set */
volatile unsigned short *g_tone_period_reg[TONE_CH_NUM] = {&TDR02,&TDR03,&TDR04,&TDR05,&TDR06,&TDR07};
volatile unsigned short *g_timer_tone_mode_reg[TONE_CH_NUM] = {&TMR02,&TMR03,&TMR04,&TMR05,&TMR06,&TMR07};
volatile unsigned short *g_timer_tone_clock_select_reg = &TPS0;
const uint8_t  tone_channel_table[TONE_CH_NUM]  = {TONE_PIN_11,TONE_PIN_6,TONE_PIN_3,TONE_PIN_10,TONE_PIN_9,TONE_PIN_5};
tone_func tone_ch[TONE_CH_NUM] =
{
    {
        .open  = R_Config_TAU0_2_Square_Wave_Create,
        .start = R_Config_TAU0_2_Square_Wave_Start,
        .stop = R_Config_TAU0_2_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_3_Square_Wave_Create,
        .start = R_Config_TAU0_3_Square_Wave_Start,
        .stop = R_Config_TAU0_3_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_4_Square_Wave_Create,
        .start = R_Config_TAU0_4_Square_Wave_Start,
        .stop = R_Config_TAU0_4_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_5_Square_Wave_Create,
        .start = R_Config_TAU0_5_Square_Wave_Start,
        .stop = R_Config_TAU0_5_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_6_Square_Wave_Create,
        .start = R_Config_TAU0_6_Square_Wave_Start,
        .stop = R_Config_TAU0_6_Square_Wave_Stop
    },
    {
        .open  = R_Config_TAU0_7_Square_Wave_Create,
        .start = R_Config_TAU0_7_Square_Wave_Start,
        .stop = R_Config_TAU0_7_Square_Wave_Stop
    }
};
