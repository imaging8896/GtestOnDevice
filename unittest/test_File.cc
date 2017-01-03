#include <string>
#include <gtest/gtest.h>

#include "File.h"

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

class FileTests : public testing::Test {
	public:
		static const string TEST_PATH;
		static const string TEST_DIR_NAME;
		static const string TEST_DIR;
		static const string TEST_FILE_NAME;
		static const string TEST_FILE;

		static const int DIR;
		static const int FILE;

	virtual void SetUp() {
		exec("rm -rf " + TEST_DIR);
		ASSERT_NE(0, access(TEST_DIR.c_str(), F_OK));
		exec("rm -f " + TEST_FILE);
		ASSERT_NE(0, access(TEST_FILE.c_str(), F_OK));
	}

	virtual void TearDown() {
		exec("rm -rf " + TEST_DIR);
		ASSERT_NE(0, access(TEST_DIR.c_str(), F_OK));
		exec("rm -f " + TEST_FILE);
		ASSERT_NE(0, access(TEST_FILE.c_str(), F_OK));
	}

	static void exec(string cmd) {
		system(cmd.c_str());
	}
};

static char tmp[100];
const string FileTests::TEST_PATH (realpath(".", tmp));
const string FileTests::TEST_DIR_NAME = "abcdir";
const string FileTests::TEST_DIR = FileTests::TEST_PATH + "/abcdir/";
const string FileTests::TEST_FILE_NAME = "abc.file";
const string FileTests::TEST_FILE = FileTests::TEST_PATH + "/abc.file";

const int FileTests::DIR = File::DIR;
const int FileTests::FILE = File::FILE;

TEST_F(FileTests, dirCase) {
	File dir(TEST_DIR);
	ASSERT_FALSE(dir.isExists());
	exec("mkdir " + TEST_DIR);
	ASSERT_TRUE(dir.isExists());
	ASSERT_EQ(DIR, dir.getFileType());
	ASSERT_STREQ(TEST_DIR.c_str(), dir.getPath().c_str());
}

TEST_F(FileTests, fileCase) {
	File file(TEST_FILE);
	ASSERT_FALSE(file.isExists());
	exec("touch " + TEST_FILE);
	ASSERT_TRUE(file.isExists()) << strerror(errno);
	ASSERT_EQ(FILE, file.getFileType());
	ASSERT_STREQ(TEST_FILE.c_str(), file.getPath().c_str());
}

TEST_F(FileTests, mkdirIfNotExistsCase) {
	File dir(TEST_DIR);

	ASSERT_TRUE(dir.mkdir_if_not_exists()) << dir.getErrorMsg();
	ASSERT_TRUE(dir.isExists());
	ASSERT_EQ(DIR, dir.getFileType());
	ASSERT_STREQ(TEST_DIR.c_str(), dir.getPath().c_str());

	ASSERT_TRUE(dir.mkdir_if_not_exists()) << dir.getErrorMsg();
	ASSERT_TRUE(dir.isExists());
	ASSERT_EQ(DIR, dir.getFileType());
	ASSERT_STREQ(TEST_DIR.c_str(), dir.getPath().c_str());
}

TEST_F(FileTests, mkdirCase) {
	File dir(TEST_DIR);

	ASSERT_TRUE(dir.mkdir()) << dir.getErrorMsg();
	ASSERT_TRUE(dir.isExists());
	ASSERT_EQ(DIR, dir.getFileType());
	ASSERT_STREQ(TEST_DIR.c_str(), dir.getPath().c_str());

	ASSERT_FALSE(dir.mkdir());
	string expectedMsg = "File(" + TEST_DIR + ") exists.";
	ASSERT_STREQ(expectedMsg.c_str(), dir.getErrorMsg().c_str());
}
