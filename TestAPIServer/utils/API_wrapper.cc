extern "C" {
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <HCFS_api.h>
}

#include "API_wrapper.h"
#include "JsonParser.h"

FILE *log_fp;
APIptr hcfs_api;

ResultPtr set_config_impl(char *key, char *value);
ResultPtr get_config_impl(char *key);

ResultPtr dir_status_impl(char *pathname);

ResultPtr set_sync_point_impl();
ResultPtr clear_sync_point_impl();

static API api_impl = {
	.HCFS_set_config = &set_config_impl,
	.HCFS_get_config = &get_config_impl,

	.HCFS_dir_status = &dir_status_impl,

	.HCFS_set_sync_point = &set_sync_point_impl,
	.HCFS_clear_sync_point = &clear_sync_point_impl
};

void init_wrapper() {
	cleanup_wrapper();
	if (access(FILE_NAME, F_OK) == 0)
		remove(FILE_NAME);
	log_fp = fopen(FILE_NAME, "a");

	hcfs_api = &api_impl;
}

void cleanup_wrapper() {
	if(log_fp != NULL) {
		fclose(log_fp);
		log_fp = NULL;
	}
}

char* get_cur_time() {
	time_t ltime; /* calendar time */
	ltime=time(NULL);
	char* timestamp = asctime(localtime(&ltime));
	timestamp[strlen(timestamp) - 1] = 0;
	return timestamp;
}

ResultPtr set_config_impl(char *key, char *value) {
	char* json_res;
	HCFS_set_config(&json_res, key, value);
	fprintf(log_fp, "%s : HCFS_set_config <%s><%s>, result<%s>\n", get_cur_time(), key, value, json_res);
	return parse(json_res);
}

ResultPtr get_config_impl(char *key) {
	char* json_res;
	HCFS_get_config(&json_res, key);
	fprintf(log_fp, "%s : HCFS_get_config <%s>, result<%s>\n", get_cur_time(), key, json_res);
	return parse(json_res);
}



ResultPtr dir_status_impl(char *pathname) {
	char* json_res;
	HCFS_dir_status(&json_res, pathname);
	fprintf(log_fp, "%s : HCFS_dir_status <%s> result<%s>\n", get_cur_time(), pathname, json_res);
	return parseDirStatus(json_res);
}



ResultPtr set_sync_point_impl() {
	char* json_res;
	HCFS_set_sync_point(&json_res);
	fprintf(log_fp, "%s : HCFS_set_sync_point result<%s>\n", get_cur_time(), json_res);
	return parse(json_res);
}

ResultPtr clear_sync_point_impl() {
	char* json_res;
	HCFS_clear_sync_point(&json_res);
	fprintf(log_fp, "%s : HCFS_clear_sync_point result<%s>\n", get_cur_time(), json_res);
	return parse(json_res);
}
