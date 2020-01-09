/************************************************************/
/**
 * @file BDS_Common.h
 * @brief Common definitions for Biometric Device Services
 *
 * Copyright (c) SAGEM Défense Sécurité
 *
 * - PROJET      : SLAP
 * - MODULE      : BDS Interfaces
 * - DATE        : August,21 2006
 *
 */
/************************************************************/

#if !defined(BDS_Common)
#define BDS_Common

#define BDS_TRACE
//#define DEBUGVISUAL

/*****************************************************************************/
#ifdef DEBUGVISUAL
	#define printDebug printOutput
	int printOutput(const char *format, ...);
#else
	#define printDebug printf
#endif

#if defined(BDS_TRACE)
	#define Buzzer_TRACE
	/* Modules flags */
//	#define SDKServices_TRACE
//	#define ICMServices_TRACE
//	#define SDKCallback_TRACE
//	#define SDKExtraction_TRACE
//	#define SDKAcquisition_TRACE
//	#define SDKCommand_TRACE
//	#define SDKFifo_TRACE
//	#define ComUSB_TRACE
// 	#define Memory_TRACE
// 	#define Mutex_TRACE
	/* Functionnal flags */
	#define Errors_TRACE 
//	#define DetectedFrame_TRACE
//	#define DetectedSYNC_TRACE
//	#define OutOfModeImage_TRACE
//	#define WriteStatistics_TRACE	
//	#define Autotest_TRACE 
//	#define SDKServer_TRACE
	#define ESD_TRACE
//	#define Temporary_TRACE
#endif

#define WindowsXP

/************************************************************/
/** @defgroup groupCommonDef Common definitions
*/
/*@{*/

/** @brief Version of the BDS */
#define BDS_VERSION	1

/** @brief Maximum number of devices on the same computer */
#define MAX_USABLE_DEVICES 8

/** @brief Maximum number of records for logging process */
#define MAX_LOG_RECORDS 100

/** @brief Maximum length of filename */
#define MAX_FILENAME_LENGTH 1024

/** @brief Return codes for services of all SDK interfaces */
typedef enum {	
	RC_OK = 0x0000,					/**< The service has been correctly executed */	

	RC_INVALID_DEVICE_HANDLE = 0xF000,/**< The handle is not the one of an opened device */	
	RC_INVALID_DEVICE_INDEX,		/**< The device index is out of bound */	
	RC_UNKNOWN_DEVICE,				/**< The device cannot be opened */	
	RC_NO_DEVICE_AVAILABLE,			/**< No usable biometric device is available*/	
	RC_IMAGE_CANNOT_BE_PROCESSED,	/**< Image cannot be processed */	
	RC_INVALID_DETECTION_MODE,		/**< Mode of presence detection is unknown */	
	RC_INVALID_FINGER_NUMBER,		/**< Number of fingers out of bound */
	RC_INVALID_DIRECTION,			/**< Direction of acquisition is unknown */	

	RC_INVALID_LIVE_ACTION,			/**< Invalid action over live process */	
	RC_INVALID_PROCESS_STATE,		/**< Invalid process state */
	RC_DIRTY_DEVICE,				/**< The device has been detected dirty */	
	RC_INVALID_SESSION_HANDLE,		/**< Session for image detection or for rolled-finger is not opened */	
	RC_INVALID_ACQUISITION_MODE,	/**< Mode of acquisition is unknown */	
	RC_INVALID_SAMPLING_MODE,		/**< The sampling mode is unknown */	
	RC_INVALID_LED_STATE,			/**< LED state unknown */ 
	RC_INVALID_LED_INDEX,			/**< LED index out of bounds */ 

	RC_AUTOTEST_NOT_PASSED,			/**< Autotest not passed (at least a test failed) */
	RC_DEVICE_AUTHENTICATION_FAILED,		/**< The device authentication does not succeed */
	RC_SOFTWARE_AUTHENTICATION_FAILED,		/**< The software authentication does not succeed */
	RC_SOFTWARE_CRYPTODATA_UPDATE_FAILED,	/**< The update of data does not succeed */
	RC_INVALID_DEVICE_RESPONSE,		/**< Invalid low-level command response */
	RC_INVALID_SLIPPAGE,			/**< Slippage value must be a percent 0 <= x <= 100 */
	RC_PRESENCE_DETECTION_PROBLEM,  /**< Problem with presence detection algorithm */
	RC_ROLLED_FINGER_PROBLEM,		/**< Problem with rolled finger algorithm */

	RC_END_ON_TIMEOUT,				/**< End of accquisition on timeout*/
	RC_INVALID_DEVICE_MODE,			/**< Mode unknown */
	RC_INVALID_TIMEOUT,				/**< Invalid timeout (not between Min and max) */
	RC_DEVICE_NOT_MANUFACTURED,		/**< Device has not be completly manufactured */
	RC_INVALID_IMAGE_FILE,			/**< IO error on image file */
	RC_INVALID_IMAGE_MAGIC,			/**< Error on image magic */
	RC_INVALID_IMAGE_VERSION,		/**< Error on image version */
	RC_INVALID_IMAGE_CHECKSUM,		/**< Error on image checksum */

	RC_DEVICE_ALREADY_OPEN,			/**< The device is already open */
	RC_INVALID_INFORMATION_TYPE,	/**< The type of information has no dictionnary */
	RC_INVALID_INFORMATION_CODE,	/**< The code is out of bound for the specified type */
	RC_INVALID_ANALYSIS_TYPE,		/**< The type of analysis is unknown */
	RC_INVALID_IMAGE_TYPE,			/**< The type of image is unknown or incompatible with analysis criteria */
	RC_INVALID_ANALYSIS_CRITERIA,	/**< The analysis criteria are invalid */
	RC_DEVICE_NOT_ENUMERATED,		/**< The device has not been enumerated */
	RC_UNCALIBRABLE_DEVICE,			/**< The device has been detected dirty and no reference image is available*/	

	RC_INVALID_ACQUISITION_AREA,	/**< The acquisition area is incorrect */	
	RC_SIGNATURE_PROBLEM,	        /**< Problem in the signature process */	
	/* Errors of BDS_ResolveInterface */
	ERROR_DLL_NOT_FUNCTIONNAL	= 0xFF00,
	ERROR_DLL_TYPE				= 0xFF01,
	ERROR_LOADLIBRARY			= 0xFF02,
	ERROR_GETPROCADDRESS		= 0xFF03,
	ERROR_DLL_VERSION			= 0xFF04,
	ERROR_UNAVAILABLE_SERVICE	= 0xFF05,
} BDS_ReturnCodes;

