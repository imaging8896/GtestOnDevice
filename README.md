- jni/
	
		- Compile gtest with NDK 

- TestAPIServer/

		- main.cc 						: Test main function, global setup and global teardown.(Add listener or command line option)
		- include/HCFS_api.h 			: (header of tested shared object on device)HCFS API header
		- include/jansson.h 			: (header of helper shared object on device)jansson header for parse json
		- include/jansson_config.h 		: (header of helper shared object on device)jansson header for parse json
		- include/API_wrapper.h 		: Test API wrapper for logging every invokation
		- include/garbageCollection.h 	: Auto cleanup utils, call clean all at 'global teardown' 
		- utils/ 						: Test tool implementations
		- TestCases/*.cc				: Test cases. Each class in cc file is single test suite

- Note
add to TEST() {}
//RecordProperty("MinimumWidgets", ComputeMinUsage());
//<testcase name="MinAndMaxWidgets" status="run" time="6" classname="WidgetUsageTest" MaximumWidgets="12" MinimumWidgets="9" />
