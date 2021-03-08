/*****************************************************************************
* Arduino M0 / M0 Pro / Zero UartBridge
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
*       The uart select switch must be on position "A" (+ jumper on "UART0").
*
* Warning: Do not use the Firmware-update feature of the WiMOD PC-Tools
*          in combination with this program!!!
*
******************************************************************************/

char buff[500];
int len;

void setup() {
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial5.begin(115200);

}

void loop() {

  // put your main code here, to run repeatedly:
  len = SerialUSB.available();
  if (len > 0) {
      SerialUSB.readBytes(buff, len);
      Serial5.write(buff, len);
  }

  len = Serial5.available();
  if (len > 0) {
      Serial5.readBytes(buff, len);
      SerialUSB.write(buff, len);
  }

}
