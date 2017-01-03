- jni/
	
		- Compile with gtest

- TestAPIServer/

		- main.cc 						: Test main function, global setup and global teardown.(Add listener or command line option)
		- include/HCFS_api.h 			: HCFS API header
		- include/jansson.h 			: jansson header for parse json
		- include/jansson_config.h 		: jansson header for parse json
		- include/API_wrapper.h 		: HCFS API wrapper for logging every invokation and parse json to structure variable
		- include/garbageCollection.h 	: Auto cleanup utils, call clean all at 'global teardown' 
		- utils/ 						: Test tool implementations
		- TestCases/*.cc				: Test cases. Each class in cc file is single test suite

- Note
add to TEST() {}
//RecordProperty("MinimumWidgets", ComputeMinUsage());
//<testcase name="MinAndMaxWidgets" status="run" time="6" classname="WidgetUsageTest" MaximumWidgets="12" MinimumWidgets="9" />
