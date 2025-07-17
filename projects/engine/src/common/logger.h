#pragma once
#include <iostream>
#include <string_view>

#include <spdlog/spdlog.h>

namespace engine::common
{
	class Logger
	{
	public:
		static const Logger& Instance()
		{
			static Logger instance;
			return instance;
		}

		void Trace(const std::string_view message) const
		{
			std::cout << message << std::endl;
			//spdlog::trace(message);
		}

		void Debug(const std::string_view message) const
		{
			std::cout << message << std::endl;
			//spdlog::debug(message);
		}

		void Error(const std::string_view message) const
		{
			std::cerr << message << std::endl;
			//spdlog::error(message);
		}

	private:
		Logger() = default;
		virtual ~Logger() = default;


	};
}