/******************************************************************************

  PROJET      : SLAP SDK
  MODULE      : Interface

  DESCRIPTION : Common code to load DLLs (Implementation)

*******************************************************************************
  Copyright (c) SAGEM Defense Securite
******************************************************************************/
#include "BDS_Common.h"
#include "BDS_OS.h"

/*****************************************************************************/
int BDS_LoadLibrary(char * i_pc_path, void ** o_pp_handle) {
	HINSTANCE h_lib = LoadLibrary(i_pc_path);
	*o_pp_handle = NULL;
	if(h_lib == NULL)
		return ERROR_LOADLIBRARY;
	*o_pp_handle = h_lib;
	return 0;
}
/*****************************************************************************/
int BDS_GetProcAddress(void * i_p_handle,char * i_pc_method, void ** o_pp_procaddress) {
	void * l_p_proc;
	l_p_proc = GetProcAddress((HINSTANCE)i_p_handle,i_pc_method);
	if(l_p_proc == NULL)
		return ERROR_GETPROCADDRESS;
	*o_pp_procaddress = l_p_proc;
	return 0;
}
/*****************************************************************************/
int BDS_resolveInterface (char * i_pc_fullpath, int i_i_dllType, 
						  interfaceFunction ** o_p_interfaceTable,
						  int * o_i_interfaceTable_count,
						  int * o_i_dllVersion) {
	void * l_p_handle = 0;
	int l_i_result;
	int l_i_dllType;
	void * l_pf_getInterface;
	l_i_result = BDS_LoadLibrary(i_pc_fullpath,&l_p_handle);
	if(l_i_result == 0) {
		l_i_result = BDS_GetProcAddress(l_p_handle,"getInterface", &l_pf_getInterface);
		if(l_i_result == 0) {
			l_i_result = ((pf_getInterface)l_pf_getInterface)
						 (&l_i_dllType,
						  o_i_dllVersion,
						  o_p_interfaceTable,
						  o_i_interfaceTable_count);
			/* Test of the DLL type */
			if (i_i_dllType != l_i_dllType) {
				return ERROR_DLL_TYPE;
			}
		}
	};
	return l_i_result;
}
