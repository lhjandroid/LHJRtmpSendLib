#APP_ABI := all
#APP_ABI := armeabi armeabi-v7a x86
#APP_CPPFLAGS= -std=gnu++0x
APP_OPTIM := debug
APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DCOCOS2D_DEBUG=1 -std=c++11 -DDEBUG=1
APP_USE_CPP0X := true
APP_ABI :=armeabi