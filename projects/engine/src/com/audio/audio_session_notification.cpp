#include "audio_session_notification.h"

#include <iostream>

engine::com::audio::AudioSessionNotification::AudioSessionNotification(std::function<void(void)> onSessionCreatedCallback) : 
	_onSessionCreatedCallback(onSessionCreatedCallback),
    _refCount(1)
{
}

HRESULT __stdcall engine::com::audio::AudioSessionNotification::QueryInterface(REFIID riid, void** ppvObject)
{
    if (IID_IUnknown == riid || __uuidof(IAudioSessionNotification) == riid)
    {
        *ppvObject = static_cast<IAudioSessionNotification*>(this);
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

ULONG __stdcall engine::com::audio::AudioSessionNotification::AddRef(void)
{
    return InterlockedIncrement(&_refCount);
}

ULONG __stdcall engine::com::audio::AudioSessionNotification::Release(void)
{
    ULONG refCount = InterlockedDecrement(&_refCount);
    if (0 == refCount)
    {
        delete this;
    }
    return refCount;
}

HRESULT __stdcall engine::com::audio::AudioSessionNotification::OnSessionCreated(IAudioSessionControl* NewSession)
{
	std::cout << "AudioSessionNotification::OnSessionCreated" << std::endl;

    if (_onSessionCreatedCallback)
    {
        _onSessionCreatedCallback();
    }

    return S_OK;
}
