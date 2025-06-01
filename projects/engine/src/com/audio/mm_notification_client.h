#pragma once
#include <functional>

#include <mmdeviceapi.h>

namespace engine::com::audio
{
	/// <summary>
	/// ����� ��ġ �̺�Ʈ ������ Ŭ����
	/// </summary>
	class MMNotificationClient : public IMMNotificationClient
	{
	public:
		MMNotificationClient();
		virtual~MMNotificationClient() = default;

		// IUnknown��(��) ���� ��ӵ�
		HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
		ULONG __stdcall AddRef(void) override;
		ULONG __stdcall Release(void) override;

		// IMMNotificationClient��(��) ���� ��ӵ�
		HRESULT __stdcall OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState) override;
		HRESULT __stdcall OnDeviceAdded(LPCWSTR pwstrDeviceId) override;
		HRESULT __stdcall OnDeviceRemoved(LPCWSTR pwstrDeviceId) override;
		HRESULT __stdcall OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId) override;
		HRESULT __stdcall OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key) override;

	private:
		ULONG _refCount = 0;

		// �Լ� ��ü�� ����Ͽ� �ݹ��� ���
	};
}