#include <string>
#include <gtest/gtest.h>

#include "FilesManager.h"

extern "C" {
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
}

using namespace Test;

void exec(string cmd);

class FilesManagerTests : public testing::Test {
	public:
		static const string TEST_PATH;
		static const string TEST_DIR_NAME;
		static const string TEST_DIR;

	protected:
    	FilesManager* filesMgr;

	virtual void SetUp() {
		exec("rm -rf " + TEST_DIR);
		ASSERT_NE(0, access(TEST_DIR.c_str(), F_OK));

		filesMgr = new FilesManager(TEST_PATH, TEST_DIR_NAME);
	}

	virtual void TearDown() {
		filesMgr->cleanup();
		delete filesMgr;

		exec("rm -rf " + TEST_DIR);
		ASSERT_NE(0, access(TEST_DIR.c_str(), F_OK));
	}

	static int countEntriesInDir(const char* dirname) {
		int n=0;
		dirent* dentry;
		DIR* dir = opendir(dirname);
		if (dir == NULL) return 0;
		while((dentry = readdir(dir))!=NULL) {
			if(strcmp(dentry->d_name, ".") != 0 && strcmp(dentry->d_name, "..") != 0) n++;
		}
		closedir(dir);
		return n;
	}

	static void exec(string cmd) {
		system(cmd.c_str());
	}
};

class FilesManagerCleanupTests : public FilesManagerTests {

	virtual void TearDown() {
		delete filesMgr;

		exec("rm -rf " + TEST_DIR);
		ASSERT_NE(0, access(TEST_DIR.c_str(), F_OK));
	}

};

static char tmp[100];
const string FilesManagerTests::TEST_PATH (realpath(".", tmp));
const string FilesManagerTests::TEST_DIR_NAME = "abcdir";
const string FilesManagerTests::TEST_DIR = FilesManagerTests::TEST_PATH + "/abcdir/";

TEST_F(FilesManagerTests, initCase) {
	ASSERT_TRUE(filesMgr->init()) << filesMgr->getErrorMsg();
	ASSERT_EQ(0, access(TEST_DIR.c_str(), F_OK));
	ASSERT_EQ(0, countEntriesInDir(TEST_DIR.c_str()));
}

TEST_F(FilesManagerTests, initExistsCase) {
	exec("mkdir " + TEST_DIR + " && cd " + TEST_DIR + " && touch 1");
	ASSERT_EQ(0, access(TEST_DIR.c_str(), F_OK));
	ASSERT_EQ(1, countEntriesInDir(TEST_DIR.c_str()));

	ASSERT_TRUE(filesMgr->init()) << filesMgr->getErrorMsg();
	ASSERT_EQ(0, access(TEST_DIR.c_str(), F_OK));
	ASSERT_EQ(0, countEntriesInDir(TEST_DIR.c_str()));
}

TEST_F(FilesManagerTests, genSeqFilesCase) {
	const int fileNum = 3;
	const long fileSize = 1024;

	ASSERT_TRUE(filesMgr->init()) << filesMgr->getErrorMsg();
	
	ASSERT_TRUE(filesMgr->genFilesSequentWrite(fileNum, fileSize)) << filesMgr->getErrorMsg();
	ASSERT_EQ(0, access(TEST_DIR.c_str(), F_OK));
	ASSERT_EQ(3, countEntriesInDir(TEST_DIR.c_str()));
	
	dirent* dentry;
	struct stat st;
	DIR* dir = opendir(TEST_DIR.c_str());
	ASSERT_FALSE(dir == NULL);
	while((dentry = readdir(dir)) != NULL) {
		if(strcmp(dentry->d_name, ".") != 0 && strcmp(dentry->d_name, "..") != 0) {
			string fileName(dentry->d_name);
			ASSERT_EQ(0, stat((TEST_DIR + "/" + fileName).c_str(), &st));
			ASSERT_EQ(fileSize, st.st_size);
		}
	}
	closedir(dir);
	
}

TEST_F(FilesManagerTests, createDirInLevelCase) {
	const int level = 12;
	const string dirName = "testDir";
	const string fullPath = TEST_DIR + "dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8/dir9/dir10/dir11/dir12/" + dirName;

	ASSERT_TRUE(filesMgr->init()) << filesMgr->getErrorMsg();
	
	string path = filesMgr->createDirInLevel(dirName, level);
	ASSERT_FALSE(path.empty());
	ASSERT_STREQ(fullPath.c_str(), path.c_str());
}

TEST_F(FilesManagerTests, createExistedDirInLevelCase) {
	const int level = 12;
	const string dirName = "testDir";
	const string fullPath = TEST_DIR + "dir1/dir2/dir3/dir4/dir5/dir6/dir7/dir8/dir9/dir10/dir11/dir12/" + dirName;

	ASSERT_TRUE(filesMgr->init()) << filesMgr->getErrorMsg();
	
	string path = filesMgr->createDirInLevel(dirName, level);
	ASSERT_FALSE(path.empty());

	path = filesMgr->createDirInLevel(dirName, level);
	ASSERT_TRUE(path.empty());
	string expectedErrMsg = "File(" + fullPath + ") exists.";
	ASSERT_STREQ(expectedErrMsg.c_str(), filesMgr->getErrorMsg().c_str());
}

TEST_F(FilesManagerTests, createDirInLevel0Case) {
	const int level = 0;
	const string dirName = "testDir";

	string path = filesMgr->createDirInLevel(dirName, level);
	ASSERT_TRUE(path.empty());
	string expectedErrMsg = "'level' should > 0";
	ASSERT_STREQ(expectedErrMsg.c_str(), filesMgr->getErrorMsg().c_str());
}

TEST_F(FilesManagerCleanupTests, cleanupCase) {
	ASSERT_TRUE(filesMgr->init()) << filesMgr->getErrorMsg();

	ASSERT_TRUE(filesMgr->cleanup()) << filesMgr->getErrorMsg();
	ASSERT_NE(0, access(TEST_DIR.c_str(), F_OK));
}
