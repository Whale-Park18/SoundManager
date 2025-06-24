#include "preset_controller.h"
#include "../../common/tstring.h"
#include "../../common/tfstream.h"

#include <rapidjson/istreamwrapper.h>

engine::json::preset::PresetController::PresetController(std::filesystem::path presetJsonPath) : _presetJsonpath(presetJsonPath)
{
	InitializeDocument();
	InitializePresetInfoList();
}
void engine::json::preset::PresetController::Store()
{
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	for (const auto& presetInfo : _presetInfoList)
	{
		rapidjson::Value preset(rapidjson::kObjectType);
		preset.AddMember(rapidjson::StringRef(KEY_NAME.data()), rapidjson::Value(presetInfo.name.c_str(), allocator), allocator);
		preset.AddMember(rapidjson::StringRef(KEY_VOLUME.data()), presetInfo.systemVolume, allocator);

		rapidjson::Value appList(rapidjson::kArrayType);
		for (const auto& appInfo : presetInfo.appPresetList)
		{
			rapidjson::Value app(rapidjson::kObjectType);
			app.AddMember(rapidjson::StringRef(KEY_NAME.data()), rapidjson::Value(appInfo.appName.c_str(), allocator), allocator);
			app.AddMember(rapidjson::StringRef(KEY_VOLUME.data()), appInfo.appVolume, allocator);
			appList.PushBack(app, allocator);
		}

		preset.AddMember(rapidjson::StringRef(KEY_APP_LIST.data()), appList, allocator);

		doc.AddMember(rapidjson::StringRef(KEY_PRESET_LIST.data()), preset, allocator);
	}
}
void engine::json::preset::PresetController::InitializeDocument()
{
	if (std::filesystem::exists(_presetJsonpath) == false)
	{
		// throw?
		return;
	}

	std::ifstream ifs{ _presetJsonpath };
	rapidjson::IStreamWrapper isw{ ifs };
	_doc.ParseStream(isw);

	if (_doc.HasParseError())
	{
		// throw?
		return;
	}
}

void engine::json::preset::PresetController::InitializePresetInfoList()
{
	// 유효성 검사
	if (!_doc.IsObject() && !_doc.HasMember(KEY_PRESET_LIST.data()) && !_doc[KEY_PRESET_LIST.data()].IsArray())
	{
		// throw?
		return;
	}

	const rapidjson::Value& presetList = _doc[KEY_PRESET_LIST.data()];
	for (const auto& preset : presetList.GetArray())
	{
		PresetInfo presetInfo = { 
			preset[KEY_NAME.data()].GetString(),
			preset[KEY_VOLUME.data()].GetFloat()
		};

		const auto& appList = preset[KEY_APP_LIST.data()];
		for (const auto& app : appList.GetArray())
		{
			AppInfo appInfo = {
				app[KEY_NAME.data()].GetString(),
				app[KEY_VOLUME.data()].GetFloat()
			};
			
			presetInfo.appPresetList.push_back(appInfo);
		}

		_presetInfoList.push_back(presetInfo);
	}
}
