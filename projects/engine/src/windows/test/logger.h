#pragma once
#include "../utils/unique_handle.h"

#include <cstddef>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

#include <windows.h>

namespace engine::windows::test
{
	class Logger
	{
	public:

		Logger();

		template<typename... Args>
		void Begin(std::string_view title, std::format_string<Args...> fmt, Args&&... args)
		{
			if(_hConsole == nullptr || _hConsole == INVALID_HANDLE_VALUE)
			{
				std::cerr << "Failed to get console handle." << std::endl;
				return;
			}

			_enableDepth = true;

			SetColor(Color::Yellow);
			std::cout << std::format("[{}] ", title);
			
			SetColor(Color::White);
			std::cout << std::format(fmt, args...) << std::endl;
		}

		template<typename... Args>
		void TestLog(std::format_string<Args...> fmt, Args&&... args)
		{
			if (_hConsole == nullptr || _hConsole == INVALID_HANDLE_VALUE)
			{
				std::cerr << "Failed to get console handle." << std::endl;
				return;
			}
			
			if (_enableDepth)
			{
				std::cout << "    ";
			}

			SetColor(Color::White);
			std::cout << std::format(fmt, args...) << std::endl;
		}

		template<typename... Args>
		void End(std::string_view title, std::format_string<Args...> fmt, Args&&... args)
		{
			if (_hConsole == nullptr || _hConsole == INVALID_HANDLE_VALUE)
			{
				std::cerr << "Failed to get console handle." << std::endl;
				return;
			}
			
			_enableDepth = false;

			SetColor(Color::Yellow);
			std::cout << std::format("[{}] ", title);

			SetColor(Color::White);
			std::cout << std::format(fmt, args...) << std::endl;
		}

	private:

		enum class Color
		{
			Black = NULL,
			Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
			Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
			Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
			White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
		};

		void SetColor(Color color)
		{
			if (_hConsole == nullptr || _hConsole == INVALID_HANDLE_VALUE)
			{
				return;
			}

			SetConsoleTextAttribute(_hConsole.Get(), static_cast<WORD>(color));
		}

		bool _enableDepth;
		UniqueHandle<HANDLE, decltype(&CloseHandle)> _hConsole{ nullptr, CloseHandle };
	};
}