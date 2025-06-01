#pragma once
#include <audiopolicy.h>

namespace engine::com::audio
{
	/// <summary>
	/// 오디오 섹션 이벤트를 처리하는 클래스
	/// </summary>
	class AudioSessionEvents : public IAudioSessionEvents
	{
	public:
		AudioSessionEvents();
		virtual ~AudioSessionEvents() = default;

		// IUnknown을(를) 통해 상속됨

		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IAudioSessionEvents을(를) 통해 상속됨

		HRESULT __stdcall OnDisplayNameChanged(LPCWSTR NewDisplayName, LPCGUID EventContext) override;
		HRESULT __stdcall OnIconPathChanged(LPCWSTR NewIconPath, LPCGUID EventContext) override;
		HRESULT __stdcall OnSimpleVolumeChanged(float NewVolume, BOOL NewMute, LPCGUID EventContext) override;
		HRESULT __stdcall OnChannelVolumeChanged(DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext) override;
		HRESULT __stdcall OnGroupingParamChanged(LPCGUID NewGroupingParam, LPCGUID EventContext) override;
		HRESULT __stdcall OnStateChanged(AudioSessionState NewState) override;
		HRESULT __stdcall OnSessionDisconnected(AudioSessionDisconnectReason DisconnectReason) override;

	private:
		ULONG _refCount = 0;
	};
}