#include "stdafx.h"
#include "MyMmsystem.h"
#include "global.h"

#define X_MIN	0
#define X_MID	32767
#define X_MAX	65535
#define Y_MIN	0
#define Y_MID	32767
#define Y_MAX	65535

enum
{
	WinmmFN_joyGetDevCapsA = 0,
	WinmmFN_joyGetPosEx = 1,
	//WinmmFN_timeEndPeriod = 2,
	//WinmmFN_timeBeginPeriod = 3,
	//WinmmFN_timeGetTime = 4,
};

SDLLHook WinmmHook = 
{
	"WINMM.DLL",
	false, NULL,		// Default hook disabled, NULL function pointer.
	{
		{ "joyGetDevCapsA", (DWORD*)MyJoyGetDevCapsA},
		{ "joyGetPosEx", (DWORD*)MyJoyGetPosEx},
		//{ "timeEndPeriod", (DWORD*)MyTimeEndPeriod},
		//{ "timeBeginPeriod", (DWORD*)MyTimeBeginPeriod},
		//{ "timeGetTime", (DWORD*)MyTimeGetTime},
		{ NULL, NULL }
	}
};

typedef MMRESULT (WINAPI * joyGetDevCapsA_t)( __in UINT_PTR uJoyID, __out_bcount(cbjc) LPJOYCAPSA pjc, __in UINT cbjc);
typedef MMRESULT (WINAPI * joyGetPosEx_t)( __in UINT uJoyID, __out LPJOYINFOEX pji);
//typedef MMRESULT (WINAPI * timeBeginPeriod_t)( __in UINT uPeriod);
//typedef MMRESULT (WINAPI * timeEndPeriod_t)( __in UINT uPeriod);
//typedef DWORD (WINAPI * timeGetTime_t)(void);

MMRESULT WINAPI MyJoyGetDevCapsA( __in UINT_PTR uJoyID, __out_bcount(cbjc) LPJOYCAPSA pjc, __in UINT cbjc)
{
	//WriteToLog( "MyMmsystem: MyJoyGetDevCapsA called." );
	//joyGetDevCapsA_t old_func = (joyGetDevCapsA_t) WinmmHook.Functions[WinmmFN_joyGetDevCapsA].OrigFn;
	//MMRESULT r = old_func(uJoyID, pjc, cbjc);

	//char dbBuff[512];
	//sprintf_s(dbBuff, sizeof(dbBuff),
	//"MyMmsystem: MyJoyGetDevCapsA called. uJoyID = 0x%08X, szPname = %s, wNumButtons = %u, wNumAxes = %u, wXmin = %u, wXmax = %u, wYmin = %u, wYmax = %u\n",
	//uJoyID, pjc->szPname, pjc->wNumButtons, pjc->wNumAxes,
	//pjc->wXmin, pjc->wXmax, pjc->wYmin, pjc->wYmax);
	//WriteToLog( dbBuff );
	//return r;

	strcpy(pjc->szPname, "ThMouse");
	pjc->wNumButtons = 32;
	pjc->wMaxButtons = 32;
	pjc->wNumAxes = 2;
	pjc->wMaxAxes = 2;
	pjc->wXmin = X_MIN;
	pjc->wXmax = X_MAX;
	pjc->wYmin = Y_MIN;
	pjc->wYmax = Y_MAX;
	return JOYERR_NOERROR;
}

MMRESULT WINAPI MyJoyGetPosEx( __in UINT uJoyID, __out LPJOYINFOEX pji)
{
	//joyGetPosEx_t old_func = (joyGetPosEx_t) WinmmHook.Functions[WinmmFN_joyGetPosEx].OrigFn;
	//MMRESULT r = old_func(uJoyID, pji);
	//char dbBuff[512];
	//sprintf_s(dbBuff, sizeof(dbBuff),
	//"MyMmsystem: MyJoyGetPosEx called. uJoyID = 0x%08X, dwFlags = 0x%08X, dwButtons = 0x%08X, dwXpos = %u, dwYpos = %u\n",
	//uJoyID, pji->dwFlags, pji->dwButtons, pji->dwXpos, pji->dwYpos);
	//WriteToLog( dbBuff );
	//return r;

	if(g_working)
	{
		DWORD address = g_currentGameConfig.Posistion.Chain[0];
		for(int i=1; i<g_currentGameConfig.Posistion.Length; i++)
		{
			address = *((DWORD*)address);
			if(address == 0)
				break;
			address	+= g_currentGameConfig.Posistion.Chain[i];
		}
		if(address != 0)
		{
			POINT playerPos, mousePos;
			if(g_currentGameConfig.PosDataType == Int_DataType)
			{
				IntPoint * pPosition = (IntPoint*)(address);
				playerPos.x = (int)(pPosition->X/g_currentGameConfig.PixelRate + g_currentGameConfig.PixelOffset.X);
				playerPos.y = (int)(pPosition->Y/g_currentGameConfig.PixelRate + g_currentGameConfig.PixelOffset.Y);
			}
			else if(g_currentGameConfig.PosDataType == Float_DataType)
			{
				FloatPoint * pPosition = (FloatPoint*)(address);
				playerPos.x = (int)(pPosition->X/g_currentGameConfig.PixelRate + g_currentGameConfig.PixelOffset.X);
				playerPos.y = (int)(pPosition->Y/g_currentGameConfig.PixelRate + g_currentGameConfig.PixelOffset.Y);
			}
			GetCursorPos(&mousePos);
			ScreenToClient(g_hFocusWindow, &mousePos);
			if(playerPos.x < mousePos.x - 1)
			{
				pji->dwXpos = X_MAX;
			}
			else if(playerPos.x > mousePos.x + 1)
			{
				pji->dwXpos = X_MIN;
			}
			else
			{
				pji->dwXpos = X_MID;
			}
			if(playerPos.y < mousePos.y - 1)
			{
				pji->dwYpos = Y_MAX;
			}
			else if(playerPos.y > mousePos.y + 1)
			{
				pji->dwYpos = Y_MIN;
			}
			else
			{
				pji->dwYpos = Y_MID;
			}
		}
		else
		{
			pji->dwXpos = X_MID;
			pji->dwYpos = Y_MID;
		}
	}
	else
	{
		pji->dwXpos = X_MID;
		pji->dwYpos = Y_MID;
	}

	if(g_mouseDown)
	{
		pji->dwButtons = g_boomButton;
		g_mouseDown = 0;
	}
	else
	{
		pji->dwButtons = 0x00000000;
	}

	return JOYERR_NOERROR;
}

//MMRESULT WINAPI MyTimeBeginPeriod( __in UINT uPeriod)
//{
//	timeBeginPeriod_t old_func = (timeBeginPeriod_t) WinmmHook.Functions[WinmmFN_timeBeginPeriod].OrigFn;
//	return old_func(uPeriod);
//}
//MMRESULT WINAPI MyTimeEndPeriod( __in UINT uPeriod)
//{
//	timeEndPeriod_t old_func = (timeEndPeriod_t) WinmmHook.Functions[WinmmFN_timeEndPeriod].OrigFn;
//	return old_func(uPeriod);
//}
//DWORD WINAPI MyTimeGetTime()
//{
//	timeGetTime_t old_func = (timeGetTime_t) WinmmHook.Functions[WinmmFN_timeGetTime].OrigFn;
//	return old_func();
//}