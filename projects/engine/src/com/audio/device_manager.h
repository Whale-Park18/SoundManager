#pragma once

#include "mm_notification_client.h"

#include <functional>

#include <atlbase.h>		// COM 관련 헤더
#include <mmdeviceapi.h>	// 오디오 장치 관련 인터페이스

namespace engine::com::audio
{
	/// <summary>
	/// 오디오 장치 관련 기능을 관리하는 클래스
	/// </summary>
	class DeviceManager
	{
	public:
		DeviceManager(DeviceEventCallback&& callback);
		virtual ~DeviceManager() = default;

		CComPtr<IMMDeviceEnumerator> GetDeviceEnumerator() const { return _pDeviceEnumerator; }
		CComPtr<IMMDevice> GetDefaultDevice() const { return _pDevice; }

	private:

		/// <summary>
		/// 오디오 장치 관련 초기화
		/// </summary>
		/// <returns>결과</returns>
		HRESULT Initialized();

		/// <summary>
		/// 오디오 장치 관련 이벤트 리스너 추가
		/// </summary>
		/// <returns>결과</returns>
		HRESULT AddAudioDeviceEventListener(DeviceEventCallback&& callback);

		CComPtr<IMMDeviceEnumerator> _pDeviceEnumerator = nullptr; // 오디오 장치 열거자 (사용가능한 오디오 장치 나열)
		CComPtr<IMMDevice>			 _pDevice			= nullptr; // 기본 오디오 장치 (예 스피커, 헤드폰 등)

		CComPtr<MMNotificationClient> _pAudioDeviceEventListener = nullptr; // 오디오 장치 이벤트 리스너
	};
}


