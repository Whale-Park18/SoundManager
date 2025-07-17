#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <optional>

#include <rapidjson/document.h>

namespace engine::data
{
	namespace preset_json_keys
	{
		inline constexpr std::string_view presetList{ "presetList" };
		inline constexpr std::string_view name{ "name" };
		inline constexpr std::string_view volume{ "volume" };
		inline constexpr std::string_view appList{ "appList" };
	}

	struct App
	{
		std::string name;
		float volume = 0.0f;
	};

	struct Preset
	{
		std::string name;
		float systemVolume = 0.0f;
		std::vector<App> appPresetList;
	};

	class PresetJsonConverter
	{
	public:
		PresetJsonConverter(std::filesystem::path presetJsonPath = "");
		virtual ~PresetJsonConverter() = default;

		void SetPresetJsonPath(std::filesystem::path&& presetJsonPath);
		const std::vector<Preset>& GetPresetList() const { return _presetList; }
		
		/// <summary>
		/// 직렬화(Json to variable)를 수행합니다.
		/// </summary>
		/// <returns>직렬화 성공 유무</returns>
		bool Serialize();

		/// <summary>
		/// 역직렬화(Variable to Json)를 수행합니다.
		/// </summary>
		/// <returns>역직렬화 성공 유무</returns>
		bool Deserialize();

		/// <summary>
		/// 프리셋을 추가하고 해당 프리셋의 인덱스를 반환합니다.
		/// </summary>
		/// <param name="preset">추가할 Preset 객체에 대한 상수 참조</param>
		/// <returns>추가된 프리셋의 인덱스</returns>
		std::size_t AddPreset(Preset&& preset);

		/// <summary>
		/// 지정된 인덱스에 해당하는 프리셋을 삭제합니다.
		/// </summary>
		/// <param name="index">삭제할 프리셋의 인덱스</param>
		bool DeletePreset(const std::size_t index);

		/// <summary>
		/// 지정된 프리셋 인덱스에 앱을 추가하고, 추가된 앱의 인덱스를 반환합니다.
		/// </summary>
		/// <param name="presetIndex">앱을 추가할 프리셋의 인덱스입니다.</param>
		/// <param name="app">추가할 App 객체입니다.</param>
		/// <returns>추가된 앱의 인덱스(크기_t 타입)를 반환합니다.</returns>
		std::size_t AddApp(const std::size_t presetIndex, App&& app);

		/// <summary>
		/// 지정된 프리셋 인덱스와 앱 인덱스에 해당하는 앱을 삭제합니다.
		/// </summary>
		/// <param name="presetIndex"></param>
		/// <param name="appIndex"></param>
		bool DeleteApp(const std::size_t presetIndex, const std::size_t appIndex);

	private:

		/// <summary>
		/// 주어진 rapidjson::Document가 유효한 프리셋 JSON인지 확인합니다.
		/// </summary>
		/// <param name="doc">검사할 rapidjson::Document 객체에 대한 상수 참조입니다.</param>
		/// <returns>프리셋 JSON이 유효하면 true, 그렇지 않으면 false를 반환합니다.</returns>
		bool IsValidPresetJson(const rapidjson::Document& doc) const;

		template<typename T>
		bool ExistsName(const std::vector<T>& list, const T& newItem) const
		{
			// 중복된 이름이 있는지 확인
			auto iterator = std::find_if(list.begin(), list.end(),
				[&](const T& item) -> bool {
					return item.name == newItem.name;
				}
			);

			return iterator != list.end();
		}

		bool IsValidPresetIndex(const std::size_t index) const;

		bool IsValidAppIndex(const std::size_t presetIndex, const std::size_t appIndex) const;

		std::filesystem::path _presetJsonPath;
		std::vector<Preset> _presetList;
	};
}