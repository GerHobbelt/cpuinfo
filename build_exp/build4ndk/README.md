# How to build cpuinfo for ndk ( Android )

Since cpuinfo is written by c, the only way to use it in Android is through NDK. With android-cmake, we can easily build it with following commands:

## Setup environment variables
    export ANDROID_NDK=<ndk_path>/
    
## Build it
    mkdir build4ndk
    cd build4ndk
    cmake -DCMAKE_TOOLCHAIN_FILE=<your path>/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a with NEON" -DANDROID_NATIVE_API_LEVEL=9 ../ && cmake --build .
    make all

Notice that we use API Level = 9 since the last supported version in our ndk is 9.
We shut down test part and command line tools, which can not be compiled.

## Use it
First of all, ndk does not contain implement of extern function sched_getcpu(), we have to implement it by ourself:

    extern "C"{
        int sched_getcpu(void){
        unsigned cpu;
        if (syscall(__NR_getcpu, &cpu, NULL, NULL) < 0) {
            return -1;
        } else {
        return (int) cpu;
        }
        }
    }

Just copy it to your code, and link libcpuinfo.a. Or, you will got following error:

    error: undefined reference to 'sched_getcpu'