/** @brief Internal errors */
typedef enum {	
	IE_OK = 0x0000,					/**< No error */	
	IE_MEMORY_ERROR_00 = 0xE000,	/**< Memory error */
	IE_MEMORY_ERROR_10,				/**< Memory error */
	IE_MEMORY_ERROR_11,				/**< Memory error */
	IE_MEMORY_ERROR_20,				/**< Memory error */
	IE_MEMORY_ERROR_21,				/**< Memory error */
	IE_MEMORY_ERROR_22,				/**< Memory error */
	IE_MEMORY_ERROR_30,				/**< Memory error */
	IE_MEMORY_ERROR_31,				/**< Memory error */
	IE_BROKEN_DEVICE,				/**< Device is broken (disconnection) */
	IE_ICS_ERROR_NORMALIZE,			/**< ICS error */
} BDS_InternalErrors;

/** @brief Exit codes of Tasks */
typedef enum {	
	EC_OK = 0x0000,					/**< No error */	
	EC_MEMORY_ERROR = 0xD000,	/**< Memory error */
	EC_BROKEN_DEVICE,				/**< USB device broken */
} BDS_ExitCodes;

/** @brief Availables dictionnaries information description */
typedef enum {	
	DI_MNEMONICS_RETURN_CODES,		/**< Dictionnary of SDK mnemonics of return codes */	
	DI_ENGLISH_RETURN_CODES,		/**< Dictionnary of english return codes */	
	DI_FRENCH_RETURN_CODES,			/**< Dictionnary of french return codes */	
	DI_MAXIMUM,						/**< Number of dictionnaries */	
} BDS_DictionnaryTypes;

/** @brief Process applied to images */
typedef enum {	
	PR_THUMBNAIL,					/**< Decimation for thumbnailing */	
	PR_DECIMATION,					/**< Standard decimation */	
	PR_NORMALIZATION,				/**< Normalization */	
	PR_PRESENCE_DETECTION,			/**< Presence detection */	
	PR_ROLLED_FINGER,				/**< Rolled-finger build */	
	PR_BACKGROUND_CANCELLATION,		/**< Background cancellation */	
	PR_FLARE_CANCELLATION,			/**< Flare cancellation */	
	PR_SIGNATURE,					/**< Signature build */
} BDS_ImageProcesses;

/** @brief Sampling modes for raw image acquisition */
typedef enum {	
	SM_FULL = 1,					/**< Full image */	
	SM_HALF = 2,					/**< Half image */	
	SM_THIRD = 3,					/**< Third image */	
	SM_QUARTER = 4,					/**< Quarter image */	
	SM_TINY = 8,					/**< Tiny image */	
	SM_LILLIPUTIAN = 16,			/**< Very tiny image */	
	SM_MINIMUM = 0,					/**< Previous invalid value */	
	SM_MAXIMUM = 17,				/**< First invalid value */	
} BDS_SamplingModes;

