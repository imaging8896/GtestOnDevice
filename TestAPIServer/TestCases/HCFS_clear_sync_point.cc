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

using namespace Test;

class HCFS_clear_sync_point : public testing::Test {
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

TEST_F(HCFS_clear_sync_point, checkAPISpecCase) {
	ResultPtr result = hcfs_api->HCFS_clear_sync_point();
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);
	ASSERT_TRUE(result->code == 0 || result->code == 1);
	ASSERT_TRUE(result->data->isEmpty);
}

TEST_F(HCFS_clear_sync_point, cancelUnsetSyncPointCase) {
	ResultPtr result = hcfs_api->HCFS_clear_sync_point();
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);

	result = hcfs_api->HCFS_clear_sync_point();
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);
	ASSERT_EQ(NO_SYNCPOINT, result->code);
	ASSERT_TRUE(result->data->isEmpty);
}

TEST_F(HCFS_clear_sync_point, cancelSyncPointCase) {
	const int fileNum = 10;
	const long fileSize = 2 * 1024 * 1024;
	filesMgr->genFilesSequentWrite(fileNum, fileSize);

	ResultPtr result = hcfs_api->HCFS_set_sync_point();
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);

	result = hcfs_api->HCFS_clear_sync_point();
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);
	ASSERT_EQ(SYNCPOINT_CLEARED, result->code);
	ASSERT_TRUE(result->data->isEmpty);
}

TEST_F(HCFS_clear_sync_point, cancelSyncPointMultiTimesCase) {
	const int testTimes = 10;
	ResultPtr result = hcfs_api->HCFS_clear_sync_point();
	ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
	ASSERT_TRUE(result->result);

	for(int i = 0; i < testTimes; i++) {
		result = hcfs_api->HCFS_clear_sync_point();
		ASSERT_TRUE(result->isCallSuccess) << result->errorMsg;
		ASSERT_TRUE(result->result);
		ASSERT_EQ(NO_SYNCPOINT, result->code);
		ASSERT_TRUE(result->data->isEmpty);
	}
}
