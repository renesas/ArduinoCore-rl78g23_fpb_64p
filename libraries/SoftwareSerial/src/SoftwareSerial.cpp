/*
SoftwareSerial.cpp (formerly NewSoftSerial.cpp) - 
Multi-instance software serial library for Arduino/Wiring
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

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

The latest version of this library can always be found at
http://arduiniana.org.
*/
/* Aug 25th 2017: Modified by Yuuki Okamiya for RL78 */

// When set, _DEBUG co-opts pins 11 and 13 for debugging with an
// oscilloscope or logic analyzer.  Beware: it also slightly modifies
// the bit times, so don't rely on it too much at high baud rates
#define _DEBUG 0
#define _DEBUG_PIN1 11
#define _DEBUG_PIN2 13
// 
// Includes
// 

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "wiring_variant.h"
extern "C" {
    #include "pintable.h"
    extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];
}
extern bool g_u8AnalogReadAvailableTable[NUM_ANALOG_INPUTS];

volatile int tempAXvalue=0;
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
        DIGITAL_PIN_MASK_0,
        DIGITAL_PIN_MASK_1,
        DIGITAL_PIN_MASK_2,
        DIGITAL_PIN_MASK_3,
        DIGITAL_PIN_MASK_4,
        DIGITAL_PIN_MASK_5,
        DIGITAL_PIN_MASK_6,
        DIGITAL_PIN_MASK_7,
        DIGITAL_PIN_MASK_8,
        DIGITAL_PIN_MASK_9,
        DIGITAL_PIN_MASK_10,
        DIGITAL_PIN_MASK_11,
        DIGITAL_PIN_MASK_12,
        DIGITAL_PIN_MASK_13,
        DIGITAL_PIN_MASK_14,
        DIGITAL_PIN_MASK_15,
        DIGITAL_PIN_MASK_16,
        DIGITAL_PIN_MASK_17,
        DIGITAL_PIN_MASK_18,
        DIGITAL_PIN_MASK_19,
        DIGITAL_PIN_MASK_20,
        DIGITAL_PIN_MASK_21,
        DIGITAL_PIN_MASK_22,
        DIGITAL_PIN_MASK_23,
        DIGITAL_PIN_MASK_24,
        DIGITAL_PIN_MASK_25,
        DIGITAL_PIN_MASK_26,
        DIGITAL_PIN_MASK_27,
        DIGITAL_PIN_MASK_28,
        DIGITAL_PIN_MASK_29,
        DIGITAL_PIN_MASK_30
};
//
// Statics
//
SoftwareSerial *SoftwareSerial::active_object = 0;
uint8_t SoftwareSerial::_receive_buffer[_SS_MAX_RX_BUFF]; 
volatile uint8_t SoftwareSerial::_receive_buffer_tail = 0;
volatile uint8_t SoftwareSerial::_receive_buffer_head = 0;

//
// Debugging
//
// This function generates a brief pulse
// for debugging or measuring on an oscilloscope.

inline void DebugPulse(uint8_t, uint8_t) {}

//
// Private methods
//

/* static */ 
inline void SoftwareSerial::tunedDelay(uint16_t delay_cnt){
    tempAXvalue = delay_cnt;
    asm("movw bc, ax");
    asm("movw de, #0");
    asm("movw ax, bc");
    asm("cmpw ax, #0");
    asm("bz $1f");
    asm("2:");
    asm("incw de");
    asm("movw ax, de");
    asm("cmpw ax, bc");
    asm("bnz $2b");
    asm("1:");
    return;
}


// This function sets the current object as the "listening"
// one and returns true if it replaces another 
bool SoftwareSerial::listen()
{
    if (!_rx_delay_stopbit)
        return false;

    if (active_object != this)
    {
        if (active_object)
            active_object->stopListening();

        _buffer_overflow = false;
        _receive_buffer_head = _receive_buffer_tail = 0;
        active_object = this;
        setRxIntMsk(true);
        return true;
    }

  return false;
}

