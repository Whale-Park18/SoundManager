#include "mm_notification_client.h"

#include <iostream>

engine::com::audio::MMNotificationClient::MMNotificationClient() : _refCount(1)
{
}

HRESULT __stdcall engine::com::audio::MMNotificationClient::QueryInterface(REFIID riid, void** ppvObject)
{
    if (IID_IUnknown == riid || __uuidof(IMMNotificationClient) == riid) 
    {
        *ppvObject = static_cast<IMMNotificationClient*>(this);
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

ULONG __stdcall engine::com::audio::MMNotificationClient::AddRef(void)
{
    return InterlockedIncrement(&_refCount);
}

ULONG __stdcall engine::com::audio::MMNotificationClient::Release(void)
{
    ULONG refCount = InterlockedDecrement(&_refCount);
    if (0 == refCount)
    {
        delete this;
    }
    return refCount;
}

HRESULT __stdcall engine::com::audio::MMNotificationClient::OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState)
{
    std::cout << "AudioDeviceEventListener::OnDeviceStateChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::MMNotificationClient::OnDeviceAdded(LPCWSTR pwstrDeviceId)
{
    std::cout << "AudioDeviceEventListener::OnDeviceAdded" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::MMNotificationClient::OnDeviceRemoved(LPCWSTR pwstrDeviceId)
{
    std::cout << "AudioDeviceEventListener::OnDeviceRemoved" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::MMNotificationClient::OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId)
{
    std::cout << "AudioDeviceEventListener::OnDefaultDeviceChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::MMNotificationClient::OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key)
{
    std::cout << "AudioDeviceEventListener::OnPropertyValueChanged" << std::endl;
    return S_OK;
}
