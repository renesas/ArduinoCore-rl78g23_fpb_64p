/*
 Servo.cpp - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
 Copyright (c) 2009 Michael Margolis.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

// #if defined(ARDUINO_ARCH_AVR)

// #include <avr/interrupt.h>
#include <Arduino.h>

#include "Servo.h"

extern "C" {
#if defined(G22_FPB)
#include "Config_TAU0_4.h"
#include "Config_TAU0_5.h"
#elif defined(G23_FPB)
#include "Config_TAU0_5_Servo.h"
#include "Config_TAU0_6_Servo.h"
#include "Config_TAU0_7_Servo.h"
#endif  // G22/G23
}

#define usToTicks(_us)    ( _us)      // converts microseconds to tick (assumes prescale of 8)  // 12 Aug 2009
#define ticksToUs(_ticks) ( _ticks ) // converts from ticks back to microseconds
#define TRIM_DURATION       2                               // compensation ticks to trim adjust for digitalWrite delays // 12 August 2009

static servo_t servos[MAX_SERVOS];                          // static array of servo structures
static volatile int8_t Channel[_Nbr_16timers ];             // counter for the servo being pulsed for each timer (or -1 if refresh interval)
uint8_t ServoCount = 0;                                     // the total number of attached servos
#if defined(G22_FPB)
/* Declaration by cores/rl78g22/smc_gen/Config_TAU0_x_Servo/Config_TAU0_x_Servo_user.c */
extern void (*g_fServoInterruptFunc4)(void);
extern void (*g_fServoInterruptFunc5)(void);
#elif defined(G23_FPB)
/* Declaration by cores/rl78g23/smc_gen/Config_TAU0_x_Servo/Config_TAU0_x_Servo_user.c */
extern void (*g_fServoInterruptFunc5)(void);
extern void (*g_fServoInterruptFunc6)(void);
extern void (*g_fServoInterruptFunc7)(void);
#endif  // G22/G23
static volatile uint16_t g_servo_time_sum[_Nbr_16timers ];  // count up the ellapse time for refresh

// convenience macros
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER)) // returns the timer controlling this servo
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)       // returns the index of the servo on this timer
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)     // macro to access servo index by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])            // macro to access servo class by timer and channel
#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // minimum value in us for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // maximum value in us for this servo

/************ static functions common to all instances ***********************/
#if defined(G22_FPB)

static void myReset_TDR(uint16_t TDRval, timer16_Sequence_t timer)
{
    if(timer == 0)
    {
        TDR04 = TDRval;
        TT0 |= _0010_TAU_CH4_STOP_TRG_ON;
        TS0 |= _0010_TAU_CH4_START_TRG_ON;
    }
    else
    {
        TDR05 = TDRval;
        TT0 |= _0020_TAU_CH5_STOP_TRG_ON;
        TS0 |= _0020_TAU_CH5_START_TRG_ON;
    }
}
#elif defined(G23_FPB)
static void Reset_TDR(uint16_t TDRval, timer16_Sequence_t timer)
{
    if(timer == 0)
    {
        TDR07 = TDRval;
        TT0 |= _0080_TAU_CH7_STOP_TRG_ON;
        TS0 |= _0080_TAU_CH7_START_TRG_ON;
    }
    else if(timer == 1)
    {
        TDR06 = TDRval;
        TT0 |= _0040_TAU_CH6_STOP_TRG_ON;
        TS0 |= _0040_TAU_CH6_START_TRG_ON;
    }
    else
    {
        TDR05 = TDRval;
        TT0 |= _0020_TAU_CH5_STOP_TRG_ON;
        TS0 |= _0020_TAU_CH5_START_TRG_ON;
    }
}
#endif  // G22/G23

static inline void servo_handle_interrupts(timer16_Sequence_t timer)
{
    uint16_t temp_TDR;
    if( Channel[timer] < 0 )
    {
        g_servo_time_sum[timer] = 0; // channel set to -1 indicated that refresh interval completed so reset the timer
    }
    else
    {
        if( SERVO_INDEX(timer,Channel[timer]) < ServoCount && SERVO(timer,Channel[timer]).Pin.isActive == true )
        {
            digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,LOW); // pulse this channel low if activated
        }
    }

    Channel[timer]++;    // increment to the next channel
    if( (SERVO_INDEX(timer,Channel[timer]) < ServoCount) && (Channel[timer] < SERVOS_PER_TIMER))
    {
        temp_TDR = SERVO(timer,Channel[timer]).ticks;
        g_servo_time_sum[timer] += temp_TDR;
        Reset_TDR(temp_TDR, timer);
        if(SERVO(timer,Channel[timer]).Pin.isActive == true)     // check if activated
        {
            digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,HIGH); // its an active channel so pulse it high
        }
    }
    else
    {
        if(usToTicks(REFRESH_INTERVAL) > g_servo_time_sum[timer])
        {
            temp_TDR = (unsigned int)usToTicks(REFRESH_INTERVAL) - g_servo_time_sum[timer];
        }
        else
        {
            temp_TDR = 100;
        }
        Reset_TDR(temp_TDR, timer);
        Channel[timer] = -1; // this will get incremented at the end of the refresh period to start again at the first channel
    }
}

