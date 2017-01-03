#include <gtest/gtest.h>

extern "C"
{
	#include <HCFS_api.h>
	#include <jansson.h>
}

class NormalValueCases22 : public testing::Test {
	protected:
    	char* pkg;

	virtual void SetUp() {
		// install app
		// set package
	}

	virtual void TearDown() {
		// uninstall app
	}

};

TEST_F(NormalValueCases22, DISABLED_existsPackage) {
  bool result;
  int code;
  json_t* data;
  char* json_res = NULL;
  HCFS_get_occupied_size(&json_res);

  json_error_t* json_error;
  json_t* json_obj = json_loads(json_res, JSON_DECODE_ANY, json_error);
  ASSERT_TRUE(json_is_object(json_obj));
  json_unpack(json_obj, "{s:b, s:i, s:o}", "result", &result, "code", &code, "data", &data);

  ASSERT_TRUE(result);
  EXPECT_EQ(1, code);
  ASSERT_TRUE(json_is_object(data));
//  ASSERT_STREQ("{}", json_res);
//  EXPECT_EQ(2, foo(1, 3));
}
