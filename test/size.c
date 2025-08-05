#include <cpuinfo.h>

#if defined(BUILD_MONOLITHIC)
#define main  cpuinfo_test_size_main
#endif

int main(void) {
	cpuinfo_initialize();
	return 0;
}