/** @brief Detection status values */
typedef enum {	
	DS_STOP,						/**< Presence detection has taken decision */
	DS_WAIT,						/**< No finger has been detected */ 
	DS_CONTINUE,					/**< Fingers have been detected but more images are needed for decision */	
	DS_REMOVE_FINGER,				/**< Fingers are detected on the sensor but are not expected */ 
	DS_LATENT,						/**< Image containts latent - the sensor must be cleaned */ 
	DS_INIT,						/**< Process has just been initialized */ 
	DS_CLOSE						/**< Process has been closed */ 
} BDS_DetectionStatus;

/** @brief State of the rolled-finger process */
typedef enum {	
	RF_IMAGE_NEEDED_FOR_TERMINATION,/**< The resulting image is not yet usable */	
	RF_IMAGE_NEEDED_FOR_QUALITY,	/**< The resulting image is usable, but its quality can be enhanced */	
	RF_NO_MORE_IMAGE_NEEDED,		/**< The resulting image is usable and cannot be enhanced */	
} BDS_RolledFingerResult;

/** @brief Direction of acquisition for rolled-finger process */
typedef enum {	
	DA_LEFT2RIGHT,					/**< Acquisition from left to right */	
	DA_RIGHT2LEFT,					/**< Acquisition from right to left */	
	DA_UNKNOWN,						/**< Unknown direction */	
	DA_MAXIMUM,						/**< First invalid value */	
} BDS_AcquisitionDirection;

/** @brief Detection modes for presence detection algorithm */
typedef enum {	
	DM_MASK = 0x07,					/**< Mask of significant bits */	
	DM_SPEED = 0x00,				/**< Detection must optimize speed process */	
	DM_VERIFICATION = DM_SPEED,		/**< Speed is used for verification */	
	DM_QUALITY = 0x01,				/**< Detection must optimize quality */	
	DM_ENROLL = DM_QUALITY,			/**< Quality is used for enrollment*/	
	DM_LATENT = 0x02,				/**< Process for detection of latent images */	
	DM_REMOVE_FINGER = 0x04,		/**< Verify that fingers are removed on first image */	
} BDS_DetectionModes;

/** @brief Action to be done by SDK after callback */
typedef enum {	
	AA_NOTHING = 0xA0,				/**< Do nothing */	
	AA_ANIMATE_LED = 0xA1,			/**< Animate the Leds */	
} BDS_ActionsAfter;

/** @brief Finger number for presence detection algorithm */
typedef enum {	
	FN_MINIMUM,						/**< First invalid low value */	
	FN_1_FINGER,					/**< Detection of one finger */	
	FN_2_FINGERS,					/**< Detection of two fingers */	
	FN_3_FINGERS,					/**< Detection of three fingers */	
	FN_4_FINGERS,					/**< Detection of four fingers */	
	FN_MAXIMUM,						/**< First invalid high value */	
} BDS_FingerNumbers;

/** @brief Image process state*/
typedef enum {	
	IP_MINIMUM,						/**< First invalid low value */	
	IP_EXCLUDED,					/**< The process is not active in the global image flow */	
	IP_INSERTED,					/**< The process is inserted in the global image flow */	
	IP_MAXIMUM,						/**< First invalid value */	
} BDS_ProcessState;

/** @brief States of a LED */
typedef enum { 	
	LED_OFF					= 0x00,		/**< LED off */	
	LED_GREEN_CONTINUOUS	= 0x05,		/**< LED Green continuously */	
	LED_RED_CONTINUOUS		= 0x01,		/**< LED Red continuously */	
	LED_ORANGE_CONTINUOUS	= 0x09,		/**< LED Orange continuously*/	
	LED_GREEN_BLINK			= 0x06,		/**< LED Green and blinking */	
	LED_RED_BLINK			= 0x02,		/**< LED Red and blinking */	
	LED_ORANGE_BLINK		= 0x0A,		/**< LED Orange and blinking */	
} BDS_LedState;

