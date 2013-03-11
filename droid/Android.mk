LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := v:/cpp y:/v8/h y:/ksana/yaui/share
LOCAL_MODULE    := dJS
LOCAL_SRC_FILES := dJS.cpp
LOCAL_CFLAGS += -O0 -w -s -Wfatal-errors -fshort-wchar
LOCAL_LDLIBS := -lv8 -Llibs -llog

include $(BUILD_SHARED_LIBRARY)
