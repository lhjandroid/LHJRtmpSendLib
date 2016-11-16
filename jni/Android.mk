# Android.mk for rtmp

LOCAL_PATH := $(call my-dir)

# rtmp library
include $(CLEAR_VARS)
LOCAL_MODULE := rtmp
LOCAL_SRC_FILES := librtmp.so
include $(PREBUILT_SHARED_LIBRARY)
#include $(PREBUILT_STATIC_LIBRARY)


# Program
include $(CLEAR_VARS)
#LOCAL_MODULE := LhjRtmpjni
LOCAL_MODULE := rtmp_send264
#LOCAL_SRC_FILES := LhjRtmpjni.cpp
LOCAL_SRC_FILES := librtmp_send264.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
-D__int64="long long"
LOCAL_LDLIBS := -llog -lz
LOCAL_SHARED_LIBRARIES := rtmp
LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS -Wl,-Map=test.map -g 
include $(BUILD_SHARED_LIBRARY)