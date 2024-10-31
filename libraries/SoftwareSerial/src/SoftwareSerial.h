#ifndef SoftwareSerial_h
#define SoftwareSerial_h

#include <inttypes.h>
#include "api/Stream.h"

/******************************************************************************
* Definitions
******************************************************************************/

#ifndef _SS_MAX_RX_BUFF
#define _SS_MAX_RX_BUFF 256 // RX buffer size
#endif

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class SoftwareSerial : public Stream
{
private:
// per object data
    uint8_t _receivePin;
    uint8_t _receiveBitMask;
    volatile uint8_t *_receivePortRegister;
    uint8_t _transmitBitMask;
    volatile uint8_t *_transmitPortRegister;
    uint8_t _transmitPin;
    uint8_t _interrupt_num;
    volatile uint8_t _pcint_maskreg_p;
    volatile uint8_t _pcint_maskreg_n;
    uint8_t _pcint_maskvalue_p;
    uint8_t _pcint_maskvalue_n;

// Expressed as 4-cycle delays (must never be 0!)
    uint16_t _rx_delay_centering;
    uint16_t _rx_delay_firstbit;
    uint16_t _rx_delay_intrabit;
    uint16_t _rx_delay_stopbit;
    uint16_t _tx_delay;

    uint16_t _buffer_overflow:1;
    uint16_t _inverse_logic:1;

// static data
    static uint8_t _receive_buffer[_SS_MAX_RX_BUFF]; 
    static volatile uint8_t _receive_buffer_tail;
    static volatile uint8_t _receive_buffer_head;
    static SoftwareSerial *active_object;

// private methods
    inline void recv() __attribute__((__always_inline__));
    uint8_t rx_pin_read();
    void tx_pin_write(uint8_t pin_state);

    inline void setRxIntMsk(bool enable) __attribute__((__always_inline__));

// Return num - sub, or 1 if the result would be < 1
    static uint16_t subtract_cap(uint16_t num, uint16_t sub);

// private static method for timing
    static inline void tunedDelay(uint16_t delay);
    void Set_SerialPort(uint8_t txd_pin,uint8_t rxd_pin);
public:
  // public methods
    SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
    ~SoftwareSerial();
    void begin(long speed);
    bool listen();
    void end();
    bool isListening() { return this == active_object; }
    bool stopListening();
    bool overflow() { bool ret = _buffer_overflow; if (ret) _buffer_overflow = false; return ret; }
    int peek();

    virtual size_t write(uint8_t byte);
    virtual int read();
    virtual int available();
    virtual void flush();
    operator bool() { return true; }

    using Print::write;

  // public only for easy access by interrupt handlers
  static inline void handle_interrupt() __attribute__((__always_inline__));
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round

#endif
