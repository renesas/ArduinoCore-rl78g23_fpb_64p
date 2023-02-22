/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

// #include "api/HardwareSerial.h"
#include "HardwareSerial.h"
#include "SafeRingBuffer.h"

#ifdef SERIAL_BUFFER_SIZE
#undef SERIAL_BUFFER_SIZE
#endif

#define SERIAL_BUFFER_SIZE  256

class HardwareUart : public arduino::HardwareSerial
{
  public:
	HardwareUart(
	  volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
	  volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
	  volatile uint8_t *ucsrc, volatile uint8_t *udr,
	  uint8_t rxen, uint8_t txen, uint8_t rxcie, uint8_t udrie, uint8_t u2x);
	HardwareUart(uint8_t rxen);
    /*API*/
    void begin(unsigned long baud) override ;
    void begin(unsigned long baud, uint16_t config) override ;
    void begin(unsigned long baud, int rx_buf, int tx_buf);
    void begin(unsigned long baud, uint16_t config, int rx_buf, int tx_buf);
    void end() override ;
    virtual int available(void) override;
    virtual int peek(void) override;
    virtual int read(void) override ;
    virtual void flush(void) override;
    virtual size_t write(uint8_t c) override;
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write; /* pull in write(str) and write(buf, size) from Print */
    int availableForWrite(void) override;
    int availableForRead(void);
    void store_char(unsigned char c);
    void setReceiveCallback(void (*userFunc)(void));
    void setTransmitCallback(void (*userFunc)(void));
    void load_char(void);
    void store_char(void);
    operator bool() override ;

  private:
  private:
    volatile int _rx_buffer_head;
    volatile int _rx_buffer_tail;
    volatile int _tx_buffer_head;
    volatile int _tx_buffer_tail;
    volatile int _rx_buf_size;
    volatile int _tx_buf_size;
    unsigned char *_rx_buffer;
    unsigned char *_tx_buffer;

    uint8_t receive_buffer;
    uint8_t _urt_channel;
    bool transmitting;

    size_t UART_Send(uint8_t c);
    /* size_t UART_Send(const uint8_t *buffer, size_t size); */

    void Set_SerialPort(uint8_t txd_pin,uint8_t rxd_pin);

    /* Add 2021.02.09 */
    void Set_Baudrate(unsigned long baurate);
    void Set_Config(uint16_t config);
};

extern HardwareUart Serial;
extern HardwareUart Serial1;
extern HardwareUart Serial2;
