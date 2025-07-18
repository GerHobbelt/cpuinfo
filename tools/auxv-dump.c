#include <stdio.h>
#include <stdlib.h>

#if !defined(_WIN32)

#include <dlfcn.h>
#include <errno.h>
#include <sys/auxv.h>

#endif

#include <cpuinfo.h>
#include "monolithic_examples.h"

typedef unsigned long (*getauxval_function_t)(unsigned long);

#if defined(BUILD_MONOLITHIC)
#define main		cpuinfo_auxv_dump_main
#endif

int main(int argc, const char** argv) {
#if !defined(_WIN32)
	void* libc = dlopen("libc.so", RTLD_NOW);
	if (libc == NULL) {
		fprintf(stderr, "Error: failed to load libc.so: %s\n", dlerror());
		return EXIT_FAILURE;
	}

	getauxval_function_t getauxval = (getauxval_function_t)dlsym(libc, "getauxval");
	if (getauxval == NULL) {
		fprintf(stderr, "Error: failed to locate getauxval in libc.so: %s", dlerror());
		return EXIT_FAILURE;
	}

	printf("AT_HWCAP = 0x%08lX\n", getauxval(AT_HWCAP));
#if CPUINFO_ARCH_ARM
	printf("AT_HWCAP2 = 0x%08lX\n", getauxval(AT_HWCAP2));
#endif

	return EXIT_SUCCESS;
#else
	printf("No getauxval(AT_HWCAP2) support.\n");
	return EXIT_FAILURE;
#endif
}
