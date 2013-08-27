#pragma once

#include "global.h"

class MyDirectInputDevice8 : public IDirectInputDevice8
{
public:
	MyDirectInputDevice8(IDirectInputDevice8 * device):m_device(device)
	{
	}
    /*** IUnknown methods ***/
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj)
	{
		return m_device->QueryInterface(riid, ppvObj);
	}
    ULONG STDMETHODCALLTYPE AddRef()
	{
		return m_device->AddRef();
	}
    ULONG STDMETHODCALLTYPE Release()
	{
		//WriteToLog( "MyDirectInputDevice8: Release called.\n" );
		ULONG count = m_device->Release();
		if(0 == count)
			delete this;

		return count;
	}

    /*** IDirectInputDevice8A methods ***/
    HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
	{
		return m_device->GetCapabilities(lpDIDevCaps);
	}
    HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		return m_device->EnumObjects(lpCallback, pvRef, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
	{
		return m_device->GetProperty(rguidProp, pdiph);
	}
    HRESULT STDMETHODCALLTYPE SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
	{
		return m_device->SetProperty(rguidProp, pdiph);
	}
	HRESULT STDMETHODCALLTYPE Acquire()
	{
		//WriteToLog( "MyDirectInputDevice8: Acquire called.\n" );
		return m_device->Acquire();
	}
    HRESULT STDMETHODCALLTYPE Unacquire()
	{
		return m_device->Unacquire();
	}
    HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData)
	{
		HRESULT hr = m_device->GetDeviceState(cbData, lpvData);
		//FILE* log;
		//log = fopen("D:\\keyboardData", "ab");
		//if (log != NULL)
		//{
		//	fwrite(lpvData, sizeof(char), cbData, log);
		//	fclose(log);
		//}
		if(SUCCEEDED(hr) && cbData == sizeof(BYTE) * 256)
		{
			BYTE* keys = static_cast<BYTE*>(lpvData);
			if(g_mouseDown)
			{
				keys[DIK_X] |= 0x80;
				g_mouseDown = 0;
			}
			if(g_working)
			{
				DWORD address = g_currentGameConfig.Posistion.Chain[0];
				for(int i=1; i<g_currentGameConfig.Posistion.Length; i++)
				{
					address = *((DWORD*)address);
					if(address == 0)
					{
						break;
					}
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
						keys[DIK_RIGHT] |= 0x80;
					}
					else if(playerPos.x > mousePos.x + 1)
					{
						keys[DIK_LEFT] |= 0x80;
					}

					if(playerPos.y < mousePos.y - 1)
					{
						keys[DIK_DOWN] |= 0x80;
					}
					else if(playerPos.y > mousePos.y + 1)
					{
						keys[DIK_UP] |= 0x80;
					}

				}
			}
		}
		return hr;
	}
    HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
	{
		//WriteToLog( "MyDirectInputDevice8: GetDeviceData called.\n" );
		return m_device->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		return m_device->SetDataFormat(lpdf);
	}
	HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent)
	{
		return m_device->SetEventNotification(hEvent);
	}
    HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		return m_device->SetCooperativeLevel(hwnd, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
	{
		return m_device->GetObjectInfo(pdidoi, dwObj, dwHow);
	}
    HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCE pdidi)
	{
		return m_device->GetDeviceInfo(pdidi);
	}
    HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		return m_device->RunControlPanel(hwndOwner, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
	{
		return m_device->Initialize(hinst, dwVersion, rguid);
	}
    HRESULT STDMETHODCALLTYPE CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT * ppdeff, LPUNKNOWN punkOuter)
	{
		return m_device->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
	}
    HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType)
	{
		return m_device->EnumEffects(lpCallback, pvRef, dwEffType);
	}
    HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA pdei, REFGUID rguid)
	{
		return m_device->GetEffectInfo(pdei, rguid);
	}
    HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut)
	{
		return m_device->GetForceFeedbackState(pdwOut);
	}
    HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags)
	{
		return m_device->SendForceFeedbackCommand(dwFlags);
	}
    HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		return m_device->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
	}
    HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE pesc)
	{
		return m_device->Escape(pesc);
	}
    HRESULT STDMETHODCALLTYPE Poll()
	{
		return m_device->Poll();
	}
    HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
	{
		return m_device->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
	}
    HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
	{
		return m_device->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
	{
		return m_device->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags)
	{
		return m_device->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE SetActionMap( LPDIACTIONFORMATA lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags)
	{
		return m_device->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
	}
    HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader)
	{
		return m_device->GetImageInfo(lpdiDevImageInfoHeader);
	}
private:
	IDirectInputDevice8 * m_device;
};