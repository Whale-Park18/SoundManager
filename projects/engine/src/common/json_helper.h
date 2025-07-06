#pragma once
#include "logger.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <optional>
#include <variant>
#include <format>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/prettywriter.h>

namespace engine::common::json_helper
{
	enum class ErrorCode
	{
		None,
		FileNotFound,
		FileOpenError,
		JsonParseError
	};

	using document = std::variant<ErrorCode, rapidjson::Document>;

	inline document LoadJsonFromFile(const std::filesystem::path& filePath)
	{
		if (std::filesystem::exists(filePath) == false)
		{
			Logger::Instance().Error(std::format("File not found: {}", filePath.string()));
			return ErrorCode::FileNotFound;
		}

		std::ifstream ifs{ filePath };
		if (ifs.is_open() == false)
		{
			Logger::Instance().Error(std::format("File open error: {}", filePath.string()));
			return ErrorCode::FileOpenError;
		}

		rapidjson::IStreamWrapper isw{ ifs };
		rapidjson::Document document;
		document.ParseStream(isw);

		if (document.HasParseError())
		{
			Logger::Instance().Error(std::format("JSON parse error: {}", static_cast<int>(document.GetParseError())));
			return ErrorCode::JsonParseError;
		}

		return document;
	}

	inline ErrorCode SaveJsonToFile(const std::filesystem::path& filePath, const rapidjson::Document& document)
	{
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		std::ofstream ofs{ filePath };
		if (!ofs.is_open())
		{
			Logger::Instance().Error(std::format("File open error: {}", filePath.string()));
			return ErrorCode::FileOpenError;
		}
		ofs << buffer.GetString();
		ofs.close();
		
		return ErrorCode::None;
	}
}