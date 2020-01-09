/************************************************************/
/**
 * @file BDS_Interface_XCS.h
 * @brief Definition of the External Customer Services Interface
 *
 * Copyright (c) SAGEM Défense Sécurité
 *
 * - PROJET      : SLAP
 * - MODULE      : BDS Interfaces
 * - DATE        : August,21 2006
 *
 */
/************************************************************/

#if !defined(BDS_Interface_XCS)
#define BDS_Interface_XCS

/************************************************************/
/** EntryPoints for interface */
enum {
	_BDS_EnumerateUsableBiometricDevices,
	_BDS_OpenBiometricDevice,
	_BDS_CloseBiometricDevice,
	_BDS_GetBiometricDeviceDescriptor,
	_BDS_SetParametersForLiveMode,
	_BDS_SetParametersForDirectMode,
	_BDS_SetParametersForDetectionMode,
	_BDS_SetParametersForRolledFingerMode,
	_BDS_SetProcessParameters,
	_BDS_GetDirectImage,
	_BDS_GetDetectedImage,
	_BDS_GetRolledFingerImage,
	_BDS_FreeMemoryOfImage,
	_BDS_DefineLiveProcess,
	_BDS_CalibrateDeviceForExploitation,
	_BDS_Autotest,
	_BDS_SetLedState,
	_BDS_VerifyImage,
	_BDS_ReadFileImage,
	_BDS_WriteFileImage,
	_BDS_GetInformationDescription,
	_BDS_GetStaticInformations,
	_BDS_GetDeviceInformations,
	_BDS_GetImageSizeInformations,
	_BDS_AnalyseImage,
	_BDS_SetBuzzer,
	_BDS_SetParametersForSignatureMode,
	_BDS_GetSignature,
	XCS_ENTRYPOINTS_COUNT
};

/************************************************************/
/** @defgroup groupXCS External customer services
*/
/*@{*/

/** @brief Global BDS definitions */
#include "BDS_Common.h"

/** @brief Device Communication Services*/
#include "BDS_Interface_DCS.h"

/** @brief Version of the interface */
#define BDS_XCS_VERSION	4

/************************************************************/
/** @defgroup groupXCSDevices Devices External customer services
*/
/*@{*/

/**
 * This service enumerates the found biometric imaging devices
 * managed by the BDS software.
 *
 * @param[out]  o_pi_deviceCount
 *				Number of identified devices (they can be indexed
 *              from 0 to o_pi_deviceCount-1)
 * @retval 0 Success
 * @retval RC_NO_DEVICE_AVAILABLE No imaging devices can be started
 */
DEFINE_API	( BDS_EnumerateUsableBiometricDevices, int,
				(int * const o_pi_deviceCount)
			);

/**
 * This service initializes the communications with the biometric 
 * imaging device.
 *
 * @param[in]  i_i_deviceIndex 
 *             Index of the device (must be set  between 0 and 
 *             the device count returned by BDS_EnumerateUsableBiometricDevices)
 * @param[out] o_p_deviceHandle 
 *             Device handle returned to be used in the next
 *             requests to the device (until BDS_CloseBiometricDevice)
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_INDEX The index is out of bound
 * @retval RC_DEVICE_ALREADY_OPEN The device is already open
 * @retval RC_UNKNOWN_DEVICE The device cannot be opened
 */
DEFINE_API	( BDS_OpenBiometricDevice, int,
				(const int i_i_deviceIndex,
				int * o_p_deviceHandle,
				void * const i_p_userData )
			);

/**
 * This service closes the communications with the biometric 
 * imaging device.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_CloseBiometricDevice, int,
				(const int i_i_deviceHandle)
			);

/**
 * This service reads the imaging device informations.
 *
 * @param[in]  i_i_deviceIndex 
 *             Index of the device (must be set  between 0 and 
 *             the device count returned by BDS_EnumerateUsableBiometricDevices)
 * @param[out] o_p_deviceDescriptor
 *             Device descriptor
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_INDEX The index is out of bound
 * @retval RC_DEVICE_NOT_MANUFACTURED The format of manufacturing information has not been recognized */
DEFINE_API	( BDS_GetBiometricDeviceDescriptor, int,
				(const int i_i_deviceIndex,
				BDS_DeviceDescriptor * o_p_deviceDescriptor)
			);

/*@}*/
/************************************************************/


/************************************************************/
/** @defgroup groupXCSAcquisition Acquisition External customer services
*/
/*@{*/

