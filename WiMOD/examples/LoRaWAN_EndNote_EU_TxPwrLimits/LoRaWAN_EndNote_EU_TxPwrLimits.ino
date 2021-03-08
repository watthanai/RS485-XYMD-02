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
 * This example demonstrates how to read out the EU TX power limits for the
 * EU subbands. LoRaWAN EndNode Modem firmware (V2 BC 140++ required)
 *
 * Setup requirements:
 * -------------------
 * - 1 WiMOD module running WiMOD LoRaWAN EndNode firmware
 *
 * Usage:
 * -------
 * Start the program and watch the serial monitor @ 115200 baud
 *
 */


#include <stdio.h>
#include <stdint.h>


// make sure to use only the WiMODLoRaWAN.h
// the WiMODLR_BASE.h must not be used for LoRaWAN firmware.
#include <WiMODLoRaWAN.h>


//-----------------------------------------------------------------------------
// section RAM
//-----------------------------------------------------------------------------

/*
 * Create in instance of the interface to the WiMOD-LR-Base firmware
 */
WiMODLoRaWAN wimod(Serial3);  // use the Arduino Serial3 as serial interface



//-----------------------------------------------------------------------------
// section code
//-----------------------------------------------------------------------------


/*****************************************************************************
 * Function for printing out some debug infos via serial interface
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

void printPayload(const uint8_t* buf, uint8_t size) {
  for (int i = 0; i < size; i++) {
	if ((uint8_t) buf[i] < 0x10) {
	  Serial.print(F("0"));
	}
    Serial.print((uint8_t) buf[i], HEX);
    Serial.print(F(" "));
  }
  Serial.print(F("\n"));
}


/******************************************************************************
 * print tx TX power limits
 *
 *****************************************************************************/

void printTxPowerLimits(void)
{
	TWiMODLORAWAN_TxPwrLimitConfig cfg;
	uint8_t						   i;

	if (wimod.GetTxPowerLimitConfig(&cfg)) {

		for (i = 0;i < cfg.NumOfEntries; i++) {
			debugMsg(F("Entry #"));
			debugMsg(i+1);
			debugMsg(F(" of "));
			debugMsg(cfg.NumOfEntries);
			debugMsg(F("\r\n"));

			debugMsg(F("SubBand-Index: "));
			debugMsg(cfg.SubBandIndex[i]);
			debugMsg(F("\r\n"));

			debugMsg(F("PwrLimitFlag: "));
			debugMsg(cfg.TxPwrLimitFlag[i]);
			debugMsg(F("\r\n"));

			debugMsg(F("PwrLimitFlag: "));
			debugMsg(cfg.TxPwrLimitValue[i]);
			debugMsg(F("\r\n"));
			debugMsg(F("\r\n"));
		}
		debugMsg(F("\r\n"));

	}
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
    debugMsg(F("the configured TX Power Limits for EU subbands\n"));
    debugMsg(F("(only for EU firmware)\n"));
    debugMsg(F("==================================================\n"));
}


/*****************************************************************************
 * get RTC - get time from WiMOD and print it
 ****************************************************************************/

void getRTC()
{
    uint32_t timestamp;
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  hour;
	uint8_t  min;
	uint8_t  sec;


    // try to get the RTC information out of the WiMOD
    if (wimod.GetRtc(&timestamp)) {
        year  = WIMOD_RTC_GET_YEARS(timestamp);
        month = WIMOD_RTC_GET_MONTHS(timestamp);
        day   = WIMOD_RTC_GET_DAYS(timestamp);
        hour  = WIMOD_RTC_GET_HOURS(timestamp);
        min   = WIMOD_RTC_GET_MINUTES(timestamp);
        sec   = WIMOD_RTC_GET_SECONDS(timestamp);

        debugMsg("WiMOD RTC: ");

        debugMsg((int) year);
        debugMsg("-");
        debugMsg((int) month);
        debugMsg("-");
        debugMsg((int) day);
        debugMsg(" ");
        debugMsg((int) hour);
        debugMsg(":");
        debugMsg((int) min);
        debugMsg(":");
        debugMsg((int) sec);
        debugMsg("\r\n");

    } else {
        // error
        debugMsg("Error getting current timestamp of WiMOD\r\n");
    }
}


/*****************************************************************************
 * Arduino setup function
 ****************************************************************************/
void setup()
{
    // init / setup the serial interface connected to WiMOD
    Serial3.begin(WIMOD_LORAWAN_SERIAL_BAUDRATE);
    // init the communication stack
    wimod.begin(LoRaWAN_Region_EU868);

    // debug interface
    Serial.begin(115200);

    delay(100);

    printStartMsg();

    printTxPowerLimits();

    debugMsg(F("\r\n\r\n"));
    debugMsg(F("--------------------------------------------------\r\n"));
}


/*****************************************************************************
 * Arduino loop function
 ****************************************************************************/

uint32_t loopCnt = 0;

void loop()
{

	// print out the current RTC information every 5 sec.
	if ((loopCnt % 50) == 0) {
		getRTC();
	}

    // check for any pending data of the WiMOD
    wimod.Process();

    delay(100);
    loopCnt++;
}
