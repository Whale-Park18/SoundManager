#include "session_manager.h"

#include <iostream>

engine::com::audio::SessionManager::SessionManager(CComPtr<IMMDevice> pDevice, SessionCreatedCallback&& callback)
	: _pDevice(std::move(pDevice))
{
	this->Initialized();
	this->AddAudioSessionEventListener(std::move(callback));
}

HRESULT engine::com::audio::SessionManager::Initialized()
{
	std::cout << "SessionManager::InitializeAudioSession()" << std::endl;

	HRESULT hr = E_FAIL;

	do // 흐름 제어용 do-wihle
	{
		if (_pDevice == nullptr)
		{
			hr = E_HANDLE;

			std::cout << "Audio device is not initialized." << std::endl;
			break;
		}

		// 기본 오디오 장치의 섹션 매니저 초기화
		// CComPtr 객체는 이미 할당됐을 때, 다시 초기화하려고 하면 에러가 발생
		if (_pAudioSessionManager != nullptr)
		{
			_pAudioSessionManager.Release();
			_pAudioSessionManager = nullptr;
		}

		hr = _pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, nullptr, (void**)&_pAudioSessionManager);
		if (FAILED(hr))
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
		if (FAILED(hr))
		{
			std::cout << "Failed to get session enumerator." << std::endl;
			break;
		}

	} while (false);

	return hr;
}

HRESULT engine::com::audio::SessionManager::UpdateAudioSessionEnumerator()
{
	return E_NOTIMPL;
}

HRESULT engine::com::audio::SessionManager::AddAudioSessionEventListener(SessionCreatedCallback&& callback)
{
	std::cout << "AudioManager::AddAudioDeviceEventListener()" << std::endl;

	_pAudioSessionNotification = new AudioSessionNotification(
		[this]() {
			UpdateAudioSessionEnumerator();

			if(_onSessionCreatedCallback)
			{
				_onSessionCreatedCallback();
			}
		}
	);

	auto hr = _pAudioSessionManager->RegisterSessionNotification(_pAudioSessionNotification);
	if (FAILED(hr))
	{
		std::cout << "Failed to register session notification callback : " << std::hex << hr << std::endl;
	}

	return hr;
}