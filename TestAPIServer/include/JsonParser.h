#ifndef TEST_JSON_PARSER_H_
#define TEST_JSON_PARSER_H_

#include "API_wrapper.h"

ResultPtr parse(char* json_str);
ResultPtr parseDirStatus(char* json_str);

#endif  /* TEST_JSON_PARSER_H_ */