/**
 * This service defines the acquisition parameters for the
 * live mode of image acquisition. In each direction,
 * the decimation is defined by the sampling mode.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_i_samplingMode
 *             Type of sampling
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_DEVICE_NOT_MANUFACTURED The device has not been manufactured
 * @retval RC_INVALID_SAMPLING_MODE The sampling mode is wrong
 */
DEFINE_API	( BDS_SetParametersForLiveMode, int,
				(const int i_i_deviceHandle,
				 const int i_i_samplingMode)
			);

/**
 * This service defines the acquisition parameters for the
 * direct mode of image acquisition. In each direction,
 * the decimation is defined by the sampling mode.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_i_samplingMode
 *             Type of sampling
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_DEVICE_NOT_MANUFACTURED The device has not been manufactured
 * @retval RC_INVALID_SAMPLING_MODE The sampling mode is wrong
 */
DEFINE_API	( BDS_SetParametersForDirectMode, int,
				(const int i_i_deviceHandle,
				 const int i_i_samplingMode)
			);

/**
 * This service defines the acquisition parameters for the
 * presence detection mode of image acquisition.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_i_detectionMode
 *             Value of the presence detection mode
 * @param[in]  i_i_fingerNumber
 *             Number of fingers to detect (between FN_MINIMUM and FN_MAXIMUM)
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_DEVICE_NOT_MANUFACTURED The device has not been manufactured
 * @retval RC_INVALID_DETECTION_MODE The detection mode is invalid
 * @retval RC_INVALID_FINGER_NUMBER Number of fingers out of bound
 */
DEFINE_API	( BDS_SetParametersForDetectionMode, int,
				(const int i_i_deviceHandle,
				const int i_i_detectionMode,
				const int i_i_fingerNumber)
			);

/**
 * This service defines the acquisition parameters for the
 * rolled-finger mode of image acquisition.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_i_acquisitionDirection
 *             Acquisition direction
 * @param[in]  i_i_slippage
 *             Slippage tolerance indicator
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_DEVICE_NOT_MANUFACTURED The device has not been manufactured
 * @retval RC_INVALID_DIRECTION The acquisition direction is wrong
 */
DEFINE_API	( BDS_SetParametersForRolledFingerMode, int,
				(const int i_i_deviceHandle,
				const int i_i_acquisitionDirection,
				const int i_i_slippage)
			);

/**
 * This service defines the acquisition parameters for the
 * signature mode of image acquisition.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_DEVICE_NOT_MANUFACTURED The device has not been manufactured
 */
DEFINE_API	( BDS_SetParametersForSignatureMode, int,
				(const int i_i_deviceHandle)
			);

/**
 * This service defines the for each image enhancing
 * process if is actually inserted in the image process.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_p_processParameters
 *             ProcessParameter structure
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_DEVICE_NOT_MANUFACTURED The device has not been manufactured
 * @retval RC_INVALID_PARAMETER A parameter of the structure, at least, has a wrong value
 *                               which don't belong to the BDS_ProcessState enumeration
 */
DEFINE_API	( BDS_SetProcessParameters, int,
				(const int i_i_deviceHandle,
				const BDS_ProcessParameters * const i_p_processParameters)
			);

