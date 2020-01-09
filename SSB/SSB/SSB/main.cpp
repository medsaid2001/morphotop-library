#include "BDS_Common.h"
#include "BDS_OS.h"
#include "BDS_Interface_XCS.h";
#include <iostream>

extern "C" __declspec(dllexport) int LoadLib(TCHAR *file, void ** o_pp_handle)
{
	HINSTANCE h_lib = LoadLibrary(file);
	*o_pp_handle = NULL;
	if(h_lib == NULL)
		return ERROR_LOADLIBRARY;
	*o_pp_handle = h_lib;
	return 0;
}
extern "C" __declspec(dllexport) int GProcAddress(void * i_p_handle,char * i_pc_method, void ** o_pp_procaddress) {
	void * l_p_proc;
	l_p_proc = GetProcAddress((HINSTANCE)i_p_handle,i_pc_method);
	if(l_p_proc == NULL)
		return ERROR_GETPROCADDRESS;
	*o_pp_procaddress = l_p_proc;
	return 0;
}
extern "C" __declspec(dllexport) int resolveInterface (TCHAR * i_pc_fullpath, int i_i_dllType, 
						  interfaceFunction ** o_p_interfaceTable,
						  int * o_i_interfaceTable_count,
						  int * o_i_dllVersion) {
	void * l_p_handle = 0;
	int l_i_result;
	int l_i_dllType;
	void * l_pf_getInterface;
	l_i_result = LoadLib(i_pc_fullpath,&l_p_handle);
	if(l_i_result == 0) {
		l_i_result = GProcAddress(l_p_handle,"getInterface", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_getInterface)l_pf_getInterface)
						 (&l_i_dllType,
						  o_i_dllVersion,
						  o_p_interfaceTable,
						  o_i_interfaceTable_count);
		if (i_i_dllType != l_i_dllType) {
				return ERROR_DLL_TYPE;
			}
		}
	};
	return l_i_result;
}
extern "C" __declspec(dllexport) int EnumerateUsableBiometricDevices (void * l_p_handle, int * const o_p_deviceCount) {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_EnumerateUsableBiometricDevices", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_EnumerateUsableBiometricDevices)l_pf_getInterface)
						 (o_p_deviceCount);
		
		}
	
	return l_i_result;
}
extern "C" __declspec(dllexport) int OpenBioDevice (void * l_p_handle, const int i_i_deviceIndex,
				int * o_p_deviceHandle,
				void * const i_p_userData) {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_OpenBiometricDevice", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_OpenBiometricDevice)l_pf_getInterface)
						 (i_i_deviceIndex,o_p_deviceHandle,i_p_userData);
		
		}
	
	return l_i_result;
}
extern "C" __declspec(dllexport) int CloseBioDevice (void * l_p_handle, const int i_i_deviceHandle) {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_CloseBiometricDevice", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_CloseBiometricDevice)l_pf_getInterface)
						 (i_i_deviceHandle);
		
		}
	
	return l_i_result;
}
extern "C" __declspec(dllexport) int SetDetectionMode (void * l_p_handle, const int    i_i_deviceHandle, 
													   const int    i_i_detectionMode,  const int    i_i_fingerNumber) 
 {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_SetParametersForDetectionMode", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_SetParametersForDetectionMode)l_pf_getInterface)
						 (i_i_deviceHandle,
						 i_i_detectionMode,
						 i_i_fingerNumber);
		
		}
	
	return l_i_result;
}
extern "C" __declspec(dllexport) int GetDetectedImage (void * l_p_handle, const int i_i_deviceHandle,
				const unsigned long i_l_timeout,
				BDS_Image * const o_p_outputImage,
				BDS_DetectionResults * const o_p_results) {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_GetDetectedImage", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_GetDetectedImage)l_pf_getInterface)
						 (i_i_deviceHandle,
						 i_l_timeout, o_p_outputImage,o_p_results);
		
		}
	
	return l_i_result;
}

extern "C" __declspec(dllexport) BDS_Image * BDS_GetDirectImage (void * l_p_handle,const int i_i_deviceHandle,const unsigned long i_l_timeout
				,BDS_Image *	o_p_outputImage)
				{
					int l_i_result;
					//o_p_outputImage=(BDS_Image*) new BDS_Image();
				BDS_Image *	o_p_outputImage2=(BDS_Image *) new BDS_Image();
	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_GetDirectImage", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_GetDirectImage)l_pf_getInterface)
						 (i_i_deviceHandle,
						 i_l_timeout, o_p_outputImage2);
		}
	
	return o_p_outputImage2;
				}

extern "C" __declspec(dllexport) int BDS_SetParametersForDirectMode (void * l_p_handle,const int i_i_deviceHandle,const int i_i_samplingMode)
				{
					int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_SetParametersForDirectMode", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_SetParametersForDirectMode)l_pf_getInterface)
						 (i_i_deviceHandle,i_i_samplingMode );
		
		}
	
	return l_i_result;
}
			

extern "C" __declspec(dllexport) int AutoTest (void * l_p_handle,const int      i_i_deviceIndex, 
											   const BDS_TestParameters * const  i_p_testParameters, 
											   BDS_TestResults * const   o_p_testResults) {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_Autotest", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_Autotest)l_pf_getInterface)
						 (i_i_deviceIndex,
						 i_p_testParameters, o_p_testResults);
		
		}
	
	return l_i_result;
}

extern "C" __declspec(dllexport) int BDS_SetParametersForLiveMode (void * l_p_handle,
const int i_i_deviceHandle,
const int i_i_samplingMode) {
	int l_i_result;

	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_SetParametersForLiveMode", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_SetParametersForLiveMode)l_pf_getInterface)
						 (i_i_deviceHandle,
						 i_i_samplingMode);
		
		}
	
	return l_i_result;
}
int  ApplicationCallback(const int i_i_deviceHandle,BDS_Image * const i_p_currentImage,const unsigned char * const i_p_inputData,
	 unsigned char * const o_p_outputData,void * const o_p_userData){
       
  return 0;
 }

extern "C" __declspec(dllexport)  int BDS_DefineLiveProcess (void * l_p_handle, const int i_i_deviceHandle,BDS_Callback c) {
	int l_i_result;
    void * l_pf_getInterface=(void*)new int(20);
	
	//o_p_outputImage2=ApplicationCallback;
		l_i_result = GProcAddress(l_p_handle,"BDS_DefineLiveProcess", &l_pf_getInterface);
		std::cout<<l_i_result;
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_DefineLiveProcess)l_pf_getInterface)
						 (0,
						c);
		
		}
		//free(l_pf_getInterface);
	return l_i_result;
}



extern "C" __declspec(dllexport) int BDS_GetBiometricDeviceDescriptor (void * l_p_handle,const int i_i_deviceIndex,char * pointer){
	int l_i_result;
	BDS_DeviceDescriptor * o_p_deviceDescriptor =NULL;
	void * l_pf_getInterface;
		l_i_result = GProcAddress(l_p_handle,"BDS_GetBiometricDeviceDescriptor", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_BDS_GetBiometricDeviceDescriptor)l_pf_getInterface)
						 (i_i_deviceIndex,
						 o_p_deviceDescriptor);
		   pointer =o_p_deviceDescriptor->m_deviceSerial;
		}
	
	return l_i_result;
}