// Stop listening. Returns true if we were actually listening.
bool SoftwareSerial::stopListening()
{
    if (active_object == this)
    {
        setRxIntMsk(false);
        active_object = NULL;
        return true;
      }
    return false;
}

uint8_t tempLEDBlink = 0;

void DebugPulse2(void){
    if(tempLEDBlink == 0)
    {
        digitalWrite(BUILTIN_LED2, HIGH);
        tempLEDBlink = 1;
    }
    else
    {
        digitalWrite(BUILTIN_LED2, LOW);
        tempLEDBlink = 0;
    }
}

//
// The receive routine called by the interrupt handler
//
void SoftwareSerial::recv()
{
    uint8_t d = 0;
  // If RX line is high, then we don't see any start bit
  // so interrupt is probably not for us
    if (_inverse_logic ? rx_pin_read() : !rx_pin_read())
    {
    // Disable further interrupts during reception, this prevents
    // triggering another interrupt directly after we return, which can
    // cause problems at higher baudrates.
        setRxIntMsk(false);

    // Wait approximately 1/2 of a bit width to "center" the sample
        if(_rx_delay_centering>0) tunedDelay(_rx_delay_centering);

        if(_rx_delay_firstbit>0) tunedDelay(_rx_delay_firstbit);
    // Read each of the 8 bits
        for (uint8_t i=8; i > 0; --i)
        {
            if(i<8) tunedDelay(_rx_delay_intrabit);
            d >>= 1;
//            DebugPulse2();
            if (rx_pin_read())
                d |= 0x80;
        }

        if (_inverse_logic)
            d = ~d;

    // if buffer full, set the overflow flag and return
        uint8_t next = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
        if (next != _receive_buffer_head)
        {
      // save new data in buffer: tail points to where byte goes
            _receive_buffer[_receive_buffer_tail] = d; // save new byte
            _receive_buffer_tail = next;
        }
        else 
        {
            _buffer_overflow = true;
        }

    // skip the stop bit
        tunedDelay(_rx_delay_stopbit);

    // Re-enable interrupts when we're sure to be inside the stop bit
        setRxIntMsk(true);
    }
}


uint8_t SoftwareSerial::rx_pin_read()
{
    return *_receivePortRegister & _receiveBitMask;
}

//
// Interrupt handling
//

/* static */
inline void SoftwareSerial::handle_interrupt()
{
    if (active_object)
    {
        active_object->recv();
    }
}

static void softwareserial_interrupt(){
      SoftwareSerial::handle_interrupt();
}

