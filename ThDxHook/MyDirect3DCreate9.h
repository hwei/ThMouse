#pragma once

#include "apihijack.h"

IDirect3D9* WINAPI MyDirect3DCreate9(UINT sdk_version);

extern SDLLHook D3DHook;
