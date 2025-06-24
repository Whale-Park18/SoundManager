#pragma once
#include <string>
#include <string_view>
#include <sstream>

namespace engine::common
{
#ifdef UNICODE
	using tstring = std::wstring;
	using tstring_view = std::wstring_view;
	using tstringstream = std::wstringstream;
	using tistringstream = std::wistringstream;
	using tostringstream = std::wostringstream;
#else
	using tstring = std::string;
	using tstring = std::string_view;
	using tstringstream = std::stringstream;
	using tistringstream = std::istringstream;
	using tostringstream = std::ostringstream;
#endif
}