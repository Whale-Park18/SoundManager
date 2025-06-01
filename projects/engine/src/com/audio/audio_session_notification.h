#pragma once
#include <functional>

#include <audiopolicy.h>

namespace engine::com::audio
{
	/// <summary>
	/// ����� ���� ���� �̺�Ʈ�� ó���ϴ� Ŭ����
	/// </summary>
	class AudioSessionNotification : public IAudioSessionNotification
	{
	public:
		AudioSessionNotification(std::function<void(void)> onSessionCreatedCallback);
		virtual ~AudioSessionNotification() = default;

		// IUnknown��(��) ���� ��ӵ�

		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IAudioSessionNotification��(��) ���� ��ӵ�

		HRESULT __stdcall OnSessionCreated(IAudioSessionControl* NewSession) override;

	private:
		ULONG _refCount = 0;

		std::function<void(void)> _onSessionCreatedCallback = nullptr;
	};
}