static boolean isTimerActive(timer16_Sequence_t timer)
{
  // returns true if any servo is active on this timer
  for(uint8_t channel=0; channel < SERVOS_PER_TIMER; channel++) {
    if(SERVO(timer,channel).Pin.isActive == true)
      return true;
  }
  return false;
}

#if defined(G22_FPB)
static void g_fServoInterruptFunc4_sub(void)
{
    servo_handle_interrupts(_timerTAU04);
}

static void g_fServoInterruptFunc5_sub(void)
{
    servo_handle_interrupts(_timerTAU05);
}
#endif
#if defined(G23_FPB)
static void g_fServoInterruptFunc5_sub(void)
{
    servo_handle_interrupts(_timerTAU05);
}

static void g_fServoInterruptFunc6_sub(void)
{
    servo_handle_interrupts(_timerTAU06);
}

static void g_fServoInterruptFunc7_sub(void)
{
    servo_handle_interrupts(_timerTAU07);
}
#endif

/****************** end of static functions ******************************/

Servo::Servo()
{
    if( ServoCount < MAX_SERVOS)
    {
        this->servoIndex = ServoCount++;                    // assign a servo index to this instance
        servos[this->servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values  - 12 Aug 2009
    }
    else
    {
        this->servoIndex = INVALID_SERVO ;  // too many servos
    }
}

uint8_t Servo::attach(int pin)
{
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}


uint8_t Servo::attach(int pin, int min_a, int max_a)
{
    if(this->servoIndex < MAX_SERVOS )
    {
        pinMode( (pin_size_t)pin, OUTPUT) ;                                   // set servo pin to output
        servos[this->servoIndex].Pin.nbr = (uint8_t)pin;
        // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
        this->min  = (MIN_PULSE_WIDTH - min_a)/4; //resolution of min/max is 4 us
        this->max  = (MAX_PULSE_WIDTH - max_a)/4;
        // initialize the timer if it has not already been initialized
        timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
#if defined(G22_FPB)
        if(timer == 0)
        {
            if(isTimerActive(timer) == false)
            {
                g_fServoInterruptFunc4 = g_fServoInterruptFunc4_sub;
                Channel[timer] = -1;
                R_Config_TAU0_4_Create();
                R_Config_TAU0_4_Start();
            }
        }
        else
        {
            if(isTimerActive(timer) == false)
            {
                g_fServoInterruptFunc5 = g_fServoInterruptFunc5_sub;
                Channel[timer] = -1;
                R_Config_TAU0_5_Create();
                R_Config_TAU0_5_Start();
            }
        }
#elif defined(G23_FPB)
        if(timer == 0)
        {
            if(isTimerActive(timer) == false)
            {
                g_fServoInterruptFunc7 = g_fServoInterruptFunc7_sub;
                Channel[timer] = -1;
                R_Config_TAU0_7_Servo_Create();
                R_Config_TAU0_7_Servo_Start();
            }
        }
        else if(timer == 1)
        {
            if(isTimerActive(timer) == false)
            {
                g_fServoInterruptFunc6 = g_fServoInterruptFunc6_sub;
                Channel[timer] = -1;
                R_Config_TAU0_6_Servo_Create();
                R_Config_TAU0_6_Servo_Start();
            }
        }
        else
        {
            if(isTimerActive(timer) == false)
            {
                g_fServoInterruptFunc5 = g_fServoInterruptFunc5_sub;
                Channel[timer] = -1;
                R_Config_TAU0_5_Servo_Create();
                R_Config_TAU0_5_Servo_Start();
            }
        }
#endif  // G22/G23

        servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
    }
    return this->servoIndex ;
}

void Servo::detach()
{
    servos[this->servoIndex].Pin.isActive = false;
}

void Servo::write(int value)
{
  if(value < MIN_PULSE_WIDTH)
  {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
    if(value < 0) value = 0;
    if(value > 180) value = 180;
    value = (int)map(value, 0, 180, SERVO_MIN(),  SERVO_MAX());
  }
  this->writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
  // calculate and store the values for the given channel
    byte channel = this->servoIndex;
    if( (channel < MAX_SERVOS) )   // ensure channel is valid
    {
        if( value < SERVO_MIN() )          // ensure pulse width is valid
        {
            value = SERVO_MIN();
        }
        else if( value > SERVO_MAX() )
        {
            value = SERVO_MAX();
        }
        value = value - TRIM_DURATION;
        value = usToTicks(value);  // convert to ticks after compensating for interrupt overhead - 12 Aug 2009
        servos[channel].ticks = (unsigned int)value;
    }
}

int Servo::read() // return the value as degrees
{
  return  (int)map( this->readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);
}

int Servo::readMicroseconds()
{
  int pulsewidth;
  if( this->servoIndex != INVALID_SERVO )
    pulsewidth = (int)ticksToUs(servos[this->servoIndex].ticks)  + TRIM_DURATION ;   // 12 aug 2009
  else
    pulsewidth  = 0;

  return pulsewidth;
}

bool Servo::attached()
{
  return servos[this->servoIndex].Pin.isActive ;
}