/** @brief Index of LEDs for the Slap device */
typedef enum { 	
	LED_Min=0,							/**<  */	
	LED_Max=14,							/**<  */	
	LED_SLAPStatus=13,					/**< LED for SLAP status */	
	LED_LeftHandIcon=4,					/**< LED for left hand icon  */	
	LED_RightHandIcon=12,				/**< LED for right hand icon   */	
	LED_LeftThumbStatus=5,				/**< LED for status of left thumb */	
	LED_RightThumbStatus=6,				/**< LED for status of right thumb */	
	LED_LeftFinger4Status=0,			/**< LED for status of left little finger */	
	LED_LeftFinger3Status=1,			/**< LED for status of left ring finger */	
	LED_LeftFinger2Status=2,			/**< LED for status of left middle finger */	
	LED_LeftFinger1Status=3,			/**< LED for status of left forefinger */	
	LED_RightFinger1Status=11,			/**< LED for status of right forefinger */	
	LED_RightFinger2Status=10,			/**< LED for status of right middle finger */	
	LED_RightFinger3Status=9,			/**< LED for status of right ring finger */	
	LED_RightFinger4Status=8,			/**< LED for status of right little finger*/	
	LED_RolledFingerAreaIcon=7,		/**< LED for area dedicated to rolled finger process */	
} BDS_SlapLeds;

/** @brief Type of biometric devices */
typedef enum { 	
	BD_VIRTUAL,						/**< Virtual */	
	BD_SLAP,						/**< SLAP */
} BDS_DeviceType;

/** @brief State of biometric device */
typedef enum { 	
	BD_CLOSED,						/**< Enumerated but closed */	
	BD_OPEN,						/**< Enumerated and open */
	BD_OPEN_ADMIN,					/**< Enumerated and open for administration */
} BDS_DeviceState;

/** @brief Mode of biometric device */
typedef enum {	
	PM_RAW,							/**< Compete raw image */	
	PM_FULL,						/**< Full image */	
	PM_HALF,						/**< Half image */	
	PM_TINY,						/**< Tiny image */	
	PM_MAXIMUM,						/**< First invalid value */	
} BDS_DeviceModes;

#define TINY_HARDWARE_DECIMATION_RATIO 3
/** @brief Strategy of Fifo insertion */
typedef enum { 	
	BD_ERASE_OLDER,					/**< Erase older image */	
	BD_ERASE_NEWER,					/**< Erase newer image */
} BDS_InsertionStrategy;

/** @brief Strategy of Fifo insertion */
typedef enum { 	
	SI_SLAP = 0x80,					/**< Slap */	
	SI_MSO1000_STD = 0x81,			/**< MSO1000 with full Slap compatibility */
	SI_SLAP_TOOL = 0xC3,			/**< Special slap with live mode witout normalization */
} BDS_SensorId;

/** @brief Containers of device upgraded for firmware 1.0.5*/
typedef enum { 	
	CONTAINER_SYSTEM_INFORMATION = 0,			/**< RAM-based device system information */	
	CONTAINER_MANUFACTURING_INFORMATION = 1,	/**< Manufacturing information */	
	CONTAINER_CALIBRATION_MANUFACTURING = 5,	/**< Distortion manufacturing parameters */	
	CONTAINER_SENSOR_PARAMETERS = 2,			/**< Sensor parameters */	
	CONTAINER_MODE_PARAMETERS = 3 ,				/**< Mode parameters */
	CONTAINER_LICENCE_DATA = 4 ,				/**< Licence data */
	CONTAINER_EEPROM_CAMERA = 6,                /**< Serial-Number camera */
} BDS_Containers;

/** @brief Firmware autotest bits */
typedef enum {	
	FA_ERROR_EEPROM,				/**< Eeprom processor */	
	FA_ERROR_EEPROM_CAMERA,			/**< Eeprom camera */	
	FA_ERROR_EVENT_COUNTER,			/**< Hardware counter */	
	FA_ERROR_ERROR_CPLD				/**< CPLD */	
} BDS_FirmwareAutotests;

/** @brief Image Test Patterns */
typedef enum {
	IA_MIRE_ANALYSE = 1,			/**< Analysis and calibration */	
	IA_MIRE_BLANCHE,				/**< White pattern */	
	IA_MIRE_GEO_HORI,				/**< Horizontal geometry */	
	IA_MIRE_GEO_VERT,				/**< Vertical geometry */	
} BDS_MireImageType;

