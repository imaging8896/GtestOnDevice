#include <string>

#include "File.h"

using namespace std;

namespace Test { 

	//For linux only
	class FilesManager
	{
	public:
		static const int FILL_BLOCK_SIZE = 1048576;
    	static const int RAND_SEED_DATA1 = 40;
		static const int RAND_SEED_DATA2 = 50;
		static const int FILL_DATA_TYPE1 = 1;
		static const int FILL_DATA_TYPE2 = 2;

 		FilesManager(const string path, const string newDirName);
		~FilesManager();
		
		bool init();
		bool cleanup();

		bool cleanFiles();

		bool genFilesSequentWrite(int fileNum, long size);

		string createDirInLevel(string name, int level);
		string getFilePathById(int id);

		string getRoot() { return _rootDir->getPath(); }
		string getErrorMsg() { return _errorMsg; }

	private:
		File* _rootDir;
		string _errorMsg;
		int _fileNum;
		char fillData1[FILL_BLOCK_SIZE];
		char fillData2[FILL_BLOCK_SIZE];
	};
};

