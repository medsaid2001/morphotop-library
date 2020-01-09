/******************************************************************************

  PROJET      : SLAP SDK
  MODULE      : Interfaces

  DESCRIPTION : Interface to Operating system

*******************************************************************************
  Copyright (c) SAGEM Defense Securite
******************************************************************************/

#if defined(WindowsXP)

#include <windows.h>
#include <process.h>

#define BDS_OS_StartThread _beginthread
#define BDS_OS_ExitThread ExitThread
#define BDS_OS_Sleep Sleep
#define BDS_OS_GetTickCount GetTickCount
#define BDS_OS_CreateMutex CreateMutex
#define BDS_OS_ReleaseMutex ReleaseMutex
#define BDS_OS_CreateEvent CreateEvent
#define BDS_OS_SetEvent SetEvent 
#define BDS_OS_ResetEvent ResetEvent
#define BDS_OS_WaitForSingleObject WaitForSingleObject
#define BDS_OS_CloseMutex CloseHandle
#define BDS_OS_CloseEvent CloseHandle
#define BDS_OS_CloseHandle CloseHandle


#endif