/** @brief Raw analysis results */
typedef struct {

	double m_d_grandissementX;
	double m_d_grandissementY;
	double m_d_decentrementX;
	double m_d_decentrementY;
	double m_d_angle_rotation;
	double m_d_Grandissement_Y_Gauche;
	double m_d_Grandissement_Y_Droit;
	double m_d_Grandissement_X;
	double m_d_Distorsion_Y;
	double m_d_Grandissement_Y_moy;
	double m_d_Distorsion_angulaire_Bas;
	double m_d_Distorsion_angulaire_Haut;
	double m_d_Resolution_Y_Droit;
	double m_d_Resolution_Y_Gauche;
	double m_d_Resolution_Y_Moyen;
	double m_d_Resolution_X;
	double m_d_Indicateur;

	
	int   m_i_moyenne_noir;
	int   m_i_maximum_noir;
	float m_f_variance_noir;
	int   m_i_ecart_max_noirs;

	int   m_i_moyenne_blanc;
	int   m_i_maximum_blanc;
	float m_f_variance_blanc;
	float m_f_saturation_blanc;
	int   m_i_ecart_max_blanc;

	float m_f_white_ref;
	float m_f_black_ref;

	float m_f_contraste_1h;
	float m_f_contraste_1v;
	float m_f_contraste_2h;
	float m_f_contraste_2v;
	float m_f_contraste_3h;
	float m_f_contraste_3v;
	float m_f_contraste_4h;
	float m_f_contraste_4v;
	float m_f_contraste_5h;
	float m_f_contraste_5v;
	float m_f_contraste_6h;
	float m_f_contraste_6v;
	float m_f_contraste_7h;
	float m_f_contraste_7v;
	float m_f_contraste_8h;
	float m_f_contraste_8v;
	float m_f_contraste_9h;
	float m_f_contraste_9v;
	float m_f_contraste_10h;
	float m_f_contraste_10v;

	float m_f_contraste_6h_hg;
	float m_f_contraste_6v_hg;
	float m_f_contraste_6h_hd;
	float m_f_contraste_6v_hd;
	float m_f_contraste_6h_bg;
	float m_f_contraste_6v_bg;
	float m_f_contraste_6h_bd;
	float m_f_contraste_6v_bd;

	float m_f_contraste_8h_h;
	float m_f_contraste_8v_h;
	float m_f_contraste_8h_b;
	float m_f_contraste_8v_b;
	float m_f_contraste_8h_d;
	float m_f_contraste_8v_d;
	float m_f_contraste_8h_g;
	float m_f_contraste_8v_g;

	float m_f_offset_colonnes_noir;
	float m_f_offset_colonnes_blanc;
	
	int m_i_CroixHautGaucheX;
	int m_i_CroixHautGaucheY;
	int m_i_CroixHautDroitX;
	int m_i_CroixHautDroitY;
	int m_i_CroixBasGaucheX;	
	int m_i_CroixBasGaucheY;

} BDS_RawAnalysisResults;

/** @brief Structure for presence detection results */
typedef struct {
	int	m_detectionStatus;			/**< Global detection status */
	int	m_finger1;					/**< Detection status of finger 1 */
	int	m_finger2;					/**< Detection status of finger 2 */
	int	m_finger3;					/**< Detection status of finger 3 */
	int	m_finger4;					/**< Detection status of finger 4 */
} BDS_DetectionResults;

/** @brief Blind structure for SDK-transparent data */
typedef struct {
	unsigned long	m_length;		/**< Byte length of the data area */
	void *			m_address;		/**< Address of the data area */
} BDS_BlindData;

/** @brief Quadrangle structure */
typedef struct {
	unsigned short	m_startingColumn;	/**< 0-based position of first column */
	unsigned short	m_startingLine;		/**< 0-based position of first line */
	unsigned short	m_width;			/**< Number of columns */
	unsigned short	m_height;			/**< Number of lines */
} BDS_Quadrangle;

/** @brief Image size structure */
typedef struct {
	unsigned int	m_width;			/**< Number of columns */
	unsigned int	m_height;			/**< Number of lines */
} BDS_ImageSize;

#define IMG_MAGIC 0xBEEFBABE
#define IMG_VERSION 1
#define IMG_RFU_LENGTH 28

/** @brief Image mode */
typedef enum { 	
	IMG_WITH_CHECKSUM,						/**< Image with checksum*/	
	IMG_WITHOUT_CHECKSUM,					/**< Image without checksum */
} BDS_ImageMode;

/** @brief Image structure */
typedef struct {
	unsigned long	m_magic;				/**< Specific marker for images */
	unsigned int	m_version;				/**< Version of this envelope structure */
	unsigned int	m_width;				/**< Number of columns */
	unsigned int	m_height;				/**< Number of lines */
	unsigned long	m_flags;				/**< Flags for applied process */
	void *			m_image;				/**< Address of image data area */
	unsigned long	m_count;				/**< Serial counter */
	unsigned long	m_checksum;				/**< Checksum over image data area*/
	char			m_rfu[IMG_RFU_LENGTH];	/**< Reserved for futur use */
} BDS_Image;

/** @brief Low-level descriptor of a biometric device */
typedef struct {
	char m_manufacturingInfos[256];		/**< Manufacturing string identifying the product + device */
	char m_deviceType[256];				/**< Device type = Product code theorically based on a 9-digit code*/
	char m_deviceSerial[256];			/**< Serial number = Theorically based on a 14-digit */
} BDS_DeviceDescriptor;

