// ThDxHook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ThDxHook.h"
#include "global.h"
#include "apihijack.h"

#pragma data_seg(".HOOKDATA")//Shared data among all instances.
HHOOK hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.HOOKDATA,RWS")//linker directive

extern HINSTANCE hinstance;


LRESULT CALLBACK hookproc(int ncode,WPARAM wparam,LPARAM lparam)
{
	return CallNextHookEx(hHook,ncode,wparam,lparam);//pass control to next hook in the hook chain.
}

THDXHOOK_API int installThDxHook(const GameConfigArray * config, int leftButton, const char * pTextureFilePath)
{
	strcpy_s<TEXTURE_FILE_PATH_LEN>(gs_textureFilePath, pTextureFilePath);

	gs_gameConfigArray = *config;
	if(leftButton >=0 && leftButton < 32)
		gs_boomButton = 1<<leftButton;
	else
		gs_boomButton = 0x00000001;

	hHook = NULL;
	hHook = SetWindowsHookEx(WH_CBT,hookproc,hinstance,NULL);
	if(hHook == NULL)
	{
		DWORD dwErr = GetLastError();
		// lookup error code and display it
		LPVOID lpMsgBuf;
		FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwErr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL
		  );
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Install ThDxHook.dll: Error", MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );         

		return 0;
	}

	return 1;
}

THDXHOOK_API int removeThDxHook(void)
{
	return UnhookWindowsHookEx(hHook);
}
