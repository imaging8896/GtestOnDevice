########################################################
#
# use ADDITIONAL_SHARED_LIBRARIES to add libraries
# use ADDITIONAL_STATIC_LIBRARIES to add libraries
#
########################################################

  LOCAL_PATH := $(call my-dir)

  ADDITIONAL_SHARED_LIBRARIES := 
  ADDITIONAL_STATIC_LIBRARIES := 

  LOCAL_PATH_BAK := $(LOCAL_PATH)
  include $(call all-subdir-makefiles)

########################################################

  LOCAL_PATH := $(LOCAL_PATH_BAK)

  # include <HCFS_api.h>
  include $(CLEAR_VARS)
  LOCAL_MODULE := HCFS_api-prebuilt
  LOCAL_SRC_FILES := libHCFS_api.so
  # include/HCFS_api.h
  LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
  include $(PREBUILT_SHARED_LIBRARY)

  # include <jansson.h>
  include $(CLEAR_VARS)
  LOCAL_MODULE := jansson-prebuilt
  LOCAL_SRC_FILES := libjansson.so
  # include/jansson.h and include/jansson_config.h
  LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
  include $(PREBUILT_SHARED_LIBRARY)

  include $(CLEAR_VARS)
  LOCAL_MODULE := utils
  LOCAL_SRC_FILES := \
		$(subst $(LOCAL_PATH)/,, \
			$(wildcard $(LOCAL_PATH)/utils/*.cc))
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
  include $(BUILD_STATIC_LIBRARY)
  
  # all tests in all sub-directories
  include $(CLEAR_VARS)
  LOCAL_MODULE := alltests
  LOCAL_SRC_FILES := \
		main.cc \
		$(subst $(LOCAL_PATH)/,, \
			$(wildcard $(LOCAL_PATH)/TestCases/*/*.cc)) \
		$(subst $(LOCAL_PATH)/,, \
			$(wildcard $(LOCAL_PATH)/TestCases/*.cc))

  LOCAL_SHARED_LIBRARIES := \
		HCFS_api-prebuilt \
		jansson-prebuilt \
		$(ADDITIONAL_SHARED_LIBRARIES)

  LOCAL_STATIC_LIBRARIES := \
		googletest_static \
		utils \
		$(ADDITIONAL_STATIC_LIBRARIES)

  include $(BUILD_STATIC_LIBRARY)
