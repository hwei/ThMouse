#include "stdafx.h"
#include "MyPeekMessageA.h"
#include "global.h"

SDLLHook PeekMessageAHook = 
{
	"USER32.DLL",
	false, NULL,		// Default hook disabled, NULL function pointer.
	{
		{ "PeekMessageA", (DWORD*)MyPeekMessageA},
		{ NULL, NULL }
	}
};

typedef BOOL (WINAPI * PeekMessageA_t)(__out LPMSG lpMsg, __in_opt HWND hWnd, __in UINT wMsgFilterMin, __in UINT wMsgFilterMax, __in UINT wRemoveMsg);

BOOL WINAPI MyPeekMessageA(__out LPMSG lpMsg, __in_opt HWND hWnd, __in UINT wMsgFilterMin, __in UINT wMsgFilterMax, __in UINT wRemoveMsg)
{
	static BOOL lastR = 0;
	PeekMessageA_t old_func = (PeekMessageA_t) PeekMessageAHook.Functions[0].OrigFn;
	BOOL r = old_func(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
	if(lpMsg->message == WM_LBUTTONDOWN)
	{
		g_mouseDown = 1;
	}
	else if(lpMsg->message == WM_RBUTTONDOWN)
	{
		lastR = 1;
	}
	else if(lpMsg->message == WM_RBUTTONUP)
	{
		if(lastR == 1)
		{
			lastR = 0;
			g_working = !g_working;
			//if(!g_working)
			//{
			//	WriteToLog( "keybd_event(VK_DOWN, 0, 0, 0);" );
			//	keybd_event(VK_DOWN, 0, 0, 0);
			//}
			//else
			//{
			//	WriteToLog( "keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);" );
			//	keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
			//}
		}
	}
	return r;
}
