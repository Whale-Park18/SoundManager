#pragma once
#include <fstream>

namespace engine::common
{
#ifdef UNICODE
	using tfstreadm = std::wfstream;
	using tofstream = std::wofstream;
	using tifstream = std::wifstream;
#else
	using tfstreadm = std::fstream;
	using tofstream = std::ofstream;
	using tifstream = std::ifstream;
#endif
}
