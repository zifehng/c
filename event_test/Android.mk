LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := event_test
LOCAL_SRC_FILES := event_test.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE) 
