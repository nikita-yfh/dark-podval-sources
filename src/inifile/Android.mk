LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := INI

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_SRC_FILES := inifile.cpp

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)

include $(BUILD_SHARED_LIBRARY)