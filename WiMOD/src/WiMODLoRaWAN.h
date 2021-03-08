//------------------------------------------------------------------------------
//! @file WiMODLoRaWAN.h
//! @ingroup WiMODLoRaWAN
//! <!------------------------------------------------------------------------->
//! @brief Declarations for the High-level Interface for WiMOD LoRaWAN EndNode Modem firmware
//! @version 0.1
//! <!------------------------------------------------------------------------->
//!
//! 
//!
//! <!--------------------------------------------------------------------------
//! Copyright (c) 2016
//! IMST GmbH
//! Carl-Friedrich Gauss Str. 2-4
//! 47475 Kamp-Lintfort
//! --------------------------------------------------------------------------->
//! @author (FB), IMST
//! <!--------------------------------------------------------------------------
//! Target OS:    none
//! Target CPU:   tbd
//! Compiler:     tbd
//! --------------------------------------------------------------------------->
//! @internal
//! @par Revision History:
//! <PRE>
//!-----------------------------------------------------------------------------
//! Version | Date       | Author | Comment
//!-----------------------------------------------------------------------------
//!
//! </PRE>
//------------------------------------------------------------------------------


#ifndef ARDUINO_WIMODLORAWAN_H_
#define ARDUINO_WIMODLORAWAN_H_



/**
 * THIS IS AN EXAMPLE IMPLEMENTATION ACCORDING THE THE HCI SPEC: V1.22
 * FOR FIRMWARE: LoRaWAN
 */


//------------------------------------------------------------------------------
//
// Section Includes Files
//
//------------------------------------------------------------------------------

#include "Arduino.h"
//#include <cstddef>
#include <string.h>

#include "SAP/WiMOD_SAP_LORAWAN.h"
#include "SAP/WiMOD_SAP_DEVMGMT.h"
#include "utils/ComSLIP.h"
#include "HCI/WiMODLRHCI.h"

//-----------------------------------------------------------------------------
// common defines
//-----------------------------------------------------------------------------
//! @cond Doxygen_Suppress
#define WIMOD_LORAWAN_SERIAL_BAUDRATE               115200

#define WiMOD_LORAWAN_TX_BUFFER_SIZE                256
//! @endcond
//-----------------------------------------------------------------------------
// types for callback functions
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// API class declaration for the WiMOD LR BASE Stack
//
// note: this is NOT compliant with the WiMOD LoRaWAN Stack
//-----------------------------------------------------------------------------
/**
 * @brief Main class representing the interface to the WiMOD running the firmware LoRaWAN EndNode Modem
 *
 * This class is the only API class a user should use for interacting with
 * a WiMOD module that runs the IMST LoRaWAN EndNode Modem firmware.
 *
 */
class WiMODLoRaWAN : public TWiMODLRHCI {
public:
    /*explicit*/ WiMODLoRaWAN(Stream& s);
    ~WiMODLoRaWAN(void);

    void begin(TLoRaWANregion region = LoRaWAN_Region_EU868);
    void end(void);

    //! @cond Doxygen_Suppress
    void beginAndAutoSetup(void);
    void autoSetupSupportedRegion(void);
    //! @endcond

