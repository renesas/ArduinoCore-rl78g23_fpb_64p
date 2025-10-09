/*
  EEPROM.h - EEPROM library
  Original Copyright (c) 2006 David A. Mellis.  All right reserved.
  New version by Christopher Andrews 2015.

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

#ifndef EEPROM_h
#define EEPROM_h

#include <inttypes.h>

extern uint8_t eeprom_read_byte( uint16_t& index  );
extern void eeprom_write_byte( uint16_t& index, uint8_t value );
extern void eeprom_write_block( uint16_t& index, uint16_t i_u16_write_data_length, const uint8_t *ptr);

#define E2END 0x1FFF
#define WRITE_DATA_BLOCK_SIZE 256

/***
    EERef class.

    This object references an EEPROM cell.
    Its purpose is to mimic a typical byte of RAM, however its storage is the EEPROM.
    This class has an overhead of two bytes, similar to storing a pointer to an EEPROM cell.
***/

struct EERef{

    EERef( const int index )
        : index( index )                 {}

    //Access/read members.
    uint8_t operator*() const            { return eeprom_read_byte( (uint16_t&) index ); }
    operator uint8_t() const             { return **this; }

    //Assignment/write members.
    EERef &operator=( const EERef &ref ) { return *this = *ref; }
    EERef &operator=( uint8_t in )       { return eeprom_write_byte( (uint16_t&) index, in ), *this;  }
    EERef &operator +=( uint8_t in )     { return *this = **this + in; }
    EERef &operator -=( uint8_t in )     { return *this = **this - in; }
    EERef &operator *=( uint8_t in )     { return *this = **this * in; }
    EERef &operator /=( uint8_t in )     { return *this = **this / in; }
    EERef &operator ^=( uint8_t in )     { return *this = **this ^ in; }
    EERef &operator %=( uint8_t in )     { return *this = **this % in; }
    EERef &operator &=( uint8_t in )     { return *this = **this & in; }
    EERef &operator |=( uint8_t in )     { return *this = **this | in; }
    EERef &operator <<=( uint8_t in )    { return *this = **this << in; }
    EERef &operator >>=( uint8_t in )    { return *this = **this >> in; }
        EERef &update( uint8_t in )          { return  in != *this ? *this = in : *this; }

    /** Prefix increment/decrement **/
    EERef& operator++()                  { return *this += 1; }
    EERef& operator--()                  { return *this -= 1; }

    /** Postfix increment/decrement **/
    uint8_t operator++ (int){
        uint8_t ret = **this;
        return ++(*this), ret;
    }

    uint8_t operator-- (int){
        uint8_t ret = **this;
        return --(*this), ret;
    }

    int index; //Index of current EEPROM cell.
};

/***
    EEPtr class.

    This object is a bidirectional pointer to EEPROM cells represented by EERef objects.
    Just like a normal pointer type, this can be dereferenced and repositioned using
    increment/decrement operators.
***/

struct EEPtr{

    EEPtr( const int index )
        : index( index )                {}

    operator int() const                { return index; }
    EEPtr &operator=( int in )          { return index = in, *this; }

    //Iterator functionality.
    bool operator!=( const EEPtr &ptr ) { return index != ptr.index; }
    EERef operator*()                   { return index; }

    /** Prefix & Postfix increment/decrement **/
    EEPtr& operator++()                 { return ++index, *this; }
    EEPtr& operator--()                 { return --index, *this; }
    EEPtr operator++ (int)              { return index++; }
    EEPtr operator-- (int)              { return index--; }

    int index; //Index of current EEPROM cell.
};

/***
    EEPROMClass class.
    
    This object represents the entire EEPROM space.
    It wraps the functionality of EEPtr and EERef into a basic interface.
    This class is also 100% backwards compatible with earlier Arduino core releases.
***/

struct EEPROMClass{

    //Basic user access methods.
    EERef operator[]( const int idx )    { return idx; }
    uint8_t read( int idx )              { return EERef( idx ); }
    void write( int idx, uint8_t val )   { (EERef( idx )) = val; }
    void update( int idx, uint8_t val )  { EERef( idx ).update( val ); }
    
    //STL and C++11 iteration capability.
    EEPtr begin()                        { return 0x00; }
    EEPtr end()                          { return length(); } //Standards requires this to be the item after the last valid entry. The returned pointer is invalid.
    uint16_t length()                    { return E2END + 1; }
    
    //Functionality to 'get' and 'put' objects to and from EEPROM.
    template< typename T > T &get( int idx, T &t ){
        EEPtr e = idx;
        uint8_t *ptr = (uint8_t*) &t;
        for( int count = sizeof(T) ; count ; --count, ++e )  *ptr++ = *e;
        return t;
    }

    template< typename T > const T &put( int idx, const T &t ){
        uint16_t l_au16_write_block_count; //Number of writes in one block.(1ブロック内の書き込み回数)
        uint8_t l_au08_write_block_index; //Number of writes in one block.(1ブロック内の書き込み位置)
        uint16_t volatile l_au16_write_count; //Number of writes in all blocks.(全ブロック内の書き込み回数)

        EEPtr e = idx;
        const uint8_t *ptr = (const uint8_t*) &t;
        for(l_au16_write_count = sizeof(T); l_au16_write_count ;)
        {
              if(*e == *ptr)
              {
                  ptr++;
                  e ++;
                  l_au16_write_count --;
              }
              else
              {
                  l_au08_write_block_index = (uint8_t)((e) % WRITE_DATA_BLOCK_SIZE);
                  l_au16_write_block_count = (uint16_t)(WRITE_DATA_BLOCK_SIZE - l_au08_write_block_index);
                  if (l_au16_write_block_count > l_au16_write_count)
                  {
                      l_au16_write_block_count = l_au16_write_count;
                  }
                  eeprom_write_block((uint16_t &)(e),l_au16_write_block_count, ptr);
                  (e) = (e)+l_au16_write_block_count;
                  ptr = ptr+l_au16_write_block_count;
                  l_au16_write_count -= l_au16_write_block_count;
              }
        }
        return t;
    }
};

static EEPROMClass EEPROM;
#endif