/**
 * This service returns the actual image of the imaging device.
 * This image is  acquired, normalized and enhanced according
 * the current mode and options.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_l_timeout
 *             Maximal time allocated for the acquisition of the image
 * @param[out] o_p_outputImage
 *             Current image acquired without presence detection
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_GetDirectImage, int,
				(const int i_i_deviceHandle,
				const unsigned long i_l_timeout,
				BDS_Image * const o_p_outputImage)
			);

/**
 * This service returns the actual image of the imaging device.
 * This image is  acquired, normalized and enhanced according
 * the presence detection mode and options. The current results of the presence detection 
 * algorithm are also returned.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_l_timeout
 *             Maximal time allocated for the acquisition of the image
 * @param[out] o_p_outputImage
 *             Current image acquired with presence detection process
 * @param[out] o_p_results
 *             Results of the presence detection algorithm
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_GetDetectedImage, int,
				(const int i_i_deviceHandle,
				const unsigned long i_l_timeout,
				BDS_Image * const o_p_outputImage,
				BDS_DetectionResults * const o_p_results)
			);

/**
 * This service returns the actual image of the imaging device.
 * This image is  acquired, normalized and enhanced according
 * the rolled finger mode and options. The effective result of
 * the algorithmic process is returned
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_l_timeout
 *             Maximal time allocated for the acquisition of the image
 * @param[out] o_p_outputImage
 *             Current image acquired with rolled finger process
 * @param[out] o_i_result
 *             Result of rolled-finger process
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_GetRolledFingerImage, int,
				(const int i_i_deviceHandle,
				const unsigned long i_l_timeout,
				BDS_Image * const o_p_outputImage,
				int * o_i_result)
			);

/**
 * This service returns the actual image of the imaging device.
 * This image is  acquired, normalized and enhanced according
 * the signature mode and options. The effective result of
 * the algorithmic process is returned
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_l_timeout
 *             Maximal time allocated for the acquisition of the image
 * @param[out] o_p_outputImage
 *             Current image acquired wit signeture process
 * @param[out] o_i_result
 *             Result of rolled-finger process
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_GetSignature, int,
				(const int i_i_deviceHandle,
				const unsigned long i_l_timeout,
				BDS_Image * const o_p_outputImage,
				int * o_i_result)
			);

/**
 * This service frees the data memory allocated for the image
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[out] i_p_inputImage
 *             Image to be freed
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_FreeMemoryOfImage, int,
				(BDS_Image * const i_p_inputImage)
			);

	
/**
 * This service defines the callback procedure.
 * The SDK calls this procedure during the image processing flow
 * 
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_p_callback
 *             Address of the callback procedure
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_DefineLiveProcess, int,
				(const int i_i_deviceHandle,
				const BDS_Callback i_p_callback)
			);

/*@}*/
/************************************************************/

/************************************************************/
/** @defgroup groupXCSMiscellaneous Miscellaneous External customer services
*/
/*@{*/

/**
 * This service starts a session calibration.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @retval 0 Success
 * @retval RC_DIRTY_DEVICE The device has been detected dirty
 */
DEFINE_API	( BDS_CalibrateDeviceForExploitation, int,
				(const int i_i_deviceHandle)
			);

/**
 * This service starts the Autotest of the device
 * @param[in]  i_i_deviceIndex
 *             Index of the device (must be set  between 0 and 
 *             the device count returned by BDS_EnumerateUsableBiometricDevices)
 * @param[in]  i_p_testParemters 
 *             Test parameters structure
 * @param[out] o_p_testResults 
 *             Test results structure
 * @retval 0 Success (All tests passed)
 * @retval RC_INVALID_DEVICE_INDEX The index is out of bound
 * @retval RC_DEVICE_ALREADY_OPEN The device is already open
 * @retval RC_AUTOTEST_NOT_PASSED At least, a test has not passed
 */
DEFINE_API	( BDS_Autotest, int,
				(const int i_i_deviceIndex,
				const BDS_TestParameters * const i_p_testParameters,
				BDS_TestResults * const o_p_testResults)
			);

/**
 * This service sets the current state of a LED
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_i_ledIndex
 *             Index of the LED
 * @param[in]  i_i_ledState
 *             New state of the LED
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 * @retval RC_INVALID_LED_INDEX The device does not possess such LED
 * @retval RC_INVALID_LED_STATE The state is wrong
 */
DEFINE_API	( BDS_SetLedState, int,
				(const int i_i_deviceHandle,
				const int i_i_ledIndex,
				const int i_i_ledState)
			);

/**
 * This service verifies the image container 
 *
 * @param[in] i_p_inputImage
 *             Current image to verify
 * @retval 0 Success
 * @retval RC_INVALID_IMAGE_MAGIC Problem with image container magic
 * @retval RC_INVALID_IMAGE_VERSION Problem with image container version
 * @retval RC_INVALID_IMAGE_CHECKSUM Problem with image checksum
 */
DEFINE_API	( BDS_VerifyImage, int,
				(const BDS_Image * const i_p_inputImage)
			);

/**
 * This service returns the actual image of the imaging device.
 * This image is  acquired, normalized and enhanced according
 * the current mode and options.
 *
 * @param[in]  i_p_filename
 *             File name of the image file
 * @param[out] o_p_outputImage
 *             Current image read
 * @retval 0 Success
 * @retval RC_INVALID_IMAGE_FILE Problem with image file
 */
DEFINE_API	( BDS_ReadFileImage, int,
				(const char * const i_p_filename,
				BDS_Image * const o_p_outputImage)
			);