    /*
     * DevMgmt SAP
     */
    bool Ping(TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool Reset(TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetDeviceInfo(TWiMODLR_DevMgmt_DevInfo* info, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetFirmwareInfo(TWiMODLR_DevMgmt_FwInfo* info, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetSystemStatus(TWiMODLR_DevMgmt_SystemStatus* info, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetRtc(UINT32* rtcTime,TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetRtc(const UINT32 rtcTime, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);

    bool GetOperationMode(TWiMOD_OperationMode* opMode, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetOperationMode(const TWiMOD_OperationMode opMode, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);

    bool SetRtcAlarm(const TWiMODLR_DevMgmt_RtcAlarm* rtcAlarm, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetRtcAlarm(TWiMODLR_DevMgmt_RtcAlarm* rtcAlarm, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool ClearRtcAlarm(TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);

    void RegisterPowerUpIndicationClient(TDevMgmtPowerUpCallback cb);
    void RegisterRtcAlarmIndicationClient(TDevMgmtRtcAlarmCallback cb);


    /*
     * LoRaWAN SAP
     */
    bool ActivateDevice(TWiMODLORAWAN_ActivateDeviceData& activationData,TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool ReactivateDevice(UINT32* devAdr, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetJoinParameter(TWiMODLORAWAN_JoinParams& joinParams, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool JoinNetwork(TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);

    void RegisterJoinTxIndicationClient(TJoinTxIndicationCallback cb);

    bool
    convert(TWiMODLR_HCIMessage& RxMsg, TWiMODLORAWAN_RX_Data* loraWanRxData);
    bool
    convert(TWiMODLR_HCIMessage& rxMsg, TWiMODLORAWAN_TxIndData* sendIndData);

    bool
    convert(TWiMODLR_HCIMessage& RxMsg, TWiMODLORAWAN_RX_MacCmdData* loraWanMacCmdData);

    bool
    convert(TWiMODLR_HCIMessage& RxMsg,TWiMODLORAWAN_RX_JoinedNwkData* joinedNwkData);

    bool
    convert(TWiMODLR_HCIMessage& RxMsg, TWiMODLORAWAN_RX_ACK_Data* ackData);

    bool
	convert(TWiMODLR_HCIMessage& RxMsg, TWiMODLORAWAN_NoData_Data* info);

    void
    RegisterNoDataIndicationClient(TNoDataIndicationCallback cb);

    void
    RegisterTxCDataIndicationClient(TTxCDataIndicationCallback cb);

    void
    RegisterTxUDataIndicationClient(TTxUDataIndicationCallback cb);

    void
    RegisterRxUDataIndicationClient(TRxUDataIndicationCallback cb);

    void
    RegisterRxCDataIndicationClient(TRxCDataIndicationCallback cb);

    void
    RegisterRxMacCmdIndicationClient(TRxMacCmdIndicationCallback cb);

    void
    RegisterJoinedNwkIndicationClient(TJoinedNwkIndicationCallback cb);

    void
    RegisterRxAckIndicationClient(TRxAckIndicationCallback cb);

    bool SendUData(const TWiMODLORAWAN_TX_Data* data, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SendCData(const TWiMODLORAWAN_TX_Data* data,TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetRadioStackConfig(TWiMODLORAWAN_RadioStackConfig* data,TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetRadioStackConfig(TWiMODLORAWAN_RadioStackConfig* data, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool DeactivateDevice(TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool FactoryReset(TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetDeviceEUI(const UINT8* deviceEUI, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetDeviceEUI(UINT8* deviceEUI, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
//    bool GetNwkStatus(UINT8* nwkStatus, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL); // implementation for spec up to  V1.13
    bool GetNwkStatus(TWiMODLORAWAN_NwkStatus_Data*	nwkStatus, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL); // new implementation for spec. V1.14
    bool SendMacCmd(const TWiMODLORAWAN_MacCmd* cmd, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetCustomConfig(const INT8 rfGain, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetCustomConfig(INT8* rfGain, TWiMDLRResultCodes* hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetSupportedBands(TWiMODLORAWAN_SupportedBands* supportedBands, TWiMDLRResultCodes*  hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetTxPowerLimitConfig(TWiMODLORAWAN_TxPwrLimitConfig* txPwrLimitCfg, TWiMDLRResultCodes*  hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetTxPowerLimitConfig(TWiMODLORAWAN_TxPwrLimitConfig& txPwrLimitCfg, TWiMDLRResultCodes*  hciResult = NULL, UINT8* rspStatus = NULL);
    bool GetLinkAdrReqConfig(TWiMODLORAWAN_LinkAdrReqConfig* linkAdrReqCfg, TWiMDLRResultCodes*  hciResult = NULL, UINT8* rspStatus = NULL);
    bool SetLinkAdrReqConfig(TWiMODLORAWAN_LinkAdrReqConfig& linkAdrReqCfg, TWiMDLRResultCodes*  hciResult = NULL, UINT8* rspStatus = NULL);


    TWiMDLRResultCodes  GetLastHciResult(void);
    UINT8               GetLastResponseStatus(void);

protected:
    WiMOD_SAP_DevMgmt   SapDevMgmt;                                             /*!< Service Access Point for 'DeviceManagement' */
    WiMOD_SAP_LoRaWAN   SapLoRaWan;                                             /*!< Service Access Point for 'LoRaWAN' */


    virtual void       ProcessUnexpectedRxMessage(TWiMODLR_HCIMessage& rxMsg);

    bool               copyLoRaWanResultInfos(TWiMDLRResultCodes* hciResult, UINT8* rspStatus);
    bool               copyDevMgmtResultInfos(TWiMDLRResultCodes* hciResult, UINT8* rspStatus);
private:
    //! @cond Doxygen_Suppress
    UINT8               txBuffer[WiMOD_LORAWAN_TX_BUFFER_SIZE];

    UINT8               localStatusRsp;
    bool                cmdResult;
    TWiMDLRResultCodes  localHciRes;

    TWiMDLRResultCodes  lastHciRes;
    UINT8               lastStatusRsp;
    //! @endcond
};


#endif /* ARDUINO_WIMODLORAWAN_H_ */
