LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2-2.0.7

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/inifile $(LOCAL_PATH)/SDL_FontCache

LOCAL_SRC_FILES :=  main.cpp inifile/inifile.cpp SDL_FontCache/SDL_FontCache.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_mixer SDL2_image 

LOCAL_CFLAGS := -std=c++11 -fexceptions -DDEV

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
