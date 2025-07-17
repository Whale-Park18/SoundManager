#pragma once
#include <utility>
#include <concepts>

#include <windows.h>

template<typename T>
concept HandleType = std::same_as<T, HANDLE> || std::same_as<T, HMODULE> || std::same_as<T, HKEY>;

template<HandleType T, typename Deleter>
class UniqueHandle
{
public:
    UniqueHandle(T handle, Deleter deleter) : _handle(handle), _deleter(std::move(deleter))
    {
    }

    UniqueHandle(const UniqueHandle&) = delete;

    UniqueHandle(UniqueHandle&& rhs) noexcept : _handle(rhs._handle), _deleter(std::move(rhs._deleter))
    {
        rhs._handle = nullptr;
    }

    UniqueHandle& operator=(const UniqueHandle&) = delete;

    UniqueHandle& operator=(UniqueHandle&& rhs) noexcept
    {
        if (this != &rhs)
        {
            Release();

            _handle = rhs._handle;
            _deleter = std::move(rhs._deleter);

            rhs._handle = nullptr;
        }

        return *this;
    }

    ~UniqueHandle()
    {
        Release();
    }

    bool operator==(T other) const noexcept
    {
        return _handle == other;
    }

    const T& Get() const noexcept
    {
        return _handle;
    }

    void Reset(T handle)
    {
        Release();

        _handle = handle;
    }

private:

    void Release()
    {
        if (_handle != nullptr && _handle != INVALID_HANDLE_VALUE)
        {
            _deleter(_handle);
        }

        _handle = nullptr;
    }

    T _handle;
    Deleter _deleter;
};