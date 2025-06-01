#pragma once
#include <winerror.h>

namespace engine::com
{
	template <typename T>
	struct ComResult
	{
		HRESULT result;
		T value;
	};
}