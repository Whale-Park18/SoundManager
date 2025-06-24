#pragma once
#include <filesystem>
#include <optional>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>

namespace engine::json::preset
{
	struct AppInfo
	{
		std::string appName;
		float appVolume = 0.0f;
	};
	
	struct PresetInfo
	{
		std::string name;
		float systemVolume = 0.0f;
		std::vector<AppInfo> appPresetList;
	};

	constexpr std::string_view KEY_PRESET_LIST{ "presetList" };
	constexpr std::string_view KEY_NAME{ "name" };
	constexpr std::string_view KEY_VOLUME{ "volume" };
	constexpr std::string_view KEY_APP_LIST{ "appList" };

	class PresetController
	{
	public:

		PresetController(std::filesystem::path presetJsonPath);
		virtual ~PresetController() = default;

		/**********************************************************************
		 * 인터페이스
		 **********************************************************************/

		// 프리셋
		void AddPreset();
		void DeletePreset();

		// 앱
		void AddApp();
		void DeleteApp();

		// 저장
		void Store();

	private:

		using PresetInfoList = std::vector<PresetInfo>;

		void InitializeDocument();
		void InitializePresetInfoList();

		std::filesystem::path _presetJsonpath;
		rapidjson::Document _doc; // <TODO> Json 한 번 읽고 안쓰는데 멤버 변수로 만들 이유가 있나?
		PresetInfoList _presetInfoList;
	};
}

