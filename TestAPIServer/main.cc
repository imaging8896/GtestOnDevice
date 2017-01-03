#include <gtest/gtest.h>

#include "API_wrapper.h"

class TestEnvironment : public testing::Environment {

	public:
		// Override this to define how to set up the environment.
		virtual void SetUp() {
			init_wrapper();
		}
		// Override this to define how to tear down the environment.
		virtual void TearDown() {
			cleanup_wrapper();
		}
};

int main(int argc, char **argv) {
	printf("Running main() from TestCases/main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	testing::AddGlobalTestEnvironment(new TestEnvironment);
	return RUN_ALL_TESTS();
}
