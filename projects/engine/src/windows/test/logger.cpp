#include "logger.h"

engine::windows::test::Logger::Logger() : _enableDepth(false)
{
	_hConsole.Reset(GetStdHandle(STD_OUTPUT_HANDLE));
	if (_hConsole == INVALID_HANDLE_VALUE)
	{
		_hConsole.Reset(nullptr);
	}
}