#include "device_manager.h"

#include <iostream>

engine::com::audio::DeviceManager::DeviceManager(DeviceEventCallback&& callback)
{
	this->Initialized();
	this->AddAudioDeviceEventListener(std::move(callback));
}

HRESULT engine::com::audio::DeviceManager::Initialized()
{
	std::cout << "AudioManager::InitializeMMDevice()" << std::endl;

	HRESULT hr = E_FAIL;

	do // 흐름 제어용 do-while
	{
		// 오디오 장치 열거자 초기화
		// CComPtr 객체는 이미 할당됐을 때, 다시 초기화하려고 하면 에러가 발생
		if (_pDeviceEnumerator != nullptr)
		{
			_pDeviceEnumerator.Release();
			_pDeviceEnumerator = nullptr;
		}

		//hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&_pDeviceEnumerator));
		hr = _pDeviceEnumerator.CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL);
		if (FAILED(hr))
		{
			std::cout << "Failed to create MMDeviceEnumerator instance." << std::endl;
			break;
		}

		// 기본 오디오 장치 초기화
		if (_pDevice != nullptr)
		{
			_pDevice.Release();
			_pDevice = nullptr;
		}

		hr = _pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &_pDevice);
		if (FAILED(hr))
		{
			std::cout << "Failed to get default audio endpoint." << std::endl;
			break;
		}

	} while (false);

	return hr;
}

HRESULT engine::com::audio::DeviceManager::AddAudioDeviceEventListener(DeviceEventCallback&& callback)
{
	std::cout << "AudioManager::AddAudioDeviceEventListener()" << std::endl;

	_pAudioDeviceEventListener = new MMNotificationClient(std::move(callback));
	auto hr = _pDeviceEnumerator->RegisterEndpointNotificationCallback(_pAudioDeviceEventListener);
	if (FAILED(hr))
	{
		std::cout << "Failed to register endpoint notification callback." << std::endl;
	}

	return hr;
}