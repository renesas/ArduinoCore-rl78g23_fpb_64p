extern "C" {
  #include "stdlib.h"
}

void randomSeed(unsigned long seed)
{
  if (seed != 0) {
#ifndef __RL78__
    srandom(seed);
#else
	srand((unsigned int)seed);
#endif
  }
}

long random(long howbig)
{
  unsigned long value = 0;
  if (howbig == 0) {
    return 0;
  }
#ifndef __RL78__
  return random() % howbig;
#else
  value = ((unsigned long)rand() << 16);
  value |= ((unsigned long)rand() << 1);
  value |= ((unsigned long)rand() & 0x01);
  return (signed long)value % howbig;
#endif
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}
/*
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned int makeWord(unsigned int w) { return w; }
unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }
*/
