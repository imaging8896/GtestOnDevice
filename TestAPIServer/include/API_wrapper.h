#ifndef TEST_HCFS_API_WRAPPER_H_
#define TEST_HCFS_API_WRAPPER_H_

extern "C" {
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
}

#define FILE_NAME "/data/local/tmp/HCFS_API_log"
#define RESULT_MSG_LENGTH 100

typedef struct Result Result;
typedef Result* ResultPtr;
typedef struct Data Data;
typedef Data* DataPtr;
typedef struct API API;
typedef API* APIptr;

typedef struct DirStatus DirStatus;
typedef DirStatus* DirStatusPtr;

extern FILE *log_fp;
extern APIptr hcfs_api;

void init_wrapper();
void cleanup_wrapper();

struct Result {
	bool isCallSuccess;
	char errorMsg[RESULT_MSG_LENGTH];

	char* json_res;

	bool result;
	int32_t code;
	DataPtr data;
};

struct Data {
	bool isEmpty;
	void* actualData;
};

struct DirStatus {
	int num_local;
	int num_cloud;
	int num_hybrid;
};

typedef ResultPtr (*set_config)(char *key, char *value);
typedef ResultPtr (*get_config)(char *key);

typedef ResultPtr (*reload_config)();

typedef ResultPtr (*hcfs_stat)();

typedef ResultPtr (*get_occupied_size)();

typedef ResultPtr (*toggle_sync)(int32_t enabled);
typedef ResultPtr (*get_sync_status)();

typedef ResultPtr (*pin_path)(char *pin_path, char pin_type);
typedef ResultPtr (*unpin_path)(char *pin_path);
typedef ResultPtr (*pin_status)(char *pathname);

typedef ResultPtr (*dir_status)(char *pathname);
typedef ResultPtr (*file_status)(char *pathname);

typedef ResultPtr (*reset_xfer)();

typedef ResultPtr (*set_notify_server)(char *path);

typedef ResultPtr (*set_swift_token)(char *url, char *token);

typedef ResultPtr (*set_sync_point)();
typedef ResultPtr (*clear_sync_point)();

typedef ResultPtr (*collect_sys_logs)();

typedef ResultPtr (*trigger_restore)();
typedef ResultPtr (*check_restore_status)();

typedef ResultPtr (*notify_applist_change)();

struct API {
	set_config HCFS_set_config;
	get_config HCFS_get_config;

//	reload_config HCFS_reload_config;

//	hcfs_stat HCFS_stat;

//	get_occupied_size HCFS_get_occupied_size;

//	toggle_sync HCFS_toggle_sync;
//	get_sync_status HCFS_get_sync_status;

//	pin_path HCFS_pin_path;
//	unpin_path HCFS_unpin_path;
//	pin_status HCFS_pin_status;

	dir_status HCFS_dir_status;
//	file_status HCFS_file_status;

//	reset_xfer HCFS_reset_xfer;

//	set_notify_server HCFS_set_notify_server;

//	set_swift_token HCFS_set_swift_token;

	set_sync_point HCFS_set_sync_point;
	clear_sync_point HCFS_clear_sync_point;

//	collect_sys_logs HCFS_collect_sys_logs;

//	trigger_restore HCFS_trigger_restore;
//	check_restore_status HCFS_check_restore_status;

//	notify_applist_change HCFS_notify_applist_change;
};

#endif  /* TEST_HCFS_API_WRAPPER_H_ */
