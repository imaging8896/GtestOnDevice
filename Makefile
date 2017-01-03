# starting with '@' means not showing command

all: 
	@ndk-build NDK_PROJECT_PATH=.
	
install:
	@adb -s $(device) push libs/arm64-v8a/libgnustl_shared.so /data/local/tmp/
	@adb -s $(device) push libs/arm64-v8a/API_server_test /data/local/tmp/
	@adb -s $(device) shell chmod 775 /data/local/tmp/API_server_test

clean:
	@rm -rf libs
	@rm -rf obj
