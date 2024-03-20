//#include "api/deprecated-avr-comp/avr/dtostrf.c.impl"

#if 1
#include <stdio.h>
#include <string.h>
#include <math.h>

static size_t printNumber(unsigned long n, uint8_t base, char *inputbuff)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2)
  {
     base = 10;
  }

  do
  {
    char c = (char)(n % base);
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  strcpy(inputbuff,str);

  return strlen(str);
}


char *dtostrf (double val, signed char width, unsigned char prec, char *sout)
{
  char fmt[20];
  double number = val;
  unsigned char digits = prec;
  signed short n;
  signed short width_local = width;
  memset(fmt, 0, sizeof(fmt));

  n = 0;

  if (isnan(number))
  {
      strcpy(fmt, "nan");
      strcpy(sout, fmt);
      return sout;
  }
  if (isinf(number))
  {
      strcpy(fmt, "inf");
      strcpy(sout, fmt);
      return sout;
  }
  if (number > 4294967040.0)
  {
      strcpy(fmt, "ovf");
      strcpy(sout, fmt);
      return sout;
  }
  if (number <-4294967040.0)
  {
      strcpy(fmt, "ovf");
      strcpy(sout, fmt);
      return sout;
  }

  // Handle negative numbers
  if (number < 0.0)
  {
    //     n += print('-');
    fmt[n] = '-';
    n++;
    number = -number;
  }


  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
//  n += print(int_part);
  n+= printNumber(int_part, 10, &fmt[n]);


    // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    fmt[n] = '.';
    n++;
//    n += print(".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)remainder;
//    n += print(toPrint);
    n+= printNumber((unsigned long)toPrint, 10, &fmt[n]);
    remainder -= toPrint;
  }

  if(width_local < 0)
  {
     /* left */
      width_local = -width_local;
    if(n <= width_local)
    {
        n = width_local;
    }
    strncpy((char *)sout, (const char *)fmt, (size_t)n);
    *(sout+n) = '\0';
  }
  else
  {
    /* right */
    signed short offset = 0;
    memset((void *)sout, ' ', (size_t)width_local);
    if(n <= width_local)
    {
        offset = width_local - n;
        strncpy((char *)sout+offset, (const char *)fmt, (size_t)n);
        *(sout+n+offset) = '\0';
    }
    else
    {
        strncpy((char *)sout, (const char *)fmt, (size_t)n);
        *(sout+n) = '\0';
    }
  }
  return sout;
}
#endif