/** @brief SDK static informations */
typedef struct {
	int m_SDKVersion;				/**< Version of SDK */
	int m_DllUSB;					/**< Version of USB Dll */
	int m_DllCustomer;				/**< Version of Customer Dll */
	int m_DllManufacturing;			/**< Version of Manufacturing Dll */
	int m_InterfaceDCS;				/**< Version of DCS interface */
	int m_InterfaceXCS;				/**< Version of XCS interface */
	int m_InterfaceXRS;				/**< Version of XRS interface */
	int m_InterfaceICS;				/**< Version of ICS interface */
	int m_InterfaceIMS;				/**< Version of IMS interface */
} BDS_SDKStaticInformations;

/** @brief Manufacturing device informations */
typedef struct {
	unsigned char	m_versionFirmwareMajor;		/**< Version of firmware major */ 
	unsigned char	m_versionFirmwareMinor;		/**< Version of firmware minor */ 
	unsigned char	m_versionFirmwareRelease;	/**< Version of firmware release */ 
	unsigned char	m_CPLDVersion;				/**< Version of CPLD software */
	unsigned long	m_totalTime;				/**< Total time of operation */
	unsigned long	m_startCount;				/**< Total count of use */
} BDS_DeviceInformations;

/** @brief Firmware version */
typedef struct {
	unsigned char	m_versionFirmwareMajor;		/**< Version of firmware major */ 
	unsigned char	m_versionFirmwareMinor;		/**< Version of firmware minor */ 
	unsigned char	m_versionFirmwareRelease;	/**< Version of firmware release */ 
} BDS_FirmwareVersion;

/** @brief Current image size of a device */
typedef struct {
	BDS_ImageSize	m_DirectImageSize;			/**< Size of image got with GetDirectImage */
	BDS_ImageSize	m_DetectedImageSize;		/**< Size of image got with GetDetectedImage */
	BDS_ImageSize	m_RolledFingerImageSize;	/**< Size of image got with GetRolledFingerImage */
	BDS_ImageSize	m_SignatureImageSize;	    /**< Size of image got with GetSignatureImage */
} BDS_ImageSizeInformations;

/** @brief Structure for image process inclusion parameters */
typedef struct {
	BDS_ProcessState	m_backgroundCancellation;	/**< Background cancellation */
	BDS_ProcessState	m_flareCancellation;		/**< Flare cancellation */
	int					m_acquisitionAreaType;		/**< Type of acquisition area */
} BDS_ProcessParameters;

/** @brief Structure for container of data mode parameters */
typedef struct {
	unsigned char	m_sensorId;
	unsigned char	m_version;
	unsigned short	m_CalibrationContainerLength;
	BDS_Quadrangle	m_FullModeDeviceQuadrangle;
	BDS_Quadrangle	m_FullModeImageQuadrangle;
	BDS_Quadrangle	m_HalfModeDeviceQuadrangle;
	BDS_Quadrangle	m_HalfModeImageQuadrangle;
	BDS_Quadrangle	m_TinyModeDeviceQuadrangle;
	BDS_Quadrangle	m_TinyModeImageQuadrangle;
} BDS_DataModeContainer;
/** @brief Structure for system information container */
typedef struct {
	unsigned char	m_versionMajor;
	unsigned char	m_versionMinor;
	unsigned char	m_versionRelease;
	unsigned char	m_sensorId;
	unsigned short	m_sensorXmax;
	unsigned short	m_sensorYmax;
	unsigned char	m_versionCPLD;
} BDS_SystemInformationsContainer;

/** @brief Parameters of a virtual device */
typedef struct {
	int m_serial;	/**< Serial number */
} BDS_VirtualDeviceParameters;

/** @brief Parameters of a SLAP device */
typedef struct {
	int m_serial;	/**< Serial number */
} BDS_SlapDeviceParameters;

/** @brief Event inducing record of statistics */
typedef enum { 	
	RE_USER_CALL			= 0x00000001, /**< User call of SDK service */	
	RE_EXTRACTION_LOOP		= 0x00000002, /**< Begin of loop of extraction thread */
	RE_RECEIVE_CHUNK		= 0x00000004, /**< Receive chunk from the com library */
} BDS_RecordEvent;

