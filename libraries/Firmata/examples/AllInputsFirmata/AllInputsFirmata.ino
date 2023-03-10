/*
 * Firmata is a generic protocol for communicating with microcontrollers
 * from software on a host computer. It is intended to work with
 * any host computer software package.
 *
 * To download a host software package, please click on the following link
 * to open the list of Firmata client libraries in your default browser.
 *
 * https://github.com/firmata/arduino#firmata-client-libraries
 */

/*
 * This firmware reads all inputs and sends them as fast as it can.  It was
 * inspired by the ease-of-use of the Arduino2Max program.
 *
 * This example code is in the public domain.
 */
#include <Firmata.h>

byte pin;

int analogValue;
int previousAnalogValues[TOTAL_ANALOG_PINS];

byte portStatus[TOTAL_PORTS]; // each bit: 1=pin is digital input, 0=other/ignore
byte previousPINs[TOTAL_PORTS];

/* timer variables */
unsigned long currentMillis;     // store the current value from millis()
unsigned long previousMillis;    // for comparison with currentMillis
/* make sure that the FTDI buffer doesn't go over 60 bytes, otherwise you
   get long, random delays.  So only read analogs every 20ms or so */
int samplingInterval = 19;      // how often to run the main loop (in ms)

void sendPort(byte portNumber, byte portValue)
{
  portValue = portValue & portStatus[portNumber];
  if (previousPINs[portNumber] != portValue) {
    Firmata.sendDigitalPort(portNumber, portValue);
    previousPINs[portNumber] = portValue;
  }
}

void setup()
{
  byte i, port, status;

  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);

  for (pin = 0; pin < TOTAL_PINS; pin++) {
    if IS_PIN_DIGITAL(pin) pinMode(PIN_TO_DIGITAL(pin), INPUT);
  }

  for (port = 0; port < TOTAL_PORTS; port++) {
    status = 0;
    for (i = 0; i < 8; i++) {
      if (IS_PIN_DIGITAL(port * 8 + i)) status |= (1 << i);
    }
    portStatus[port] = status;
  }

  Firmata.begin(57600);
}

void loop()
{
  byte i;

  for (i = 0; i < TOTAL_PORTS; i++) {
    sendPort(i, readPort(i, 0xff));
  }
  /* make sure that the FTDI buffer doesn't go over 60 bytes, otherwise you
     get long, random delays.  So only read analogs every 20ms or so */
  currentMillis = millis();
  if (currentMillis - previousMillis > samplingInterval) {
    previousMillis += samplingInterval;
    while (Firmata.available()) {
      Firmata.processInput();
    }
    for (i = 0,pin = A0; pin < TOTAL_ANALOG_PINS+A0; i++,pin++) {
      analogValue = analogRead(pin);
      if (analogValue != previousAnalogValues[i]) {
        Firmata.sendAnalog(i, analogValue);
        previousAnalogValues[i] = analogValue;
      }
    }
  }
}


