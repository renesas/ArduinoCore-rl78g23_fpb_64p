#include "api/ArduinoAPI.h"
#include "wiring_private.h"
// #include "ArduinoClassics.h"


uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder)
// uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i)
	{
		digitalWrite(clockPin, HIGH);

		if (bitOrder == LSBFIRST)
		{
			value |= digitalRead(dataPin) << i;
		}
		else
		{
			value |= digitalRead(dataPin) << (7 - i);
		}
		digitalWrite(clockPin, LOW);
	}

	return value;
}

// void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t value){
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		if (bitOrder == LSBFIRST)
		{
			digitalWrite(dataPin, !!(value & (1 << i)));
		}
		else
		{
			digitalWrite(dataPin, !!(value & (1 << (7 - i))));
		}

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}

}

/* 1112 nhu add */
void shiftOutEx(uint8_t dataPin, uint8_t clockPin, BitOrder bitOrder, uint8_t len, uint32_t value)
{
	uint8_t i;

	if(len <= 32)
	{
		if (bitOrder == LSBFIRST)
		{
			for(i = 0; i < len; i++)
			{
				digitalWrite(dataPin, ((value >> i) & 0x00000001));
				digitalWrite(clockPin, HIGH);
				digitalWrite(clockPin, LOW);
			}
		}
		else
		{
			for(i = len ; i > 0 ; i--)
			{
				digitalWrite(dataPin, ((value >> (i-1)) & 0x00000001));
				digitalWrite(clockPin, HIGH);
				digitalWrite(clockPin, LOW);
			}
		}

	}

}


/* 1112 nhu add */
