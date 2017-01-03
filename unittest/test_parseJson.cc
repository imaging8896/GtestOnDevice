#include <string>
#include <gtest/gtest.h>

extern "C" {
#include <stdlib.h>
#include <string.h>
}


#include "JsonParser.h"

using namespace std;

TEST(ParseTests, parseCase) {
	string json = "{\"result\": true,\"code\": 0,\"data\": {}}";
	char* json_c_str = (char *) malloc(json.length() + 1);
	strncpy(json_c_str, json.c_str(), json.length() + 1);

	ResultPtr result = parse(json_c_str);
	ASSERT_TRUE(result->isCallSuccess) << string(result->errorMsg);
	ASSERT_STREQ("", result->errorMsg);
	ASSERT_STREQ(json_c_str, result->json_res);
	ASSERT_TRUE(result->result);
	ASSERT_EQ(0, result->code);
	ASSERT_TRUE(result->data->isEmpty);
}

TEST(ParseTests, parseDirStatusCase) {
	string json = "{\"result\": true,\"code\": 0,\"data\": {\"num_local\": 1, \"num_cloud\": 2, \"num_hybrid\": 3}}";
	char* json_c_str = (char *) malloc(json.length() + 1);
	strncpy(json_c_str, json.c_str(), json.length() + 1);

	ResultPtr result = parseDirStatus(json_c_str);
	ASSERT_TRUE(result->isCallSuccess) << string(result->errorMsg);
	ASSERT_STREQ("", result->errorMsg);
	ASSERT_STREQ(json_c_str, result->json_res);
	ASSERT_TRUE(result->result);
	ASSERT_EQ(0, result->code);
	ASSERT_FALSE(result->data->isEmpty);

	DirStatusPtr dirStatus = (DirStatusPtr) result->data->actualData;
	ASSERT_EQ(1, dirStatus->num_local);
	ASSERT_EQ(2, dirStatus->num_cloud);
	ASSERT_EQ(3, dirStatus->num_hybrid);
}
