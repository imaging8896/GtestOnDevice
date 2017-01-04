# Project of test on device using googletest framework
## Feature
* test cases management : 
	test cases are in TestAPIServer/TestCases as '*.cc'. You can rename folder but need to modify `jni/Android.mk`
* unit test for test utils :
	every file name with prefix 'test' in `unittest/` is unit test test cases. 

## Project structure
- jni/ : Compile gtest with NDK 
- TestAPIServer/ : can be rename for your appreciated
	* main.cc : Test main function, global setup and global teardown.(Add listener or command line option)
	* include/ : Header for test tool or shared object
		* HCFS_api.h 			: (header of tested shared object on device)HCFS API header
		* jansson.h 			: (header of helper shared object on device)jansson header for parse json
		* jansson_config.h 		: (header of helper shared object on device)jansson header for parse json
		* API_wrapper.h 		: Test API wrapper for logging every invokation
		* garbageCollection.h 	: Auto cleanup utils, call clean all at 'global teardown' 
	* utils/ : Test tool implementations
	* TestCases/ : Test cases. Each class in cc file is single test suite

- Note
add to TEST() {}
//RecordProperty("MinimumWidgets", ComputeMinUsage());
//<testcase name="MinAndMaxWidgets" status="run" time="6" classname="WidgetUsageTest" MaximumWidgets="12" MinimumWidgets="9" />
