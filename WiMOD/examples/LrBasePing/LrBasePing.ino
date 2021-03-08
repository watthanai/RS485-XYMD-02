/*
 * This is a simple example file to show how to use the WiMOD Arduino
 * library to communicate with a WiMOD Module by IMST GmbH
 *
 * http://www.wireless-solutions.de
 *
 */


/*
 * Example:
 *
 * This example demonstrates how to issue a (local) ping command to the WiMOD.
 * There is no radio communication involved in this example.
 *
 * Setup requirements:
 * -------------------
 * - 1 WiMOD module running LR-Base or LoRaWAN EndNode Modem firmware
 *
 * Usage:
 * -------
 * Start the program and watch the serial monitor @ 115200 baud
 *
 */




// make sure to use only the WiMODLR_BASE.h
// the WiMODLR_BASE.h must not be used for LoRaWAN firmware.
#include <WiMODLR_BASE.h>
#include <avr/pgmspace.h>


/*
 * Create in instance of the interface to the WiMOD-LR-Base firmware
 */
WiMODLRBASE wimod(Serial3);  // use the Arduino Serial3 as serial interface

/*****************************************************************************
 * Function for printing out some debug infos via serial interface
 ****************************************************************************/
void debugMsg(String msg)
{
    Serial.print(msg);  // use default Arduino serial interface
}

/*****************************************************************************
 * print out a welcome message
 ****************************************************************************/
void printStartMsg()
{
    debugMsg(F("==================================================\n"));
    debugMsg(F("This is FileName: "));
    debugMsg(F(__FILE__));
    debugMsg(F("\r\n"));
    debugMsg(F("Starting...\n"));
    debugMsg(F("This simple demo will show \n"));
    debugMsg(F("how to ping a WiMOD radio module\n"));
    debugMsg(F("running the LR-Base or LoRaWAN Firmware.\n"));
    debugMsg(F("==================================================\n"));
}




/*****************************************************************************
 * Arduino setup function
 ****************************************************************************/
void setup()
{
    // init / setup the serial interface connected to WiMOD
    Serial3.begin(WIMOD_LR_BASE_SERIAL_BAUDRATE);
    // init the communication stack
    wimod.begin();

    // debug interface
    Serial.begin(115200);

    printStartMsg();

    delay(100);
}


void loop()
{
    debugMsg(F("Ping WiMOD: "));
    if (wimod.Ping() == true) {
        debugMsg(F("OK\n"));
    } else {
        debugMsg(F("FAILED\n"));
    }

    // check for any pending data of the WiMOD
    wimod.Process();

    delay(2000);
}
