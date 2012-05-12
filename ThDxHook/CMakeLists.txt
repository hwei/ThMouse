cmake_minimum_required(VERSION 2.8)
set(SRC_LIST
apihijack.h                GameConfigArray.h
global.h                   MyDirect3D9.h
MyDirect3DCreate9.h        MyDirect3DDevice9.h
MyDirectInput8.h           MyDirectInput8Create.h
MyDirectInputDevice8.h     MyMmsystem.h
MyPeekMessageA.h           stdafx.h
targetver.h                ThDxHook.h
apihijack.cpp              dllmain.cpp
global.cpp                 MyDirect3DCreate9.cpp
MyDirectInput8Create.cpp   MyMmsystem.cpp
MyPeekMessageA.cpp         stdafx.cpp
ThDxHook.cpp
)
add_library(ThDxHook SHARED ${SRC_LIST})
target_link_libraries(ThDxHook shlwapi winmm dxguid D3dx9)
add_definitions("-DTHDXHOOK_EXPORTS")