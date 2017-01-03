#include <gtest/gtest.h>

extern "C"
{
#include "API_wrapper.h"
}

#include "FilesManager.h"

#define SYNCPOINT_CLEARED 0
#define NO_SYNCPOINT 1

#define TEST_PATH "/storage/emulated/0"
#define TEST_DIR_NAME "apiServerTestDir"
#define TEST_DIR "/storage/emulated/0/apiServerTestDir"

using namespace Test;

class NormalCases : public testing::Test {
	protected:
    	FilesManager* filesMgr;

	virtual void SetUp() {
		filesMgr = new FilesManager(TEST_PATH, TEST_DIR_NAME);
		filesMgr->init();
	}

	virtual void TearDown() {
		filesMgr->cleanup();
		free(filesMgr);
	}

};

TEST_F(NormalCases, dirCase) {
	const int fileNum = 20;
	const long fileSize = 2 * 1024 * 1024;
	char* testDir = TEST_DIR;
	filesMgr->genFilesSequentWrite(fileNum, fileSize);

	ResultPtr result = hcfs_api->HCFS_dir_status(testDir);
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);
	ASSERT_EQ(0, result->code);
	ASSERT_FALSE(result->data->isEmpty);

	DirStatusPtr dirStatus = (DirStatusPtr) result->data->actualData;
	ASSERT_EQ(fileNum, dirStatus->num_local + dirStatus->num_cloud + dirStatus->num_hybrid);
}

TEST_F(NormalCases, manyLevelsDirCase) {
	const int fileNum = 20;
	const long fileSize = 2 * 1024 * 1024;
	char* testDir = TEST_DIR;
	filesMgr->genFilesSequentWrite(fileNum, fileSize);

	ResultPtr result = hcfs_api->HCFS_dir_status(testDir);
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);
	ASSERT_EQ(0, result->code);
	ASSERT_FALSE(result->data->isEmpty);

	DirStatusPtr dirStatus = (DirStatusPtr) result->data->actualData;
	ASSERT_EQ(fileNum, dirStatus->num_local + dirStatus->num_cloud + dirStatus->num_hybrid);
}
