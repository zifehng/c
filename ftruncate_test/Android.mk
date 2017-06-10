LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ftruncate_test
LOCAL_SRC_FILES := ftruncate_test.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE) 

include $(CLEAR_VARS)
LOCAL_MODULE := c787_config_read
LOCAL_SRC_FILES := c787_config_read.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE) 