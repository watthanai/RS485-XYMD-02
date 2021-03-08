/*****************************************************************************
* Arduino DUE UartBridge
*
* This programm receives the usart data from one serial interface and
* sends the data to the other serial interface. And vice versa.
*
* This allows the user to use the PC-Tools to communicate with the WiMOD
* module mounted on the boards.
*
* Note: This sketch is for Arduino devices with two separate interfaces.
*       One for the PC and one for the WiMOD.
*
*       The uart select switch must be on position "A". (+ jumper on "UART3").
*
* Warning: Do not use the Firmware-update feature of the WiMOD PC-Tools
*          in combination with this program!!!
******************************************************************************/

byte buff[500];
int len;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);

}

void loop() {

  // put your main code here, to run repeatedly:
  len = Serial.available();
  if (len > 0) {
      Serial.readBytes(buff, len);
      Serial3.write(buff, len);
  }

  len = Serial3.available();
  if (len > 0) {
      Serial3.readBytes(buff, len);
      Serial.write(buff, len);
  }

  // do not use a delay() function here.
  // the arduino plaform uses a 64 byte low level buffer that is likely to
  // overflow, if a delay is used here
}
