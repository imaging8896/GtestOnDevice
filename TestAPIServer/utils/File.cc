#include <string>

extern "C" {
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
}

#include "File.h"

using namespace std;
using namespace Test;

File::File(const string path) {
	_path = path;
}

bool File::isExists() {
	//Ensure a trailing / in the directory name
	if(access((_path + "/").c_str(), F_OK) != 0) {
		if(errno == ENOENT)
			return false;
	}
	return true;
}

int File::getFileType() {
	struct stat info;
	if(stat(_path.c_str(), &info) != 0){
		_errorMsg = strerror(errno);
		return -1;
	} else if(S_ISSOCK(info.st_mode))
		return File::SOCKET;
	else if(S_ISLNK(info.st_mode))
		return File::LINK;
	else if(S_ISREG(info.st_mode))
		return File::FILE;
	else if(S_ISBLK(info.st_mode))
		return File::BLOCK;
	else if(S_ISDIR(info.st_mode))
		return File::DIR;
	else if(S_ISCHR(info.st_mode))
		return File::CHAR;
	else if(S_ISFIFO(info.st_mode))
		return File::FIFO;
	return -1;
}

bool File::mkdir_if_not_exists() {
	if(this->isExists()) {
		if(this->getFileType() != File::DIR) {
			_errorMsg = "File exists but not directory";
			return false;
		}
		return true;
	} else
		return this->mkdir();
}

bool File::mkdirs() {
	bool isSuccess = false;
	if(!this->isExists()) {
		string cmd = "mkdir -m u+rwx -p " + _path;
		system(cmd.c_str());
		if(!this->isExists())
			_errorMsg = "Fail to mkdir (" + _path + ")";
		else
			isSuccess = true;
	} else
		_errorMsg = "File(" + _path + ") exists.";
	return isSuccess;
}


bool File::mkdir() {
	bool isSuccess = false;
	if(!this->isExists()) {
		string cmd = "mkdir -m u+rwx " + _path;
		system(cmd.c_str());
		if(!this->isExists())
			_errorMsg = "Fail to mkdir (" + _path + ")";
		else
			isSuccess = true;
	} else
		_errorMsg = "File(" + _path + ") exists.";
	return isSuccess;
}

bool File::rm_r() {
	if(this->isExists() && this->getFileType() != File::DIR) {
		_errorMsg = "File(" + _path + ") is not directory";
		return false;
	}

	string cmd = "rm -rf " + _path;
	system(cmd.c_str());
	return !this->isExists();
}
