LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := uevent_test
LOCAL_SRC_FILES := uevent_test.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE) 