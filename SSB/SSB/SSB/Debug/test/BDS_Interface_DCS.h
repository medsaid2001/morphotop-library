/************************************************************/
/**
 * @file BDS_Interface_DCS.h
 * @brief Definition of the Device Communication Services Interface
 *
 * Copyright (c) SAGEM Défense Sécurité
 *
 * - PROJET      : SLAP
 * - MODULE      : BDS Interfaces
 * - DATE        : August,21 2006
 *
 */
/************************************************************/

#if !defined(BDS_Interface_DCS)
#define BDS_Interface_DCS

/************************************************************/
/** EntryPoints for interface */
enum {
	_BDS_EnumerateBiometricDevices,
	_BDS_OpenBiometricDeviceSession,
	_BDS_CloseBiometricDeviceSession,
	_BDS_OpenAdministrationDeviceSession,
	_BDS_CloseAdministrationDeviceSession,
	_BDS_ExchangeCommandWithBiometricDevice,
	DCS_ENTRYPOINTS_COUNT
};

/************************************************************/
/** @defgroup groupDCS Device communication services
*/
/*@{*/

/** @brief Version of the interface */
#define BDS_DCS_VERSION	2

/** @brief Return code for communication services */
typedef enum {	
	RC_DCS_INVALID_DEVICE_INDEX,		/**< Index is wrong */	
} BDS_CommunicationReturnCodes;

/**
 * This service enumerates the found biometric imaging devices
 * managed by the BDS software and builds the table of
 * hardware descriptors. The memory is allocated by the service,
 * and must be freed by the caller.
 *
 * @param[out]  o_p_deviceCount
 *				Number of identified devices (they can be indexed
 *              from 0 to o_pi_deviceCount-1)
 * @param[out]  o_p_deviceTable
 *				Table of hardware informations for identified devices
 * @retval 0 Success
 */
DEFINE_API	( BDS_EnumerateBiometricDevices, int,
				(int * const o_p_deviceCount,
				BDS_DeviceDescriptor o_p_deviceTable[])
			);

/**
 * This service initializes the communications with the biometric 
 * imaging device. 
 *
 * @param[in]  i_i_deviceIndex 
 *             Index of the device (must be set  between 0 and 
 *             the device count returned by BDS_EnumerateBiometricDevices)
 * @param[in]  i_i_deviceHandle 
 *             Handle of the device to pass to the acquisition function
 * @param[in]  i_device 
 *             High-level device structure 
 * @retval 0 Success
 * @retval RC_DCS_INVALID_DEVICE_INDEX The index is out of bound
 */
DEFINE_API	( BDS_OpenBiometricDeviceSession, int,
				(const int i_i_deviceIndex,
				const int i_i_deviceHandle,
				BDS_Device * const i_device)
			);

/**
 * This service closes the communications with the biometric 
 * imaging device.
 *
 * @param[in]  i_i_deviceIndex
 *             Device index used in BDS_OpenBiometricDeviceSession
 * @retval 0 Success
 * @retval RC_DCS_INVALID_DEVICE_INDEX The index is out of bound
 */
DEFINE_API	( BDS_CloseBiometricDeviceSession, int,
				(const int i_i_deviceIndex)
			);

/**
 * This service initializes the communications with the biometric 
 * imaging device without image producing. 
 *
 * @param[in]  i_i_deviceIndex 
 *             Index of the device (must be set  between 0 and 
 *             the device count returned by BDS_EnumerateBiometricDevices)
 * @param[in]  i_i_deviceHandle 
 *             Handle of the device to pass to the acquisition function
 * @param[in]  i_device 
 *             High-level device structure 
 * @retval 0 Success
 * @retval RC_DCS_INVALID_DEVICE_INDEX The index is out of bound
 */
DEFINE_API	( BDS_OpenAdministrationDeviceSession, int,
				(const int i_i_deviceIndex,
				const int i_i_deviceHandle,
				BDS_Device * const i_device)
			);

/**
 * This service closes the communications with the biometric 
 * imaging device without image producing.
 *
 * @param[in]  i_i_deviceIndex
 *             Device index used in BDS_OpenAdministrationDeviceSession
 * @retval 0 Success
 * @retval RC_DCS_INVALID_DEVICE_INDEX The index is out of bound
 */
DEFINE_API	( BDS_CloseAdministrationDeviceSession, int,
				(const int i_i_deviceIndex)
			);

/**
 * This service send a command to a biometric device and returns
 * its response. Data exchanged with the device are transparently
 * processed by the SDK over the command channel of the device.
 *
 * @param[in]  i_i_deviceIndex 
 *             Index of the device (must be set  between 0 and 
 *             the device count returned by BDS_EnumerateBiometricDevices)
 * @param[in]  i_p_commandData
 *             Command data (ILV device formatted)
 * @param[out] o_p_responseData
 *             Returned response data
 * @retval 0 Success
 * @retval RC_DCS_INVALID_DEVICE_INDEX The index is out of bound
 */
DEFINE_API	( BDS_ExchangeCommandWithBiometricDevice, int,
				(const int i_i_deviceIndex,
				const char * const i_p_commandData,
				char * const o_p_responseData)
			);

/*@}*/
/************************************************************/

#endif
