#include <string>

using namespace std;

namespace Test { 

	class File {
	private:
		string _path;
		string _errorMsg;
 
	public:
		static const int SOCKET = 0;
		static const int LINK = 1;
		static const int FILE = 2;
		static const int BLOCK = 3;
		static const int DIR = 4;
		static const int CHAR = 5;
		static const int FIFO = 6;

 		File(const string path);

		bool isExists();
		int getFileType();

		bool mkdir_if_not_exists();
		bool mkdirs();
		bool mkdir();
		bool rm_r();

		string getPath() { return _path; }
		string getErrorMsg() { return _errorMsg; }
	};
};
