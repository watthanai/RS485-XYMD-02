//------------------------------------------------------------------------------
//! @file WiMOD_SAP_DEVMGMT.h
//! @ingroup WiMOD_SAP_DEVMGMT
//! <!------------------------------------------------------------------------->
//! @brief Declarations for the DeviceManagement SericeAccessPoint
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


#ifndef ARDUINO_WIMOD_SAP_DEVMGMT_H_
#define ARDUINO_WIMOD_SAP_DEVMGMT_H_


/*
 * THIS IS AN EXAMPLE IMPLEMENTATION ACCORDING THE THE HCI SPEC: V1.8
 * FOR FIRMWARE: LR-BASE
 *
 * SEE FILE: WiMOD_LR_Base_HCI_Spec_V1_8.pdf for detailed information
 *
 */

//------------------------------------------------------------------------------
//
// Section Includes Files
//
//------------------------------------------------------------------------------

#include "WiMOD_SAP_DEVMGMT_IDs.h"
#include "../HCI/WiMODLRHCI.h"

/*
 * C++11 supports a better way for function pointers / function objects
 * But C++11 mode is not supported by all platforms.
 */
#ifdef WIMOD_USE_CPP11
#include <functional>
#endif

//------------------------------------------------------------------------------
//
// Section defines
//
//------------------------------------------------------------------------------
/** Buffer size for DevMgmt related messages */
#define WiMOD_DEVMGMT_MSG_SIZE               (100)


//-----------------------------------------------------------------------------
//
// types for callback functions
//
//-----------------------------------------------------------------------------

// C++11 check
#ifdef WIMOD_USE_CPP11
	/* C++11 function callback definitions */

	/** Type definition for a 'device power up' indication callback  */
	typedef std::function<void (void)> TDevMgmtPowerUpCallback;


	/** Type definition for a 'RTC alarm' indication callback  */
	typedef std::function<void (void)> TDevMgmtRtcAlarmCallback;

#else
	/* pre C++11 function callback definitions */

	/** Type definition for a 'device power up' indication callback function */
	typedef void (*TDevMgmtPowerUpCallback)(void);

	/** Type definition for a 'RTC alarm' indication callback function */
	typedef void (*TDevMgmtRtcAlarmCallback)(void);

#endif

//------------------------------------------------------------------------------
//
// Section class
//
//------------------------------------------------------------------------------

/**
 * @brief Implementation for the ServiceAccessPoint DeviceManagement
 */
class WiMOD_SAP_DevMgmt {
public:
    WiMOD_SAP_DevMgmt(TWiMODLRHCI* hci, UINT8* buffer, UINT16 bufferSize);
    ~WiMOD_SAP_DevMgmt(void);

    TWiMDLRResultCodes Ping(UINT8* statusRsp);

    TWiMDLRResultCodes Reset(UINT8* statusRsp);

    TWiMDLRResultCodes GetDeviceInfo(TWiMODLR_DevMgmt_DevInfo* info, UINT8* statusRsp);

    TWiMDLRResultCodes GetFirmwareInfo(TWiMODLR_DevMgmt_FwInfo* info, UINT8* statusRsp);

    TWiMDLRResultCodes GetSystemStatus(TWiMODLR_DevMgmt_SystemStatus* info, UINT8* statusRsp);

    TWiMDLRResultCodes GetRtc(UINT32* rtcTime, UINT8* statusRsp);

    TWiMDLRResultCodes SetRtc(const UINT32 rtcTime, UINT8* statusRsp);

    TWiMDLRResultCodes GetRadioConfig(TWiMODLR_DevMgmt_RadioConfig* radioCfg, UINT8* statusRsp);

    TWiMDLRResultCodes SetRadioConfig(const TWiMODLR_DevMgmt_RadioConfig* radioCfg, UINT8* statusRsp);

    TWiMDLRResultCodes ResetRadioConfig(UINT8* statusRsp);

    TWiMDLRResultCodes GetOperationMode(TWiMOD_OperationMode* opMode, UINT8* statusRsp);

    TWiMDLRResultCodes SetOperationMode(const TWiMOD_OperationMode opMode, UINT8* statusRsp);

    TWiMDLRResultCodes SetAesKey(const UINT8* key, UINT8* statusRsp);

    TWiMDLRResultCodes GetAesKey(UINT8* key, UINT8* statusRsp);

    TWiMDLRResultCodes SetRtcAlarm(const TWiMODLR_DevMgmt_RtcAlarm* rtcAlarm, UINT8* statusRsp);

    TWiMDLRResultCodes GetRtcAlarm(TWiMODLR_DevMgmt_RtcAlarm* rtcAlarm, UINT8* statusRsp);

    TWiMDLRResultCodes ClearRtcAlarm(UINT8* statusRsp);


    void               RegisterPowerUpIndicationClient(TDevMgmtPowerUpCallback cb);

    void               RegisterRtcAlarmIndicationClient(TDevMgmtRtcAlarmCallback cb);

    void               DispatchDeviceMgmtMessage(TWiMODLR_HCIMessage& rxMsg);
protected:

private:
    //! @cond Doxygen_Suppress
    UINT8*              txPayload;
    UINT16              txyPayloadSize;

    TDevMgmtPowerUpCallback  PowerUpCallack;
    TDevMgmtRtcAlarmCallback RtcAlarmCallback;

    TWiMODLRHCI*       HciParser;
    //! @endcond
};


#endif /* ARDUINO_WIMOD_SAP_DEVMGMT_H_ */
