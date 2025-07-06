#include "google_test_config.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
}