/** @brief Reporting informations of a device */
#define STAT_MAGIC 0xBEEFBABE
typedef struct {
	unsigned long m_magic;					/**< Indicator of structure */
	unsigned long m_recordEvent;			/**< Event inducing recording of statistics */
	unsigned long m_currentTime;			/**< Current time in ms since Dll load */
	unsigned long m_usbDetectedFrameCount;	/**< Count of valid frames inserted in Fifo */
	unsigned long m_usbLostFrameCount;		/**< Count of lost frames based on firmware stamping */
	unsigned long m_usbRawByteCount;		/**< Count of bytes provided by the USB driver */
	unsigned long m_usbEffectiveByteCount;	/**< Count of bytes used for valid frames (data + synchronisation) */
	unsigned long m_usbChunkCount;			/**< Count of chunks provided by the USB driver*/
	unsigned long m_usbChunkMinimumSize;	/**< Size of the shorter chunk */
	unsigned long m_usbChunkMaximumSize;	/**< Size of the longer chunk */
	unsigned long m_fifoCurrentImageCount;	/**< Count of images currently in Fifo */
	unsigned long m_fifoLostImageCount;		/**< Count of images erased before extraction */
	unsigned long m_fifoDroppedImageCount;	/**< Count of images erased during purge of Fifo */
	unsigned long m_fifoSize;				/**< Size of Fifo */
	unsigned long m_frameExtractionCount;	/**< Count of frames extracted from Fifo */
	unsigned long m_frameOutOfModeCount;	/**< Count of frames detected out of mode */
	unsigned long m_frameLiveModeCount;		/**< Count of frames processed in live mode */
	unsigned long m_frameDirectModeCount;	/**< Count of frames processed in direct mode */
	unsigned long m_frameDetectedModeCount;	/**< Count of frames processed in detected mode */
	unsigned long m_frameRolledModeCount;	/**< Count of frames processed in rolled mode */
	unsigned long m_frameSignatureModeCount;/**< Count of frames processed in signature mode */
	unsigned long m_imageLiveModeCount;		/**< Count of images provided in live mode (ie calls to user callback) */
	unsigned long m_imageDirectModeCount;	/**< Count of images provided in direct mode */
	unsigned long m_imageDetectedModeCount;	/**< Count of images provided in detected mode */
	unsigned long m_imageRolledModeCount;	/**< Count of images provided in rolled mode */
	unsigned long m_imageSignatureModeCount;/**< Count of images provided in signature mode */
	unsigned long m_callbackTime;			/**< Elapsed time in user callback */
	unsigned long m_algoCountLiveMode;		/**< Count of algorithm calls in live mode*/
	unsigned long m_algoCountDirectMode;	/**< Count of algorithm calls in direct mode */
	unsigned long m_algoCountDetectedMode;	/**< Count of algorithm calls in detected mode */
	unsigned long m_algoCountRolledMode;	/**< Count of algorithm calls in rolled mode */
	unsigned long m_algoCountSignatureMode;	/**< Count of algorithm calls in signature mode */
	unsigned long m_algoTimeLiveMode;		/**< Elapsed time in algorithms in live mode*/
	unsigned long m_algoTimeDirectMode;		/**< Elapsed time in algorithms in direct mode */
	unsigned long m_algoTimeDetectedMode;	/**< Elapsed time in algorithms in detected mode */
	unsigned long m_algoTimeRolledMode;		/**< Elapsed time in algorithms in rolled mode */
	unsigned long m_algoTimeSignatureMode;	/**< Elapsed time in algorithms in signature mode */
	unsigned long m_memoryAllocationCount;	/**< Count of malloc */
	unsigned long m_memoryReleaseCount;		/**< Count of free */
	unsigned long m_memoryErrors;			/**< Count of errors */
	unsigned long m_spare[24];              /**< For future extentions */
} BDS_DeviceStatistics;

/** @brief Logged records */
typedef struct {
	char					m_logFilename[MAX_FILENAME_LENGTH];	/* Current index for insertion */	
	unsigned int			m_currentIndex;					/* Current index for insertion */	
	unsigned long			m_eventMask;					/* Mask for selecting records to log in file */	
	BDS_DeviceStatistics	m_statRecord[MAX_LOG_RECORDS];	/* Array of statistics records */	
} BDS_LogData;

/** @brief Test parameters */
typedef struct {
	int m_testGlobalTime;			/**< Global time of the whole test (in ms) */
	int m_imageProcessTime;			/**< Processing time by application over a single image */
	int m_samplingMode;				/**< Decimation factor for test images */
} BDS_TestParameters;

/** @brief Test results */
typedef struct {
	int m_imageCount;			/**< Number of images processed */
	int m_lostCount;			/**< Number of lost images */
	int m_lostSequenceCount;	/**< Current count of sequence of lost images */
} BDS_TestResults;

