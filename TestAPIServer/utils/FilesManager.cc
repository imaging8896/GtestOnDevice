#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

extern "C" {
#include <stdlib.h>
}

#include "FilesManager.h"

using namespace std;
using namespace Test;

string getPathInLevel(string fromePath, string name, int level);
bool writeFile(string filePath, long size, char* fillData);
void genRandom(char *s, const int len, int seed);

FilesManager::FilesManager(string path, string newDirName) {
	_rootDir = new File(path + "/" + newDirName);
	_fileNum = 0;

	genRandom(fillData1, sizeof(fillData1), FilesManager::RAND_SEED_DATA1);
	genRandom(fillData2, sizeof(fillData2), FilesManager::RAND_SEED_DATA2);
}

FilesManager::~FilesManager() {
	delete _rootDir;
}

bool FilesManager::init() {
	if(!_rootDir->rm_r()) {
		_errorMsg = _rootDir->getErrorMsg();
		return false;
	}
	if(!_rootDir->mkdir()) {
		_errorMsg = "Cannot create folder(" + _rootDir->getPath() + ")";
		return false;
	}
	return true;
}

bool FilesManager::cleanup() {
	return cleanFiles();
}

bool FilesManager::cleanFiles() {
	return _rootDir->rm_r();
}

bool FilesManager::genFilesSequentWrite(int fileNum, long size) {
	bool isSuccess = true;
	_fileNum = fileNum;
	string dirpaht;
	for(int i = 0; i < fileNum; i++) {
		if(!writeFile(this->getFilePathById(i), size, fillData1)) {
			_errorMsg = "Cannot write file(" + this->getFilePathById(i) + ")";
			isSuccess = false;
			break;
		}
	}
	return isSuccess;
}

/**
 * return empty string for error
 */
string FilesManager::createDirInLevel(string name, int level) {
	string path = "";
	if(level > 0) {
		path = getPathInLevel(_rootDir->getPath(), name, level);
		File file (path);
	
		if(!file.mkdirs()) {
			ostringstream ss;
			ss << "Fail to mkdirs with path(" << path << ") level(" << level << ")";
			_errorMsg = file.getErrorMsg();
			path = "";
		}
	} else 
		_errorMsg = "'level' should > 0";
	return path;
}

string getPathInLevel(string fromePath, string name, int level) {
	ostringstream ss;
	ss << fromePath;
	for (int i = 1; i <= level; i++)
		ss << "/dir" << i;
	ss << "/" << name;
	return ss.str();
}

string FilesManager::getFilePathById(int id) {
	ostringstream ss;
	ss << id;
	return _rootDir->getPath() + "/" + ss.str() + ".file";
}

bool writeFile(string filePath, long size, char* fillData) {
	ofstream fout (filePath.c_str(), ios::out | ios::binary | ios::trunc); 
	long curSize = size;
	if (fout.is_open()) {
		while (curSize >= FilesManager::FILL_BLOCK_SIZE) {
			fout << fillData;
			curSize -= FilesManager::FILL_BLOCK_SIZE;
		}
		fout.write(fillData, curSize);
		fout.close();
		return true;
	} else
		return false;
}

void genRandom(char *s, const int len, int seed) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

	srand(seed);
    for (int i = 0; i < len; i++)
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

    s[len] = 0;
}
