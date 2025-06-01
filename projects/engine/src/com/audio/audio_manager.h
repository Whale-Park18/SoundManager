#pragma once
#include "../com_result.h"
#include "mm_notification_client.h"
#include "audio_session_events.h"
#include "audio_session_notification.h"

#include <thread>
#include <vector>
#include <memory>

#include <atlbase.h>		// COM ���� ���
#include <mmdeviceapi.h>	// ����� ��ġ ���� �������̽�
#include <audiopolicy.h>	// ����� ���� ���� �������̽�
#include <endpointvolume.h>	// ���� ���� �������̽�

namespace engine::com::audio
{
	using ResultVolume = ComResult<float>;

	class AudioManager
	{
	public:

		struct AudioSettingInfo
		{
			DWORD processId = 0;	  // ���μ��� ID
			float volumeLevel = 0.0f; // ���� ���� (0.0f ~ 1.0f)
		};

		AudioManager();
		virtual ~AudioManager() = default;

		/// <summary>
		/// �⺻ ��ġ�� ����� ���� ����
		/// </summary>
		/// <param name="volumeLevel"></param>
		/// <returns></returns>
		HRESULT SetAudioMasterVolume(float volumeLevel);

		/// <summary>
		/// �⺻ ��ġ�� ����� ���� ��ȯ
		/// </summary>
		/// <returns></returns>
		ResultVolume GetAudioMasterVolume() const;

		/// <summary>
		/// ����� ������ ���� ���� ����
		/// </summary>
		/// <param name="processId"></param>
		/// <param name="volumeLevel"></param>
		/// <returns></returns>
		HRESULT SetAudioSessionSettings(DWORD processId, float volumeLevel);

		/// <summary>
		/// ����� ������ ���� ����Ʈ ��ȯ
		/// </summary>
		/// <param name="audioSessions"></param>
		void GetAudioSessionSettings(std::vector<AudioSettingInfo>& audioSessions) const;

	private:

		/// <summary>
		/// ����� ��ġ ���� �ʱ�ȭ
		/// </summary>
		/// <returns>���</returns>
		HRESULT InitializeMMDevice();

		/// <summary>
		/// ����� ���� ���� �ʱ�ȭ
		/// </summary>
		/// <returns>���</returns>
		HRESULT InitializeAudioSession();

		/// <summary>
		/// ����� �ý��� ���� ���� �ʱ�ȭ
		/// </summary>
		/// <returns>���</returns>
		HRESULT InitializeEndpointVolume();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>���</returns>
		HRESULT InitializeAudioSessionControlList();

		/// <summary>
		/// ����� ��ġ ���� �̺�Ʈ ������ �߰�
		/// </summary>
		/// <returns>���</returns>
		HRESULT AddAudioDeviceEventListener();

		/// <summary>
		/// ����� ���� ���� �̺�Ʈ ������ ����
		/// </summary>
		/// <returns>���</returns>
		HRESULT AddAudioSessionEventListener();

		// ����� ��ġ ����
		CComPtr<IMMDeviceEnumerator>	 _pDeviceEnumerator = nullptr; // ����� ��ġ ������ (��밡���� ����� ��ġ ����)
		CComPtr<IMMDevice>				 _pDevice			= nullptr; // �⺻ ����� ��ġ (�� ����Ŀ, ����� ��)
		
		// ����� ���� ����
		CComPtr<IAudioSessionManager2>	 _pAudioSessionManager	  = nullptr; // ����� ���� ���� �������̽� (����� ������ �����ϰ� �ش� ��Ʈ�ѿ� ���� �׼��� ����)
		CComPtr<IAudioSessionEnumerator> _pAudioSessionEnumerator = nullptr; // ����� ���� ���ű�
		
		// ����� �ý��� ���� ���� ����
		CComPtr<IAudioEndpointVolume>	 _pEndpointVolume = nullptr; // ����� ���� ���� �������̽�

		// ����� ���� ���� ���� ����
		std::vector<CComPtr<IAudioSessionControl>> _audioSessionControlList; // ����� ���� ��Ʈ�� ����Ʈ

		// ����� ��ġ �̺�Ʈ ������ �� ���� �̺�Ʈ ������
		CComPtr<MMNotificationClient>	  _pAudioDeviceEventListener = nullptr; // ����� ��ġ �̺�Ʈ ������
		CComPtr<AudioSessionEvents>		  _pAudioSessionEvents		 = nullptr; // ����� ���� �̺�Ʈ ������
		CComPtr<AudioSessionNotification> _pAudioSessionNotification = nullptr; // ����� ���� �˸�
	};
}


