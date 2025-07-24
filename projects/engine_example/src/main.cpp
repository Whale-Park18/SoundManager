#include <iostream>
#include <thread>
#include <chrono>

#include <engine/com.h>
#include <spdlog/spdlog.h>

#pragma comment(lib, "engine64.lib")

void AudioEvedntExample()
{
	using namespace std::chrono_literals;

	try
	{
		engine::com::ComInitializer comInitializer;
		engine::com::audio::AudioManager audioManager;

		while(true)
		{
			std::this_thread::sleep_for(1s);
		}
	}
	catch (const std::exception&)
	{

	}
}

int main(int argc, char* argv[])
{
	AudioEvedntExample();

	return 0;
}