/** @brief IQS measures over an image */
typedef struct {
	int m_iqsMeasures[32];			/**< Results of IQS measurement */
} BDS_BDS_DeviceIQSMeasures;
/** @brief Structure for manufacturing calibration parameters*/
typedef BDS_BlindData BDS_Handle27;

/** @brief Structure for device session calibration parameters*/
typedef BDS_BlindData BDS_SessionCalibrationParameters;

/** @brief Structure for manufacturing calibration parameters*/
typedef BDS_BlindData BDS_ManufacturingCalibrationParameters;

/** @brief Structure for IQS measures */
typedef BDS_BlindData BDS_DeviceIQSMeasures;

/** @brief Structure for image analysis criteria*/
typedef BDS_BlindData BDS_AnalysisCriteria;

/** @brief Structure for image analysis reults */
typedef BDS_BlindData BDS_AnalysisResults;

/** @brief Prototype for callback function */
typedef int (*BDS_Callback) (	const int i_i_deviceHandle,
								BDS_Image * const i_p_currentImage,
								const unsigned char * const i_p_inputData,
								unsigned char * const o_p_outputData,
								void * const i_p_userData);
/** @brief Prototype for acquisition function */
typedef int (*BDS_AcquisitionFunction) ( void * const i_device,
										 unsigned char * i_p_dataBuffer,
										 unsigned long i_l_dataLength);

/** @brief High-level descriptor of a biometric device */
typedef struct {
	BDS_DeviceDescriptor	m_descriptor;	/**< SDK device descriptor */
	int						m_index;		/**< Device index */
	int						m_handle;		/**< Device handle */
	int						m_state;		/**< Current state of the device */
	int						m_error;		/**< Current internal error */
	void				   *m_startReception;	/**< Event for Reception thread start */
	void				   *m_stopReception;	/**< Event for Reception thread stop */
	void				   *m_endReception; 	/**< Event for Reception thread end */
	void				   *m_purgeReception; 	/**< Event for Reception thread purge */
	void				   *m_startExtraction;	/**< Event for Extraction thread start */
	void				   *m_stopExtraction;	/**< Event for Extraction thread stop */
	void				   *m_endExtraction; 	/**< Event for Extraction thread end */
	BDS_Callback			m_callback;		/**< Callback user function */
	BDS_AcquisitionFunction	m_acquisition;	/**< Callback acquisition function */
	void                   *m_process;      /**< Address of process data */
} BDS_Device;

/*****************************************************************************/
#define BDS_RANDOM_LENGTH 8
#define BDS_LICENSE_INFO_LENGTH 512
#define BDS_DEFAULT_SERVER_PORT 1959

typedef enum {	
	RSS_OK = 0,
	RSS_DEVICE_NOT_OPEN = 1,	
} BDS_ServerResponse;
typedef enum {	
	RQS_LICENSE,
	RQS_MAXIMUM,	
} BDS_ServerRequests;
typedef struct {
	unsigned char m_clientRandom[BDS_RANDOM_LENGTH];
} BDS_CommandLicenseInformations;
typedef struct {
	unsigned int m_status;
	unsigned char m_serverRandom[BDS_RANDOM_LENGTH];
	unsigned char m_cipheredLicenseInformations[BDS_LICENSE_INFO_LENGTH];
} BDS_ResponseLicenseInformations;

/*****************************************************************************/
typedef int (*interfaceFunction) (void);

typedef enum {
	DLL_SDKSERVICES,
	DLL_CUSTOMER,
	DLL_MANUFACTURING,
	DLL_COMMUNICATION,
} BDS_DllType;

/*** Interface of the common code for loading dynamic libraries **************/
int BDS_resolveInterface (char * i_pc_fullpath, int i_i_dllType, 
						  interfaceFunction ** o_p_interfaceTable,
						  int * o_i_interfaceTable_count,
						  int * o_i_dllVersion);
/*****************************************************************************/

#endif

/*** Macros for standardization of API use ***********************************/
#undef DEFINE_API
#undef DLL_API
#undef API_CALL

#ifdef _DLL_SERVICES
	#define DEFINE_API(Name, ReturnType, Signature) extern __declspec( dllexport ) ReturnType Name Signature
#else
	#define DEFINE_API(Name, ReturnType, Signature) typedef ReturnType (*pf_##Name)Signature
#endif

#define DLL_API extern __declspec( dllexport )
#define API_CALL(Interface, Name, Parameters) ((pf_##Name) Interface[_##Name])Parameters

/*** Prototype of mandatory Dll procedure for dynamic link********************/
DEFINE_API	( getInterface,	int,  
				(int * o_dllType, 
				int * o_dllVersion,
				interfaceFunction ** o_interfaceTable_address,
				int * o_interfaceTable_count)
			);

/*@}*/
/************************************************************/

