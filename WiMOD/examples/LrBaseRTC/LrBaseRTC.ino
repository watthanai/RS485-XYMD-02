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
 * This example demonstrates how to get and set the RTC of the WiMOD
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


typedef struct TWimodTime
{
    UINT16  year;
    UINT8   month;
    UINT8   day;
    UINT8   hour;
    UINT8   min;
    UINT8   sec;
} TWimodTime;


// function prototypes
void debugMsg(String msg);
void debugMsgInt(int a);
void showWimodTime(TWimodTime* moduleTime);
void printStartMsg();
void setRTC();
void getRTC();


// define a date
static TWimodTime wimodTime = { .year  = 2016,
                                .month = 8,
                                .day   = 23,
                                .hour  = 10,
                                .min   = 30,
                                .sec   = 40};


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

void debugMsgInt(int a)
{
    Serial.print(a, DEC);
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
    debugMsg(F("how to use the RTC feature of the WiMOD Radio Module\n"));
    debugMsg(F("==================================================\n"));
}

/*****************************************************************************
 * print time
 ****************************************************************************/
void showWimodTime(TWimodTime* moduleTime)
{
    if (moduleTime) {
        debugMsgInt((int)moduleTime->year);
        debugMsg("-");
        debugMsgInt((int)moduleTime->month);
        debugMsg("-");
        debugMsgInt((int)moduleTime->day);
        debugMsg(" ");
        debugMsgInt((int)moduleTime->hour);
        debugMsg(":");
        debugMsgInt((int)moduleTime->min);
        debugMsg(":");
        debugMsgInt((int)moduleTime->sec);
        debugMsg("\r\n");
    }
}

/*****************************************************************************
 * set RTC - set the time in WiMOD
 ****************************************************************************/
void setRTC()
{
    UINT32 timestamp;

    // convert date/time to timestamp format
    timestamp = WIMOD_RTC_MAKE_DATETIME_U32(wimodTime.sec,   \
                                            wimodTime.min,   \
                                            wimodTime.hour,  \
                                            wimodTime.day,   \
                                            wimodTime.month, \
                                            wimodTime.year);

    // try to set the RTC to specified date/time
    if (wimod.SetRtc(timestamp)) {
        debugMsg("Setup of RTC: OK\r\n");

        debugMsg("WiMOD time has been  set to: ");
        showWimodTime(&wimodTime);
    } else {
        debugMsg("Setup of RTC: Failed\r\n");
    }
}

/*****************************************************************************
 * get RTC - get time from WiMOD and print it
 ****************************************************************************/

void getRTC()
{
    UINT32 timestamp;

    // try to get the RTC information out of the WiMOD
    if (wimod.GetRtc(&timestamp)) {
        wimodTime.year  = WIMOD_RTC_GET_YEARS(timestamp);
        wimodTime.month = WIMOD_RTC_GET_MONTHS(timestamp);
        wimodTime.day   = WIMOD_RTC_GET_DAYS(timestamp);
        wimodTime.hour  = WIMOD_RTC_GET_HOURS(timestamp);
        wimodTime.min   = WIMOD_RTC_GET_MINUTES(timestamp);
        wimodTime.sec   = WIMOD_RTC_GET_SECONDS(timestamp);

        debugMsg("WiMOD time is now: ");
        showWimodTime(&wimodTime);

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
    Serial3.begin(WIMOD_LR_BASE_SERIAL_BAUDRATE);
    // init the communication stack
    wimod.begin();

    // debug interface
    Serial.begin(115200);

    printStartMsg();

    // wait a while (for the user to open the serial monitor)
    delay(1000);

    // init the RTC time to specified date
    setRTC();
}


void loop()
{
    getRTC();

    // check for any pending data of the WiMOD
    wimod.Process();

    delay(2000);
}
