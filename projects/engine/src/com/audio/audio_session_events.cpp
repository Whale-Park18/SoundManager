#include "audio_session_events.h"

#include <iostream>

engine::com::audio::AudioSessionEvents::AudioSessionEvents() : _refCount(1)
{
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::QueryInterface(REFIID riid, void** ppvObject)
{
    if (IID_IUnknown == riid || __uuidof(IAudioSessionEvents) == riid)
    {
        *ppvObject = static_cast<IAudioSessionEvents*>(this);
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

ULONG __stdcall engine::com::audio::AudioSessionEvents::AddRef(void)
{
    return InterlockedIncrement(&_refCount);
}

ULONG __stdcall engine::com::audio::AudioSessionEvents::Release(void)
{
    ULONG refCount = InterlockedDecrement(&_refCount);
    if (0 == refCount)
    {
        delete this;
    }
    return refCount;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnDisplayNameChanged(LPCWSTR NewDisplayName, LPCGUID EventContext)
{
    std::cout << "AudioSessionEventListener::OnDisplayNameChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnIconPathChanged(LPCWSTR NewIconPath, LPCGUID EventContext)
{
    std::cout << "AudioSessionEventListener::OnIconPathChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnSimpleVolumeChanged(float NewVolume, BOOL NewMute, LPCGUID EventContext)
{
    std::cout << "AudioSessionEventListener::OnSimpleVolumeChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnChannelVolumeChanged(DWORD ChannelCount, float NewChannelVolumeArray[], DWORD ChangedChannel, LPCGUID EventContext)
{
    std::cout << "AudioSessionEventListener::OnChannelVolumeChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnGroupingParamChanged(LPCGUID NewGroupingParam, LPCGUID EventContext)
{
    std::cout << "AudioSessionEventListener::OnGroupingParamChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnStateChanged(AudioSessionState NewState)
{
    std::cout << "AudioSessionEventListener::OnStateChanged" << std::endl;
    return S_OK;
}

HRESULT __stdcall engine::com::audio::AudioSessionEvents::OnSessionDisconnected(AudioSessionDisconnectReason DisconnectReason)
{
    std::cout << "AudioSessionEventListener::OnSessionDisconnected" << std::endl;
    return S_OK;
}