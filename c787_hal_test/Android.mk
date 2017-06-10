LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := c787_ctrl_test
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := c787_ctrl_test.c \
		keystone.c \
		calc_homography.c \
		init_wpgrid.c \
		init_wptable.c \
		set_curpos.c \
		set_lut.c \
		set_lut_wplg.c \
		set_wpgrid.c \
		set_wpkey4c.c \
		spi_sync.c \
		write_wptable.c \
		wait1_povs.c \
		calc_4corner.c

LOCAL_CFLAGS += -Wno-unused-parameter

include $(BUILD_EXECUTABLE)

