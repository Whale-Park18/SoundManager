#include "volume_controller.h"

#include <iostream>

engine::com::audio::VolumeController::VolumeController(CComPtr< IMMDevice> pDevice, CComPtr<IAudioSessionEnumerator> pAudioSessionEnumerator)
	: _pDevice(pDevice)
	, _pAudioSessionEnumerator(pAudioSessionEnumerator)
{

}

HRESULT engine::com::audio::VolumeController::Update(CComPtr<IMMDevice> pDevice, CComPtr<IAudioSessionEnumerator> pAudioSessionEnumerator)
{
	return E_NOTIMPL;
}

HRESULT engine::com::audio::VolumeController::UpdateEndPoint(CComPtr< IMMDevice> pDevice)
{
	// 동일한 포인터이면, 같은 객체로 판단하여 예외 처리
	if (_pDevice == pDevice)
		return S_OK;

	HRESULT hr = E_FAIL;

	do
	{
		if (_pDevice == nullptr)
		{
			hr = E_HANDLE;

			// log
			break;
		}

		_pDevice = pDevice;
		hr = _pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&_pEndpointVolume);
		if (FAILED(hr))
		{
			std::cout << "Failed to activate IAudioEndpointVolume." << std::endl;
			break;
		}

	} while (false);

	return hr;
}

HRESULT engine::com::audio::VolumeController::UpdateSessionControllerList(CComPtr<IAudioSessionEnumerator> pAudioSessionEnumerator)
{
	// 동일한 포인터이면, 같은 객체로 판단하여 예외 처리
	if (_pAudioSessionEnumerator == pAudioSessionEnumerator)
		return S_OK;

	HRESULT hr = E_FAIL;

	do
	{
		if (_pAudioSessionEnumerator == nullptr)
		{
			hr = E_HANDLE;

			std::cout << "Audio session enumerator is not initialized." << std::endl;
			break;
		}

		_audioSessionControllerList.clear();

		int sessionCount = 0;
		_pAudioSessionEnumerator->GetCount(&sessionCount);

		for (int i = 0; i < sessionCount; ++i)
		{
			IAudioSessionControl* pSessionControl = nullptr;
			hr = _pAudioSessionEnumerator->GetSession(i, &pSessionControl);
			if (FAILED(hr))
			{
				std::cout << "Failed to get audio session control at index " << i << ": " << std::hex << hr << std::endl;
				continue;
			}

			_audioSessionControllerList.push_back(pSessionControl);
		}

	} while (false);

	return hr;
}
