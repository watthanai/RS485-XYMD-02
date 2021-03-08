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
 * This example demonstrates how to read out some basic information about
 * the WiMOD firmware
 *
 * Setup requirements:
 * -------------------
 * - 1 WiMOD module running LR-Base firmware / WiMOD LoRaWAN EndNode Modem
 *     firmware
 *
 * Usage:
 * -------
 * Start the program and watch the serial monitor @ 115200 baud
 *
 */


// make sure to use only the WiMODLR_BASE.h
// the WiMODLR_BASE.h must not be used for LR-BASE firmware.
#include <WiMODLR_BASE.h>
#if defined(ARDUINO_ARCH_AVR)
#include <avr/pgmspace.h>
#endif


/*
 * Create in instance of the interface to the WiMOD-LR-Base firmware
 */
WiMODLRBASE wimod(Serial3);  // use the Arduino Serial3 as serial interface


/*****************************************************************************
 * Functions for printing out some debug infos via serial interface
 ****************************************************************************/
void debugMsg(String msg)
{
    Serial.print(msg);  // use default Arduino serial interface
}

void debugMsg(int a)
{
    Serial.print(a, DEC);
}

void debugMsgChar(char c)
{
    Serial.print(c);
}

void debugMsgHex(int a)
{
    Serial.print(a, HEX);
}


/*****************************************************************************
 * print out a welcome message
 ****************************************************************************/


void printStartMsg()
{
    debugMsg(F("==================================================\n"));
    debugMsg(F("Starting...\n"));
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

}


/*****************************************************************************
 * read and print out the configuration of the WiMOD module
 ****************************************************************************/
void printWimdRadioConfig()
{
    TWiMODLR_DevMgmt_RadioConfig radioCfg;

    debugMsg(F("\n\n RadioConfig:\n"));


    // read the current configuration of the WiMOD module
    if (wimod.GetRadioConfig(&radioCfg)) {
        // print out some parts of the config
        debugMsg(F("GroupAdr:    "));
        debugMsg(radioCfg.GroupAddress);
        debugMsg(F("\n"));

        debugMsg(F("TxGroupAdr:  "));
        debugMsg(radioCfg.TxGroupAddress);
        debugMsg(F("\n"));

        debugMsg(F("DeviceAdr:   "));
        debugMsg(radioCfg.DeviceAddress);
        debugMsg(F("\n"));

        debugMsg(F("TxDeviceAdr: "));
        debugMsg(radioCfg.TxDeviceAddress);
        debugMsg(F("\n"));

        debugMsg(F("Modulation:  "));
        debugMsg((int) radioCfg.Modulation);    // see TRadioCfg_Modulation for symbolic meaning
        debugMsg(F("\n"));

        debugMsg(F("LoRa-BW ID:  "));
        debugMsg((int) radioCfg.LoRaBandWidth); // see TRadioCfg_LoRaBandwidth for symbolic meaning
        debugMsg(F("\n"));

        debugMsg(F("LoRa-EC ID:  "));
        debugMsg((int) radioCfg.ErrorCoding);   // see TRadioCfg_ErrorCoding for symbolic meaning
        debugMsg(F("\n"));

        debugMsg(F("LoRa-SF ID:  "));
        debugMsg((int) radioCfg.LoRaSpreadingFactor); // see TRadioCfg_LoRaSpreadingFactor for symbolic meaning
        debugMsg(F("\n"));
    }

}

/*****************************************************************************
 * read and print out some infos about the firmware of the WiMOD module
 ****************************************************************************/
void printWimodFirmwareInfos()
{
    TWiMODLR_DevMgmt_FwInfo fwInfo;

    debugMsg(F("\n\n FirmwareInfos:\n"));

    // readout the Firmware infomation
    if (wimod.GetFirmwareInfo(&fwInfo)) {
        debugMsg(F("FW-Name:  "));
        debugMsg((const char*) fwInfo.FirmwareName);
        debugMsg(F("\n"));

        debugMsg(F("FW-Date:  "));
        debugMsg((const char*) fwInfo.BuildDateStr);
        debugMsg(F("\n"));

        debugMsg(F("FW-Ver:   "));
        debugMsg(fwInfo.FirmwareMayorVersion);
        debugMsg(F("."));
        debugMsg(fwInfo.FirmwareMinorVersion);
        debugMsg(F("\n"));
    }
}



void loop()
{
    bool result;

    printWimdRadioConfig();

    printWimodFirmwareInfos();

    // check for any pending data of the WiMOD
    wimod.Process();

    delay(2000);
}

