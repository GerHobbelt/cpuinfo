
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int cpuinfo_auxv_dump_main(int argc, const char** argv);
int cpuinfo_cache_info_main(int argc, const char** argv);
int cpuinfo_cpu_info_main(int argc, const char** argv);
int cpuinfo_cpuid_dump_main(int argc, const char** argv);
int cpuinfo_dump_main(int argc, const char** argv);
int cpuinfo_gnu_dump_main(int argc, const char** argv);
int cpuinfo_isa_info_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
