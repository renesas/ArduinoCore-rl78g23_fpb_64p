/*
  Software serial multple serial test
  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.
  Only the following pins can be used for RX:
  D4, D6, D7, D11, D12, D13, D26
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
