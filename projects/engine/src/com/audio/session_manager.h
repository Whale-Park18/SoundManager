#pragma once
#include "audio_session_notification.h"

#include <Windows.h>
#include <atlbase.h>		// COM 관련 헤더
#include <mmdeviceapi.h>	// 오디오 장치 관련 인터페이스
#include <audiopolicy.h>	// 오디오 세션 제어 인터페이스

namespace engine::com::audio
{
	/// <summary>
	/// 개별 어플리케이션의 오디오 세션을 관리하는 클래스
	/// </summary>
	class SessionManager
	{
	public:
		SessionManager(CComPtr<IMMDevice> pDevice, SessionCreatedCallback&& callback);
		virtual ~SessionManager() = default;

	private:

		/// <summary>
		/// 오디오 세션 관련 초기화
		/// </summary>
		/// <returns>결과</returns>
		HRESULT Initialized();

		/// <summary>
		/// 오디오 섹션 열거자 갱신
		/// </summary>
		/// <returns></returns>
		HRESULT UpdateAudioSessionEnumerator();

		/// <summary>
		/// 오디오 섹션 관련 이벤트 리스너 제거
		/// </summary>
		/// <returns>결과</returns>
		HRESULT AddAudioSessionEventListener(SessionCreatedCallback&& callback);

		CComPtr<IMMDevice> _pDevice = nullptr; // 기본 오디오 장치 (예 스피커, 헤드폰 등)

		CComPtr<IAudioSessionManager2>   _pAudioSessionManager	  = nullptr; // 오디오 세션 관리 인터페이스 (오디오 섹션을 관리하고 해당 컨트롤에 대한 액세스 제공)
		CComPtr<IAudioSessionEnumerator> _pAudioSessionEnumerator = nullptr; // 오디오 세션 열거기

		CComPtr<AudioSessionNotification> _pAudioSessionNotification = nullptr; // 오디오 세션 알림
		SessionCreatedCallback			  _onSessionCreatedCallback  = nullptr; // 세션 생성 콜백 함수	
	};
}