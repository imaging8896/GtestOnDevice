extern "C" {
#include <jansson.h>
#include <string.h>
}

#include "JsonParser.h"
#include "garbageCollection.h"

bool isEmpty(json_t* data) {
	json_t* empty = json_object();
	bool isEmpty = json_equal(empty, data) == 1;
	json_decref(empty);
	return isEmpty;
}

ResultPtr _parse(char* json_str, json_t** json_result, json_t** json_data) {
	ResultPtr result = (ResultPtr) malloc(sizeof(Result));
	auto_cleanup(result);
	result->isCallSuccess = true;
	strncpy(result->errorMsg, "", 1);
	
	result->json_res = json_str;
	auto_cleanup(result->json_res);
	
	json_error_t json_error;
	*json_result = json_loads(json_str, JSON_DECODE_ANY, &json_error);
	if(*json_result == NULL)
		goto error;

	int ret;
	ret = json_unpack_ex(*json_result, &json_error, JSON_STRICT, "{s:b, s:i, s:o}", "result", &result->result, "code", &result->code, "data", json_data);
	if(ret != 0)
		goto error;

	result->data = (DataPtr) malloc(sizeof(Data));
	auto_cleanup(result->data);
	result->data->isEmpty = isEmpty(*json_data);
	goto end;

error:
	result->isCallSuccess = false;
	strncpy(result->errorMsg, json_error.text, RESULT_MSG_LENGTH);

end:
	return result;
}


ResultPtr parse(char* json_str) {
	json_t* json_data;
	json_t* json_result;
	ResultPtr result = _parse(json_str, &json_result, &json_data);
	if(json_result != NULL)
		json_decref(json_result);
	return result;
}

ResultPtr parseDirStatus(char* json_str) {
	json_t* json_data;
	json_t* json_result;
	ResultPtr result = _parse(json_str, &json_result, &json_data);
	if(!result->isCallSuccess) {
		if(json_result != NULL)
			json_decref(json_result);
		return result;
	}

	DirStatusPtr dirStatus = (DirStatusPtr) malloc(sizeof(DirStatus));
	auto_cleanup(dirStatus);
	
	json_error_t json_error;
	int ret;
	ret = json_unpack_ex(json_data, &json_error, JSON_STRICT, "{s:i, s:i, s:i}", 
		"num_local", &dirStatus->num_local, 
		"num_cloud", &dirStatus->num_cloud, 
		"num_hybrid", &dirStatus->num_hybrid);
	if(ret != 0) {
		result->isCallSuccess = false;
		strncpy(result->errorMsg, json_error.text, RESULT_MSG_LENGTH);
	}
	result->data->actualData = dirStatus;

	if(json_result != NULL)
		json_decref(json_result);
	return result;
}
