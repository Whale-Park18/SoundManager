#pragma once
#include <functional>

#include <mmdeviceapi.h>

namespace engine::com::audio
{
	/// <summary>
	/// 오디오 장치 이벤트 리스너 클래스
	/// </summary>
	class MMNotificationClient : public IMMNotificationClient
	{
	public:
		MMNotificationClient();
		virtual~MMNotificationClient() = default;

		// IUnknown을(를) 통해 상속됨
		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IMMNotificationClient을(를) 통해 상속됨
		HRESULT __stdcall OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState) override;
		HRESULT __stdcall OnDeviceAdded(LPCWSTR pwstrDeviceId) override;
		HRESULT __stdcall OnDeviceRemoved(LPCWSTR pwstrDeviceId) override;
		HRESULT __stdcall OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId) override;
		HRESULT __stdcall OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key) override;

	private:
		ULONG _refCount = 0;

		// 함수 객체를 사용하여 콜백을 등록
	};
}