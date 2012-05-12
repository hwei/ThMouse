#include "stdafx.h"

#include "MyDirectInput8Create.h"
#include "MyDirectInput8.h"

// Function pointer types.
typedef HRESULT (WINAPI * DirectInput8Create_t)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);


SDLLHook DInput8Hook = 
{
	"DINPUT8.dll",
	false, NULL,		// Default hook disabled, NULL function pointer.
	{
		{ "DirectInput8Create", (DWORD*)MyDirectInput8Create},
		{ NULL, NULL }
	}
};

HRESULT WINAPI MyDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	//WriteToLog( "DInput8Hook: MyDirectInput8Create called.\n" );

	DirectInput8Create_t old_func = (DirectInput8Create_t) DInput8Hook.Functions[0].OrigFn;
	HRESULT hr = old_func(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	*ppvOut = new MyDirectInput8((IDirectInput8*)*ppvOut);
	
	return hr;
}