//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */) : 
    _rx_delay_centering(0),
    _rx_delay_firstbit(0),
    _rx_delay_intrabit(0),
    _rx_delay_stopbit(0),
    _tx_delay(0),
    _buffer_overflow(false),
    _inverse_logic(inverse_logic)
{
    _transmitPin = transmitPin;
    _receivePin = receivePin;
    _transmitBitMask = digitalPinToBitMask(transmitPin);
    _receiveBitMask = digitalPinToBitMask(receivePin);
    PinTableType* p;
    PinTableType pin_tbl;
    p =(PinTableType*)&pin_tbl;
    const PinTableType ** pp;
    pp = &pinTablelist[transmitPin];
    p = (PinTableType *)*pp;
    _transmitPortRegister = p->portRegisterAddr;
    pp = &pinTablelist[receivePin];
    p = (PinTableType *)*pp;
    _receiveBitMask = p->mask;
    _receivePortRegister = p->portRegisterAddr;
    _interrupt_num = digitalPinToInterrupt(_receivePin);
    _pcint_maskreg_p = 0;
    _pcint_maskreg_n = 0;
    _pcint_maskvalue_p = 0;
    _pcint_maskvalue_n = 0;
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial()
{
    end();
}

uint16_t SoftwareSerial::subtract_cap(uint16_t num, uint16_t sub) {
    if (num > sub)
        return num - sub;
    else
        return 1;
}

//
// Public methods
//

void SoftwareSerial::begin(long speed)
{
  _rx_delay_centering = _rx_delay_intrabit = _rx_delay_stopbit = _tx_delay = _rx_delay_firstbit = 0;

    uint16_t bit_delay = (F_CPU / speed) / 5 - 5;

  // 12 (gcc 4.8.2) or 13 (gcc 4.3.2) cycles from start bit to first bit,
  // 15 (gcc 4.8.2) or 16 (gcc 4.3.2) cycles between bits,
  // 12 (gcc 4.8.2) or 14 (gcc 4.3.2) cycles from last bit to stop bit
  // These are all close enough to just use 15 cycles, since the inter-bit
  // timings are the most critical (deviations stack 8 times)
  _tx_delay = subtract_cap(bit_delay, 15 / 4);

    attachInterrupt(_interrupt_num, softwareserial_interrupt, CHANGE);

    if (115200L == speed)
    {
        _rx_delay_centering = 0;
        _rx_delay_firstbit = 30;
        _rx_delay_intrabit = 30;
        _rx_delay_stopbit = 30;
        _tx_delay = 30;
    }
    else if (57600L == speed)
    {
        _rx_delay_centering = 25;
        _rx_delay_firstbit = 69;
        _rx_delay_intrabit = 69;
        _rx_delay_stopbit = 69;
        _tx_delay = 69;
    }
    else if (38400L == speed)
    {
        _rx_delay_centering = 45;
        _rx_delay_firstbit = 108;
        _rx_delay_intrabit = 108;
        _rx_delay_stopbit = 108;
        _tx_delay = 108;
    }
    else if (19200L == speed)
    {
        _rx_delay_centering = 110;
        _rx_delay_firstbit = 227;
        _rx_delay_intrabit = 227;
        _rx_delay_stopbit = 227;
        _tx_delay = 227;
    }
    else if (9600L == speed)
    {
        _rx_delay_centering = 227;
        _rx_delay_firstbit = 463;
        _rx_delay_intrabit = 463;
        _rx_delay_stopbit = 463;
        _tx_delay = 463;
    }
    else if (4800L == speed)
    {
        _rx_delay_centering = 467;
        _rx_delay_firstbit = 935;
        _rx_delay_intrabit = 935;
        _rx_delay_stopbit = 935;
        _tx_delay = 935;
    }

    Set_SerialPort(_transmitPin,_receivePin);

    listen();
}
// param : true means enable the interruption
void SoftwareSerial::setRxIntMsk(bool enable)
{
    if (enable)
    {
        _pcint_maskreg_p |= _pcint_maskvalue_p;
        _pcint_maskreg_n |= _pcint_maskvalue_p;
    }
    else{
        _pcint_maskreg_p &= ~_pcint_maskvalue_p;
        _pcint_maskreg_n &= ~_pcint_maskvalue_p;
    }
}

void SoftwareSerial::tx_pin_write(uint8_t pin_state)
{
    if (pin_state == LOW)
        *_transmitPortRegister &= ~_transmitBitMask;
    else
        *_transmitPortRegister |= _transmitBitMask;
}

void SoftwareSerial::end()
{
  stopListening();
}


// Read data from buffer
int SoftwareSerial::read()
{
    if (!isListening())
        return -1;

  // Empty buffer?
    if (_receive_buffer_head == _receive_buffer_tail)
        return -1;

  // Read from "head"
    uint8_t d = _receive_buffer[_receive_buffer_head]; // grab next byte
    _receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
    return d;
}

int SoftwareSerial::available()
{
    if (!isListening())
        return 0;

    return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head) % _SS_MAX_RX_BUFF;
}

// modified from 6->4
const int XMIT_START_ADJUSTMENT = 4;

