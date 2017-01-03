########################################################
#
# use ADDITIONAL_SHARED_LIBRARIES to add libraries
# use ADDITIONAL_STATIC_LIBRARIES to add libraries
#
########################################################

  LOCAL_PATH_BAK := $(call my-dir)
  include TestAPIServer/Android.mk

########################################################

  LOCAL_PATH := $(LOCAL_PATH_BAK)

  # main executable
  include $(CLEAR_VARS)
  LOCAL_MODULE := API_server_test
  LOCAL_CFLAGS := -pie -fPIE
  LOCAL_LDFLAGS := -pie -fPIE 
  LOCAL_WHOLE_STATIC_LIBRARIES := alltests 
  include $(BUILD_EXECUTABLE)

  $(call import-module,third_party/googletest)
