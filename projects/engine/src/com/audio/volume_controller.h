#pragma once

#include <vector>

#include <atlbase.h>		// COM 관련 헤더
#include <mmdeviceapi.h>	// 오디오 장치 관련 인터페이스
#include <audiopolicy.h>	// 오디오 세션 제어 인터페이스
#include <endpointvolume.h>	// 볼륨 제어 인터페이스

namespace engine::com::audio
{
	using AudioSessionControllerList = std::vector<CComPtr<IAudioSessionControl>>;

	/// <summary>
	/// 시스템 및 섹션의 볼륨을 제어하는 클래스
	/// </summary>
	/// <remarks>
	/// - 시스템 볼륨 제어
	///	    1. IMMDevice 객체 초기화
	///	    2. IMMDevice 객체로 IAudioEndPointVolume 객체 초기화
	/// - 어플리케이션 오디오 섹션 제어
	///     1. "섹션 열거자" 객체 초기화
	///     2. "섹션 열거자" 객체에서 IAudioSessionControl 객체 획득
	/// </remarks>
	class VolumeController
	{
	public:
		VolumeController(CComPtr< IMMDevice> pDevice, CComPtr<IAudioSessionEnumerator> pAudioSessionEnumerator);
		virtual ~VolumeController() = default;

		HRESULT Update(CComPtr< IMMDevice> pDevice, CComPtr<IAudioSessionEnumerator> pAudioSessionEnumerator);

	private:

		HRESULT UpdateEndPoint(CComPtr< IMMDevice> pDevice);

		HRESULT UpdateSessionControllerList(CComPtr<IAudioSessionEnumerator> pAudioSessionEnumerator);

		CComPtr< IMMDevice>			  _pDevice		   = nullptr;
		CComPtr<IAudioEndpointVolume> _pEndpointVolume = nullptr; // 오디오 볼륨 제어 객체

		CComPtr<IAudioSessionEnumerator> _pAudioSessionEnumerator = nullptr; //
		AudioSessionControllerList			 _audioSessionControllerList;			 // 오디오 섹션 볼륨 제어 객체
	};
}