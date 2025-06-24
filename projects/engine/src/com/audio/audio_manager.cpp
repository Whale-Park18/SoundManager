#include "audio_manager.h"

#include <iostream>
#include <stdexcept>
#include <format>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

engine::com::audio::AudioManager::AudioManager()
{
	InitializeMMDevice();
	InitializeEndpointVolume();

	InitializeAudioSession();
	InitializeAudioSessionControlList();

	AddAudioDeviceEventListener();
	AddAudioSessionEventListener();
}

HRESULT engine::com::audio::AudioManager::SetAudioMasterVolume(float volumeLevel)
{
	HRESULT hr = E_FAIL;

	do // 흐름 제어용 do-while
	{
		if(0.0f < volumeLevel || volumeLevel < 1.0f)
		{
			hr = E_INVALIDARG;

			std::cout << "Volume level must be between 0.0 and 1.0." << std::endl;
			break;
		}
		
		if(_pEndpointVolume == nullptr)
		{
			hr = E_POINTER;

			std::cout << "Audio endpoint volume is not initialized." << std::endl;
			break;
		}

		auto hr = _pEndpointVolume->SetMasterVolumeLevelScalar(volumeLevel, nullptr);
		if(FAILED(hr))
		{
			std::cout << "Failed to set master volume level: " << std::hex << hr << std::endl;
			break;
		}

	} while (false);

	return hr;
}

engine::com::audio::ResultVolume engine::com::audio::AudioManager::GetAudioMasterVolume() const
{
	ResultVolume volumeLevel = { E_FAIL, 0.0f };

	do
	{
		if(_pEndpointVolume == nullptr)
		{
			volumeLevel.result = E_HANDLE;

			std::cout << "Audio endpoint volume is not initialized." << std::endl;
			break;
		}

		volumeLevel.result = _pEndpointVolume->GetMasterVolumeLevelScalar(&volumeLevel.value);
		if(FAILED(volumeLevel.result))
		{
			std::cout << "Failed to get master volume level: " << std::hex << volumeLevel.result << std::endl;
			break;
		}

	} while (false);
	
	return volumeLevel;
}

HRESULT engine::com::audio::AudioManager::SetAudioSessionSettings(DWORD processId, float volumeLevel)
{
	HRESULT hr = E_FAIL;
	
	return hr;
}

void engine::com::audio::AudioManager::GetAudioSessionSettings(std::vector<AudioSettingInfo>& audioSessions) const
{

}

HRESULT engine::com::audio::AudioManager::InitializeMMDevice()
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

		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&_pDeviceEnumerator));
		if(FAILED(hr))
		{
			std::cout << "Failed to create MMDeviceEnumerator instance." << std::endl;
			break;
		}

		// 기본 오디오 장치 초기화
		if(_pDevice != nullptr)
		{
			_pDevice.Release();
			_pDevice = nullptr;
		}

		hr = _pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &_pDevice);
		if(FAILED(hr))
		{
			std::cout << "Failed to get default audio endpoint." << std::endl;
			break;
		}

	} while (false);
	
	return hr;
}

HRESULT engine::com::audio::AudioManager::InitializeAudioSession()
{
	std::cout << "AudioManager::InitializeAudioSession()" << std::endl;
	
	HRESULT hr = E_FAIL;

	do // 흐름 제어용 do-wihle
	{
		if(_pDevice == nullptr)
		{
			hr = E_HANDLE;

			std::cout << "Audio device is not initialized." << std::endl;
			break;
		}

		// 기본 오디오 장치의 섹션 매니저 초기화
		// CComPtr 객체는 이미 할당됐을 때, 다시 초기화하려고 하면 에러가 발생
		if(_pAudioSessionManager != nullptr)
		{
			_pAudioSessionManager.Release();
			_pAudioSessionManager = nullptr;
		}

		hr = _pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr, (void**)&_pAudioSessionManager);
		if(FAILED(hr))
		{
			std::cout << "Failed to activate IAudioSessionManager2." << std::endl;
			break;
		}

		// 오디오 섹션 열거자 초기화
		if (_pAudioSessionEnumerator != nullptr)
		{
			_pAudioSessionEnumerator.Release();
			_pAudioSessionEnumerator = nullptr;
		}

		hr = _pAudioSessionManager->GetSessionEnumerator(&_pAudioSessionEnumerator);
		if(FAILED(hr))
		{
			std::cout << "Failed to get session enumerator." << std::endl;
			break;
		}

	} while (false);
	
	return hr;
}

HRESULT engine::com::audio::AudioManager::InitializeEndpointVolume()
{
	std::cout << "AudioManager::InitializeEndpointVolume()" << std::endl;
	
	HRESULT hr = E_FAIL;

	do
	{
		if (_pDevice == nullptr)
		{
			hr = E_HANDLE;

			std::cout << "Audio device is not initialized." << std::endl;
			break;
		}
		
		hr = _pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&_pEndpointVolume);
		if(FAILED(hr))
		{
			std::cout << "Failed to activate IAudioEndpointVolume." << std::endl;
			break;
		}

	} while (false);


	return hr;
}

HRESULT engine::com::audio::AudioManager::InitializeAudioSessionControlList()
{
	std::cout << "AudioManager::InitializeAudioSessionControlList()" << std::endl;
	
	HRESULT hr = E_FAIL;

	do
	{
		if(_pAudioSessionEnumerator == nullptr)
		{
			hr = E_HANDLE;

			std::cout << "Audio session enumerator is not initialized." << std::endl;
			break;
		}

		_audioSessionControlList.clear();

		int sessionCount = 0;
		_pAudioSessionEnumerator->GetCount(&sessionCount);

		for(int i = 0; i < sessionCount; ++i)
		{
			IAudioSessionControl* pSessionControl = nullptr;
			hr = _pAudioSessionEnumerator->GetSession(i, &pSessionControl);
			if(FAILED(hr))
			{
				std::cout << "Failed to get audio session control at index " << i << ": " << std::hex << hr << std::endl;
				continue;
			}
			
			_audioSessionControlList.push_back(pSessionControl);
		}

	} while (false);

	return hr;
}

HRESULT engine::com::audio::AudioManager::AddAudioDeviceEventListener()
{
	std::cout << "AudioManager::AddAudioDeviceEventListener()" << std::endl;
	
	_pAudioDeviceEventListener = new MMNotificationClient();
	auto hr = _pDeviceEnumerator->RegisterEndpointNotificationCallback(_pAudioDeviceEventListener);
	if(FAILED(hr))
	{
		std::cout << "Failed to register endpoint notification callback." << std::endl;
	}

	return hr;
}

HRESULT engine::com::audio::AudioManager::AddAudioSessionEventListener()
{
	std::cout << "AudioManager::AddAudioDeviceEventListener()" << std::endl;

	_pAudioSessionNotification = new AudioSessionNotification(
		[this]() {
			InitializeAudioSession();
			InitializeAudioSessionControlList();
		}
	);

	auto hr = _pAudioSessionManager->RegisterSessionNotification(_pAudioSessionNotification);
	if (FAILED(hr))
	{
		std::cout << "Failed to register session notification callback : " << std::hex << hr << std::endl;
	}

	return hr;
}
