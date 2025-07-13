#include "google_test_config.h"

#include <data/preset_json_converter.h>
#include <iostream>
#include <format>

namespace test_data
{
	namespace config
	{
		inline constexpr std::string_view test_in_preset_json_path{ R"(.\test_in_preset.json)" };
		inline constexpr std::string_view test_out_preset_json_path{ R"(.\test_out_preset.json)" };
	}

	namespace constants
	{
		inline constexpr std::size_t serialize_prest_count{ 2 };
		inline constexpr std::size_t serialize_preset1_app_count{ 3 };
		inline constexpr std::size_t serialize_preset2_app_count{ 1 };
		inline constexpr std::size_t failed_add_index{ static_cast<std::size_t>(-1) };
	}
}

class TestDataPresetJsonConverter : public ::testing::Test
{
protected:

	void SetUp() override
	{
		// 테스트를 위한 초기화 작업을 여기에 작성합니다.
		
		_presetJsonConverter.SetPresetJsonPath(test_data::config::test_in_preset_json_path);
		ASSERT_TRUE(_presetJsonConverter.Serialize());
	}

	void TestBody() override
	{
		// 테스트 본문을 여기에 작성합니다.
		// 예: ASSERT_TRUE(_presetJsonConverter.Serialize());
		//      ASSERT_TRUE(_presetJsonConverter.Deserialize());
		//      ASSERT_EQ(_presetJsonConverter.GetPresetList().size(), expectedSize);
	}

	void TearDown() override
	{
		// 테스트 후 정리 작업을 여기에 작성합니다.
		// 예: _presetJsonConverter.SetPresetJsonPath(TEST_OUT_PRESET_JSON_FILE);
	}

	void PrintPresetList()
	{
		auto presetList = _presetJsonConverter.GetPresetList();
		for (const auto& preset : presetList)
		{
			std::cout << std::format("Preset Name: {}, System Volume: {}\n", preset.name, preset.systemVolume);
			for (const auto& app : preset.appPresetList)
			{
				std::cout << std::format("  App Name: {}, Volume: {}\n", app.name, app.volume);
			}
		}
	}

	engine::data::PresetJsonConverter _presetJsonConverter;
};

TEST_F(TestDataPresetJsonConverter, Serialize)
{
	// TestDataPresetJsonConverter::SetUp() 메소드에서 직렬화 수행

	PrintPresetList();

	auto presetList = _presetJsonConverter.GetPresetList();
	EXPECT_EQ(presetList.size(), test_data::constants::serialize_prest_count);
}

TEST_F(TestDataPresetJsonConverter, AddPreset)
{
	auto i = _presetJsonConverter.AddPreset(
		{
			.name = "preset3",
			.systemVolume = 0.5f,
			.appPresetList = {
				{.name = "preset3_app1", .volume = 0.5f },
				{.name = "preset3_app2", .volume = 0.5f }
			}
		}
	);

	PrintPresetList();

	EXPECT_NE(i, test_data::constants::failed_add_index);
}

TEST_F(TestDataPresetJsonConverter, DeletePreset)
{
	std::size_t presetIndex = test_data::constants::serialize_prest_count - 1;

	bool isSuccess = _presetJsonConverter.DeletePreset(presetIndex);
	PrintPresetList();

	EXPECT_TRUE(isSuccess);
}

TEST_F(TestDataPresetJsonConverter, AddApp)
{
	auto i = _presetJsonConverter.AddApp(
		1,
		{ .name = "preset2_app2", .volume = 0.5f }
	);

	PrintPresetList();

	EXPECT_NE(i, test_data::constants::failed_add_index);
}

TEST_F(TestDataPresetJsonConverter, DeleteApp)
{
	std::size_t presetIndex = 0;
	std::size_t appIndex = test_data::constants::serialize_preset1_app_count - 1;

	bool isSuccess = _presetJsonConverter.DeleteApp(presetIndex, appIndex);
	PrintPresetList();

	EXPECT_TRUE(isSuccess);
}

TEST_F(TestDataPresetJsonConverter, Deserialize)
{
	PrintPresetList();

	_presetJsonConverter.SetPresetJsonPath(test_data::config::test_out_preset_json_path);
	ASSERT_TRUE(_presetJsonConverter.Deserialize());
}