#ifndef Arduino_h
#define Arduino_h

#include "api/ArduinoAPI.h"
#include <stdbool.h>
#include "utilities.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "r_cg_macrodriver.h"
#ifdef __cplusplus
}
#endif
#include "pintable.h"
#include "pins_variant.h"

#define RLDUINO78_VERSION 0x0203
#define INTERRUPT
#define _BV(bit) (1 << (bit))
#define _HALT()		asm("halt;");
#define _STOP()		asm("stop;");

#define clockCyclesPerMicrosecond()			(configCPU_CLOCK_HZ / 1000000)				//!< CPUの動作周波数を1000000で割ったもの
#define clockCyclesToMicroseconds(cycle)	((cycle) / clockCyclesPerMicrosecond())		//!< サイクルあたりの時間[us]
#define microsecondsToClockCycles(us)		((us) * clockCyclesPerMicrosecond())		//!< 時間当たりのサイクル数


#define HOOK_TIMER_CHANNEL  7

#define MICROSECONDS_PER_TIMER05_OVERFLOW 0xffff //1us * 2 ^ 16
#define MILLISECONDS_PER_TIMER05_OVERFLOW (MICROSECONDS_PER_TIMER05_OVERFLOW / 1000)
#define INTERVAL_MICRO_TDR	(MICROSECONDS_PER_TIMER05_OVERFLOW - 1)

/* Serial define */
#define USE_SMART_CONFIGRATOR (1)

#ifdef __cplusplus

using namespace arduino;

#include "api/WCharacter.h"
#include "api/HardwareSerial.h"
#include "HardwareUart.h"


extern "C"{
#endif // __cplusplus

// Include Atmel headers
#undef LITTLE_ENDIAN

// #include "WVariant.h"

#define INPUT_TTL	0x5
#define INPUT_TTL_PULLUP	0x6

/* PWM setting. */
#define PWM_MASTER_CLOCK    (32000000)
#if PWM_MASTER_CLOCK == 32000000
#define PWM_MASTER_MODE     (0x0801)    // CK0を選択
#define PWM_SLAVE_MODE      (0x0409)
#elif PWM_MASTER_CLOCK == 1000000
#define PWM_MASTER_MODE     (0x8801)    // CK1を選択
#define PWM_SLAVE_MODE      (0x8409)
#endif

#define PWM_DEFAULT_FREQ    (490)       // 490Hz
#define PWM_TDR00           (PWM_MASTER_CLOCK / PWM_DEFAULT_FREQ - 1)

#define interrupts()  EI()
#define noInterrupts()  DI()

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

#define bit(b) (1UL << (b))

void init(void);
void initVariant(void);

int atexit(void (*func)()) __attribute__((weak));

void DisableDigitalInput(uint8_t pin);
void EnableDigitalInput(uint8_t pin);
void analogWriteFrequency(uint32_t Hz);
void analogWritePinFrequency(uint8_t pin, uint32_t Hz);
void set_starttime(void);
long set_endtime();
void shiftOutEx(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder, uint8_t len, uint32_t value);
void setup();
void loop();

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

#define analogInPinToBit(P) (P)

#define NOT_AN_INTERRUPT -1


#ifdef __cplusplus
} // extern "C"
#endif

// Include board variant
#include "pins_variant.h"

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs

#define abs(x) ((x)>0?(x):-(x))


#include "api/itoa.h"
#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ 					(32000000)	//!< CPUの動作周波数（RTOS未使用時に定義）
#endif
/* Analog reference mode. */
#define DEFAULT			0x00
#define EXTERNAL		0x01
#define INTERNAL		0x02
/* Power Management Mode. */
#define PM_NORMAL_MODE	0
#define PM_HALT_MODE	1
#define PM_STOP_MODE	2
#define PM_SNOOZE_MODE	3


#ifdef __RL78__
#define ISP_LEVEL_3 (3)
#define ISP_LEVEL_2 (2)
#define ISP_LEVEL_1 (1)
#define ISP_LEVEL_0 (0)

#define GET_PSW_ISP()  (__builtin_rl78_getpswisp ())
#define isNoInterrupts() (!__builtin_rl78_pswie ())

#if defined(__RL78_S3__)
/* S3 core (with Multiply/divide/multiply & accumulate instructions)*/

#if (F_CPU == 32000000)
/* For RL78/G23, RL78/G22, etc. */
#define MICROS_EXEC_TIME  (3) /* micros() execution time(unit:us) */
#define DELAYMICROSECONDS_ADJUST1  (1) /* Processing time(unit:us) if delayMicroseconds() function returns immediately */
#define DELAYMICROSECONDS_ADJUST2  (MICROS_EXEC_TIME + DELAYMICROSECONDS_ADJUST1 + 1)
#define DELAYMICROSECONDS_ADJUST3  (DELAYMICROSECONDS_ADJUST2 + MICROS_EXEC_TIME)
#define DELAYMICROSECONDS_ADJUST4  (5) /* Adjustment when waiting for time in delay_wait().　(visual check) */
#else /* (F_CPU == 16000000) */
#endif /* (F_CPU == 16000000) */

#elif defined(__RL78_S2__)

#if defined(__MDA_ENABLED__)
/* S2 core & with MDA(Multiplier and Divider/Multiply-Accumulator) */

#if (F_CPU == 32000000)
#elif (F_CPU == 16000000)
#else /* (F_CPU == XXX) */
#endif /* (F_CPU == XXX) */

#elif defined(__MDA_DISABLED__)
/* S2 core & with no MDA */

#if (F_CPU == 32000000)
#elif (F_CPU == 16000000)
/* For RL78/G15, etc */
#define MICROS_EXEC_TIME  (5) /* unit : us */
#define DELAYMICROSECONDS_ADJUST1  (2) /* Processing time(unit:us) if delayMicroseconds() function returns immediately */
#define DELAYMICROSECONDS_ADJUST2  (MICROS_EXEC_TIME + DELAYMICROSECONDS_ADJUST1 + 1)
#define DELAYMICROSECONDS_ADJUST3  (DELAYMICROSECONDS_ADJUST2 + MICROS_EXEC_TIME)
#define DELAYMICROSECONDS_ADJUST4  (2) /* Adjustment when waiting for time in delay_wait().　(visual check) */
#else /* (F_CPU == XXX) */
#endif /* (F_CPU == XXX) */

#endif /* defined(__MDA_DISABLED__),defined(__MDA_DISABLED__) */
#endif /* defined(__RL78_S3__), defined(__RL78_S2__) */

#endif /* ifdef __RL78__ */


#endif // Arduino_h
