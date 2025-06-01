#pragma once
#include <functional>

#include <audiopolicy.h>

namespace engine::com::audio
{
	/// <summary>
	/// 오디오 생성 섹션 이벤트를 처리하는 클래스
	/// </summary>
	class AudioSessionNotification : public IAudioSessionNotification
	{
	public:
		AudioSessionNotification(std::function<void(void)> onSessionCreatedCallback);
		virtual ~AudioSessionNotification() = default;

		// IUnknown을(를) 통해 상속됨

		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IAudioSessionNotification을(를) 통해 상속됨

		HRESULT __stdcall OnSessionCreated(IAudioSessionControl* NewSession) override;

	private:
		ULONG _refCount = 0;

		std::function<void(void)> _onSessionCreatedCallback = nullptr;
	};
}