#include "preset_json_converter.h"
#include "../common/json_helper.h"
#include "../common/logger.h"

#include <fstream>
#include <format>

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>

using namespace engine::common;

engine::data::PresetJsonConverter::PresetJsonConverter(std::filesystem::path presetJsonPath) : 
	_presetJsonPath(std::move(presetJsonPath))
{
}

bool engine::data::PresetJsonConverter::Serialize()
{
	// 파일 로드
	auto docVariant = json_helper::LoadJsonFromFile(_presetJsonPath);
	if(std::holds_alternative<json_helper::ErrorCode>(docVariant))
	{
		Logger::Instance().Error(std::format("Failed to load JSON file: {}", _presetJsonPath.string()));
		return false;
	}

	// JSON 문서가 유효한지 검사
	auto& document = std::get<rapidjson::Document>(docVariant);
	if(IsValidPresetJson(document) == false)
	{
		Logger::Instance().Error(std::format("Invalid JSON format in file: {}", _presetJsonPath.string()));
		return false;
	}

	// Preset 리스트를 순회하며 Preset 객체 생성
	const auto& presetListJson = document[preset_json_keys::presetList.data()];
	for (const auto& presetJson : presetListJson.GetArray())
	{
		// Preset 객체 생성
		Preset preset = {
			.name = presetJson[preset_json_keys::name.data()].GetString(),
			.systemVolume = presetJson[preset_json_keys::volume.data()].GetFloat(),
		};

		// App 리스트를 순회하며 App 객체 생성
		const auto& appListJson = presetJson[preset_json_keys::appList.data()];
		for(const auto& appJson : appListJson.GetArray())
		{
			// App 객체 생성
			App app = {
				.appName = appJson[preset_json_keys::name.data()].GetString(),
				.appVolume = appJson[preset_json_keys::volume.data()].GetFloat(),
			};
			preset.appPresetList.push_back(app);
		}

		_presetList.push_back(preset);
	}

	return true;
}

bool engine::data::PresetJsonConverter::Deserialize()
{
	// 파일이 비어있어있어 변환할 내용이 없는 경우
	if(_presetList.empty())
	{
		Logger::Instance().Error(std::format("No presets is empty"));
		return false;
	}

	// JSON 문서 생성
	rapidjson::Document doccument;
	doccument.SetObject();
	rapidjson::Document::AllocatorType& allocator = doccument.GetAllocator();

	// Preset 리스트를 JSON으로 변환
	for(const auto& preset : _presetList)
	{
		// Preset 객체를 JSON으로 변환
		rapidjson::Value presetJson(rapidjson::kObjectType);
		presetJson.AddMember(rapidjson::StringRef(preset_json_keys::name.data()), rapidjson::Value(preset.name.c_str(), allocator), allocator);
		presetJson.AddMember(rapidjson::StringRef(preset_json_keys::volume.data()), preset.systemVolume, allocator);

		// App 리스트를 JSON으로 변환
		rapidjson::Value appListJson(rapidjson::kArrayType);
		for(const auto& app : preset.appPresetList)
		{
			// App 객체를 JSON으로 변환
			rapidjson::Value appJson(rapidjson::kObjectType);
			appJson.AddMember(rapidjson::StringRef(preset_json_keys::name.data()), rapidjson::Value(app.appName.c_str(), allocator), allocator);
			appJson.AddMember(rapidjson::StringRef(preset_json_keys::volume.data()), app.appVolume, allocator);
			appListJson.PushBack(appJson, allocator);
		}
		presetJson.AddMember(rapidjson::StringRef(preset_json_keys::appList.data()), appListJson, allocator);
		
		doccument.AddMember(rapidjson::StringRef(preset_json_keys::presetList.data()), presetJson, allocator);
	}

	// JSON 문서를 파일로 저장
	json_helper::SaveJsonToFile(_presetJsonPath, doccument);

	return true;
}

std::size_t engine::data::PresetJsonConverter::AddPreset(Preset& preset)
{
	_presetList.push_back(std::move(preset));

	return _presetList.size() - 1; // 새로 추가된 프리셋의 인덱스 반환
}

void engine::data::PresetJsonConverter::DeletePreset(const std::size_t index)
{
	if(IsInvalidPresetIndex(index))
	{
		return;
	}

	_presetList.erase(_presetList.begin() + index);
}

std::size_t engine::data::PresetJsonConverter::AddApp(const std::size_t presetIndex, App& app)
{
	if(IsInvalidPresetIndex(presetIndex))
	{
		return std::size_t();
	}

	_presetList.at(presetIndex).appPresetList.push_back(std::move(app));

	return _presetList.at(presetIndex).appPresetList.size() - 1; // 새로 추가된 앱의 인덱스 반환
}

void engine::data::PresetJsonConverter::DeleteApp(const std::size_t presetIndex, const std::size_t appIndex)
{
	if(IsInvalidAppIndex(presetIndex, appIndex))
	{
		return;
	}

	_presetList.at(presetIndex).appPresetList.erase(_presetList.at(presetIndex).appPresetList.begin() + appIndex);
}

bool engine::data::PresetJsonConverter::IsValidPresetJson(const rapidjson::Document& document) const
{
	bool isObject = document.IsObject();
	bool hasPresetList = document.HasMember(preset_json_keys::presetList.data());
	bool isArray = document[preset_json_keys::presetList.data()].IsArray();
	
	return isObject && hasPresetList && isArray;
}

bool engine::data::PresetJsonConverter::IsInvalidPresetIndex(const std::size_t index) const
{
	return 0 < index || index <= _presetList.size();
}

bool engine::data::PresetJsonConverter::IsInvalidAppIndex(const std::size_t presetIndex, const std::size_t appIndex) const
{
	if (IsInvalidPresetIndex(presetIndex))
	{
		return false;
	}
	
	return 0 < appIndex || appIndex <= _presetList.at(presetIndex).appPresetList.size();
}