size_t SoftwareSerial::write(uint8_t b)
{
    if (_tx_delay == 0)
        return 0;

    noInterrupts();

  // Write the start bit
    tempAXvalue = _inverse_logic ? HIGH : LOW;
    tx_pin_write(tempAXvalue);
    tempAXvalue = _tx_delay + XMIT_START_ADJUSTMENT;
    tunedDelay(tempAXvalue);

  // Write each of the 8 bits
    if (_inverse_logic)
    {
        for (uint8_t mask = 0x01; mask; mask <<= 1)
        {
            if (b & mask) // choose bit
            tx_pin_write(LOW); // send 1
            else
            tx_pin_write(HIGH); // send 0

            tunedDelay(_tx_delay);
        }
        tx_pin_write(LOW); // restore pin to natural state
    }
    else
    {
        for (uint8_t mask = 0x01; mask; mask <<= 1)
        {
            if (b & mask) // choose bit
                tx_pin_write(HIGH); // send 1
            else
                tx_pin_write(LOW); // send 0

            tunedDelay(_tx_delay);
        }

        tx_pin_write(HIGH); // restore pin to natural state
    }
    tunedDelay(_tx_delay);
    interrupts();

    return 1;
}

void SoftwareSerial::flush()
{
  // There is no tx buffering, simply return
}

int SoftwareSerial::peek()
{
    if (!isListening())
        return -1;

  // Empty buffer?
    if (_receive_buffer_head == _receive_buffer_tail)
        return -1;

  // Read from "head"
    return _receive_buffer[_receive_buffer_head];
}

void SoftwareSerial::Set_SerialPort(uint8_t txd_pin,uint8_t rxd_pin)
{
    const PinTableType ** pp;
    PinTableType * p;
    uint8_t pin_index;

    /* Set RxD pin */
    //getPinTable(rxd_pin,p);
    pp = &pinTablelist[rxd_pin];
    p = (PinTableType *)*pp;
    /* Set PM Register for Input */
    *p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);

    /* Set PMCA Register */
    if (0!=p->pmca){
        *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);

        pin_index = rxd_pin - ANALOG_PIN_START_NUMBER;
        if(pin_index >=0 && pin_index < NUM_ANALOG_INPUTS)
        {
            g_u8AnalogReadAvailableTable[pin_index] = false;
        }
    }

    /* Set PMCT Register */
    if (0!=p->pmct){
        *p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
    }

    /* Set PMCE Register for Output */
    if (0!=p->pmce){
        *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }

    /* Set CCDE Register for Digital InOut */
    if (0!=p->ccde){
        CCDE &= (uint8_t)~(p->ccde);
    }

    /* Set TxD pin */
    pp = &pinTablelist[txd_pin];
    p = (PinTableType *)*pp;
    /* Set PMCE Register t */
    if (0!=p->pmce){
        *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }

    if(true == _inverse_logic)
    {
        /* Set P Register for Set "L" Output Port*/
        *p->portRegisterAddr &= (uint8_t)~(0x1 << p->bit);
    }
    else
    {
        /* Set P Register for Set "H" Output Port*/
        *p->portRegisterAddr |= (uint8_t)(0x1 << p->bit);
    }

    /* Set PM Register for Output */
    *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);

    /* Set PMCA Register */
    if (0!=p->pmca){
        *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);

        pin_index = txd_pin - ANALOG_PIN_START_NUMBER;
        if(pin_index >=0 && pin_index < NUM_ANALOG_INPUTS)
        {
            g_u8AnalogReadAvailableTable[pin_index] = false;
        }
    }

    /* Set PMCT Register */
    if (0!=p->pmct){
        *p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
    }

    /* Set PMCE Register t */
    if (0!=p->pmce){
        *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }

    /* Set CCDE Register for Digital InOut */
    if (0!=p->ccde){
        CCDE &= (uint8_t)~(p->ccde);
    }
}