/**
 * This service returns the actual image of the imaging device.
 * This image is  acquired, normalized and enhanced according
 * the current mode and options.
 *
 * @param[in]  i_p_filename
 *             File name of the image file
 * @param[in]  i_p_inputImage
 *             Current image to write
 * @retval 0 Success
 * @retval RC_INVALID_IMAGE_FILE Problem with image file
 */
DEFINE_API	( BDS_WriteFileImage, int,
				(const char * const i_p_filename,
				const BDS_Image * const i_p_inputImage)
			);

/**
 * This service returns the a string describing the meaning of
 * a SDK-specific coding. The code is always an integer one.
 * The coding type defines the dictionnary addressed to provide
 * the information. This allows a smart localization of application
 * software.
 *
 * @param[in]  i_i_informationType
 *             Coding type of the information
 * @param[in]  i_i_informationCode
 *             Code of the information
 * @param[out] o_p_string
 *             Null terminated description string
 * @retval 0 Success
 * @retval RC_INVALID_INFORMATION_TYPE The type of information is unknown
 * @retval RC_INVALID_INFORMATION_CODE The code is out of bound for the specified type
 */
DEFINE_API	( BDS_GetInformationDescription, int,
				(const int i_i_informationType,
				const int i_i_informationCode,
				const char ** o_p_string)
			);

/**
 * This service returns static informations of the SDK which are
 * independant of devices.
 *
 * @param[out] o_p_results
 *             Static SDK-informations (version of SDK, DLLs and interfaces)
 * @retval 0 Success
 */
DEFINE_API	( BDS_GetStaticInformations, int,
				(BDS_SDKStaticInformations * const o_p_results)
			);

/**
 * This service returns the informations of a device which need
 * to communicate with it. The informations are manufacturing ones.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[out] o_p_results
 *             Device informations (Firmware, CPLD)
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_GetDeviceInformations, int,
				(const int i_i_deviceHandle,
				BDS_DeviceInformations * const o_p_results)
			);

/**
 * This service returns the image sizes returned by a specific opened
 * device. These data are dependant of the device itself but also of
 * current SDK configuration set with services of type SetParametersForXXXMode.
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[out] o_p_results
 *             Size informations (For Direct, detected and rooled images)
 * @retval 0 Success
 * @retval RC_INVALID_DEVICE_HANDLE The device handle does not address an open device
 */
DEFINE_API	( BDS_GetImageSizeInformations, int,
				(const int i_i_deviceHandle,
				BDS_ImageSizeInformations * const o_p_results)
			);

/**
 * This service returns image analysis results according input criteria.
 * The analysis type specifies which library (manufacturing or customer)
 * makes the analysis. The image type specifies what depicts the input image.
 * This type must comply with the expected one (according input criteria).
 * The input image is a normalized one.
 *
 * @param[in]  i_i_imageType
 *             Image type (known by application and libraries which processes analysis)
 * @param[in]  i_p_inputImage
 *             Current image to analyse
 * @param[in]  i_p_analysisCriteria 
 *             Analysis criteria structure
 * @param[out] i_p_analysisResults 
 *             Analysis results structure
 * @retval 0 Success
 * @retval RC_INVALID_ANALYSIS_TYPE The type of analysis is unknown
 * @retval RC_INVALID_IMAGE_TYPE The type of image is unknown or incompatible with analysis criteria
 * @retval RC_INVALID_ANALYSIS_CRITERIA The analysis criteria are invalid
 */
DEFINE_API	( BDS_AnalyseImage, int,
				(const int i_i_imageType,
				const BDS_Image * const i_p_inputImage,
				const BDS_AnalysisCriteria * const i_p_analysisCriteria,
				BDS_AnalysisResults * const i_p_analysisResults)
			);

/**
 * This service activate the buzzer at at a given frequency during a specified time.
 * The service returns at the end of the buzz but the image flow is
 * not impacted by this process
 *
 * @param[in]  i_i_deviceHandle
 *             Device handle returned by BDS_OpenBiometricDevice
 * @param[in]  i_s_frequency
 *             Frequency of the buzz in Hz
 * @param[in]  i_s_duration 
 *             Duration in ms of the buzz
 * @retval 0 Success
 */
DEFINE_API	( BDS_SetBuzzer, int,
				(const int i_i_deviceHandle, 
				unsigned short i_s_frequency, 
				unsigned short i_s_duration)
			);

/*@}*/
/************************************************************/

/*@}*/
/************************************************************/

#endif
