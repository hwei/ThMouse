#pragma once

#include "GameConfigArray.h"

#define TEXTURE_FILE_PATH_LEN 256

extern HWND g_hFocusWindow;
extern BOOL g_mouseDown;
extern GameConfig g_currentGameConfig;
extern DWORD g_boomButton;
extern BOOL g_working;

extern GameConfigArray gs_gameConfigArray;
extern DWORD gs_boomButton;
extern char gs_textureFilePath[TEXTURE_FILE_PATH_LEN];
