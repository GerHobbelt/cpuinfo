#define BENCHMARK_FAMILY_ID "CPUinfo-init"

#include <benchmark/benchmark.h>

#include <cpuinfo.h>

static void cpuinfo_initialize(benchmark::State& state) {
	while (state.KeepRunning()) {
		cpuinfo_initialize();
	}
}
BENCHMARK(cpuinfo_initialize)->Iterations(1)->Unit(benchmark::kMillisecond);


#if defined(BUILD_MONOLITHIC)
#define main   cpuinfo_benchmark_init_main
#endif

BENCHMARK_MAIN();
