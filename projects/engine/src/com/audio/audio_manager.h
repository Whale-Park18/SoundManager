#pragma once
#include "../com_result.h"
#include "mm_notification_client.h"
#include "audio_session_events.h"
#include "audio_session_notification.h"

#include <thread>
#include <vector>
#include <memory>

#include <atlbase.h>		// COM 관련 헤더
#include <mmdeviceapi.h>	// 오디오 장치 관련 인터페이스
#include <audiopolicy.h>	// 오디오 세션 제어 인터페이스
#include <endpointvolume.h>	// 볼륨 제어 인터페이스

namespace engine::com::audio
{
	using ResultVolume = ComResult<float>;

	class AudioManager
	{
	public:

		struct AudioSettingInfo
		{
			DWORD processId = 0;	  // 프로세스 ID
			float volumeLevel = 0.0f; // 볼륨 레벨 (0.0f ~ 1.0f)
		};

		AudioManager();
		virtual ~AudioManager() = default;

		/// <summary>
		/// 기본 장치의 오디오 볼륨 설정
		/// </summary>
		/// <param name="volumeLevel"></param>
		/// <returns></returns>
		HRESULT SetAudioMasterVolume(float volumeLevel);

		/// <summary>
		/// 기본 장치의 오디오 볼륨 반환
		/// </summary>
		/// <returns></returns>
		ResultVolume GetAudioMasterVolume() const;

		/// <summary>
		/// 오디오 섹션의 설정 레벨 설정
		/// </summary>
		/// <param name="processId"></param>
		/// <param name="volumeLevel"></param>
		/// <returns></returns>
		HRESULT SetAudioSessionSettings(DWORD processId, float volumeLevel);

		/// <summary>
		/// 오디오 섹션의 설정 리스트 반환
		/// </summary>
		/// <param name="audioSessions"></param>
		void GetAudioSessionSettings(std::vector<AudioSettingInfo>& audioSessions) const;

	private:

		/// <summary>
		/// 오디오 장치 관련 초기화
		/// </summary>
		/// <returns>결과</returns>
		HRESULT InitializeMMDevice();

		/// <summary>
		/// 오디오 세션 관련 초기화
		/// </summary>
		/// <returns>결과</returns>
		HRESULT InitializeAudioSession();

		/// <summary>
		/// 오디오 시스템 볼륨 제어 초기화
		/// </summary>
		/// <returns>결과</returns>
		HRESULT InitializeEndpointVolume();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>결과</returns>
		HRESULT InitializeAudioSessionControlList();

		/// <summary>
		/// 오디오 장치 관련 이벤트 리스너 추가
		/// </summary>
		/// <returns>결과</returns>
		HRESULT AddAudioDeviceEventListener();

		/// <summary>
		/// 오디오 섹션 관련 이벤트 리스너 제거
		/// </summary>
		/// <returns>결과</returns>
		HRESULT AddAudioSessionEventListener();

		// 오디오 장치 관련
		CComPtr<IMMDeviceEnumerator>	 _pDeviceEnumerator = nullptr; // 오디오 장치 열거자 (사용가능한 오디오 장치 나열)
		CComPtr<IMMDevice>				 _pDevice			= nullptr; // 기본 오디오 장치 (예 스피커, 헤드폰 등)
		
		// 오디오 세션 관련
		CComPtr<IAudioSessionManager2>	 _pAudioSessionManager	  = nullptr; // 오디오 세션 관리 인터페이스 (오디오 섹션을 관리하고 해당 컨트롤에 대한 액세스 제공)
		CComPtr<IAudioSessionEnumerator> _pAudioSessionEnumerator = nullptr; // 오디오 세션 열거기
		
		// 오디오 시스템 볼륨 제어 관련
		CComPtr<IAudioEndpointVolume>	 _pEndpointVolume = nullptr; // 오디오 볼륨 제어 인터페이스

		// 오디오 섹션 볼륨 제어 관련
		std::vector<CComPtr<IAudioSessionControl>> _audioSessionControlList; // 오디오 섹션 컨트롤 리스트

		// 오디오 장치 이벤트 리스너 및 세션 이벤트 리스너
		CComPtr<MMNotificationClient>	  _pAudioDeviceEventListener = nullptr; // 오디오 장치 이벤트 리스너
		CComPtr<AudioSessionEvents>		  _pAudioSessionEvents		 = nullptr; // 오디오 세션 이벤트 리스너
		CComPtr<AudioSessionNotification> _pAudioSessionNotification = nullptr; // 오디오 세션 알림
	};
}


