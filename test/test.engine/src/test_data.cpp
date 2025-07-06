#include "google_test_config.h"

#include <data/preset_json_converter.h>

#define TEST_IN_PRESET_JSON_FILE R"(.\test_in_preset.json)"
#define TEST_OUT_PRESET_JSON_FILE R"(.\test_out_preset.json)"

class TestDataPresetJsonConverter : public ::testing::Test
{
protected:
	engine::data::PresetJsonConverter _presetJsonConverter{ TEST_IN_PRESET_JSON_FILE };
};

TEST_F(TestDataPresetJsonConverter, Serialize)
{
	ASSERT_TRUE(_presetJsonConverter.Serialize());
}

TEST_F(TestDataPresetJsonConverter, Deserialize)
{
	ASSERT_TRUE(_presetJsonConverter.Deserialize());
}