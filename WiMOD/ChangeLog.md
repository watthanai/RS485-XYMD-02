# ChangeLog

This file gives a short overview about the changes of the library.

## V1.0.0 (2017-02-20)
* Pre-release Version for beta testing

## V1.1.0 (2017-03-08)
* First release version
* added support for non AVR-based boards 
 
## V1.2.0 (2017-05-25)
* BUG-FIX: CRC generation for some non AVR-based boards was wrong
* added possibility to use Cpp11 function objects for callback mechanism. (Since not all platforms support Cpp11 (by now) this feauture has to be manually activated by the user! see "#define WIMOD_USE_CPP11")

## V1.3.0 (2017-06-05)
* adoption to LoRaWAN EndNode Modem Firmware V 2.0

## V1.3.1 (2017-06-26)
* BUG-FIX: fixed with of DevAddr in the example files
* Added new example showing how to read out some LoRaWAN related infos of a radio module
* minor documentation update

## V1.3.2 (2017-08-21)
* Added the MIC-field within RadioLinkMessage
* fixed a typo in an encryption related define
* added the airtime parameter of spec V1.10
* modified the TRadioLinkUDataTxIndicationCallback  (according to spec V1.10)

## V1.4.0 (2018-02-28)
* gernal LoRaWAN upate according to HCI spev V1.22 + Regionalsettings 
