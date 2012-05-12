// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "apihijack.h"
#include "MyDirect3DCreate9.h"
#include "MyDirectInput8Create.h"
#include "MyMmsystem.h"
#include "MyPeekMessageA.h"
#include "global.h"


HINSTANCE hinstance = NULL;
static char buffer[256];


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	char dbBuff[128];

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hinstance = hModule;
		
		// We don't need thread notifications for what we're doing.  Thus, get
		// rid of them, thereby eliminating some of the overhead of this DLL
		DisableThreadLibraryCalls( hModule );

		// Only hook the APIs if this is the process of the th11.exe.
		GetModuleFileName( GetModuleHandle( NULL ), buffer, sizeof(buffer) );
		
		PathStripPath( buffer );


		//sprintf_s(dbBuff, sizeof(dbBuff), "attach to %s", buffer);
		//WriteToLog(dbBuff);
		for(int i=0; i<gs_gameConfigArray.Length; i++)
		{
			if(strcmp(buffer, gs_gameConfigArray.Configs[i].ProcessName) == 0)
			{
				g_currentGameConfig = gs_gameConfigArray.Configs[i];
				g_boomButton = gs_boomButton;
				//sprintf_s(dbBuff, sizeof(dbBuff), "found %s. Let's hook it.\n", buffer);
				//WriteToLog(dbBuff);
				HookAPICalls(&D3DHook);
				HookAPICalls(&DInput8Hook);
				HookAPICalls(&WinmmHook);
				HookAPICalls(&PeekMessageAHook);
			}
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

