#include "stdio.h"
#include "cpuinfo.h"
#include <sys/syscall.h>

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


int main( ){
    printf("Hello world!\n");
    //Log processor name:
    cpuinfo_initialize();
    
    printf("Total %d processors, %d cores, %d packages\n"
           , cpuinfo_get_processors_count()
           , cpuinfo_get_cores_count()
           , cpuinfo_get_packages_count());
    
    // get now running cpu
    const struct cpuinfo_processor* nowProcessor = cpuinfo_get_current_processor();
    printf("Now running on core: %d, %s cpu, %s gpu\n", nowProcessor->core->core_id,
           nowProcessor->core->package->name,
           nowProcessor->core->package->gpu_name);
    printf("Target CPU microarchitectures is %#010x\n", nowProcessor->core->uarch);
    
    //printf("Running on %s CPU\n", cpuinfo_get_package(0)->name);
    
    // Check if the host CPU support ARM NEON
    if (cpuinfo_has_arm_neon()) {
        printf("Target cpu has NEON\n");
    }
    else{
        printf("Target cpu has no NEON\n");
    }
    
    // Check if the host CPU supports x86 AVX
    if (cpuinfo_has_x86_avx()) {
        printf("Target cpu has x86 AVX\n");
    }
    else{
        printf("Target cpu has no x86 AVX\n");
    }
    
    // Get target CPU microarchitectures
    printf("Target CPU microarchitectures is %#010x\n", cpuinfo_get_current_core()->uarch);
    
    
    return 0;
}
