/* -MASTER-
* This program sends strings of length 255 from the master to slave.
* Enable new line ending on master device
* connect RX of hc05 to pin 6 of the arduino and TX of hc05 to pin 5 of the arduino
*/

#include <SoftwareSerial.h>
#define RX 5
#define TX 6

SoftwareSerial BTserial(RX,TX);

int code;

void setup() {
  BTserial.begin(38400);
  Serial.begin(9600);
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    code = Serial.read(); //reads from serial monitor
    //Serial.println(code); //uncomment to print code sent from master to slave
    BTserial.write(code); //msg of 1 char is sent
  }
}
