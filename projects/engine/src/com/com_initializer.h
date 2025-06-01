#pragma once
#include <stdexcept>
#include <objbase.h>
#include <roapi.h>

#pragma comment(lib, "ole32.lib")

namespace engine::com
{
	struct ComInitializer
	{
		ComInitializer(tagCOINIT tagCoInit = COINIT_MULTITHREADED)
		{
			HRESULT hr = CoInitializeEx(nullptr, tagCoInit);
			if (FAILED(hr))
			{
				throw std::runtime_error("Failed to initialize COM library.");
			}
		}

		~ComInitializer()
		{
			CoUninitialize();
		}
	};
} // namespace engine::com