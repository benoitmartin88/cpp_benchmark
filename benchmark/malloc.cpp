#include <benchmark/benchmark.h>
#include <cstdlib>

void allocate(benchmark::State& state) {
    char* c;
    for (auto _ : state) {
            benchmark::DoNotOptimize(c = static_cast<char*>(malloc(state.range(0))));

            state.PauseTiming();
            free(c);
            state.ResumeTiming();
    }
}

BENCHMARK(allocate)
    ->RangeMultiplier(2)->Range(1, 1024000<<10);

BENCHMARK(allocate)
    ->RangeMultiplier(2)->Range(1, 1024000<<10)
    ->Threads(2)
    ->UseRealTime();

BENCHMARK_MAIN();

