#include <benchmark/benchmark.h>
#include <stdexcept>


static int test(uint64_t i) {
    return ++i;
}

static int test(uint64_t i, bool shouldThrow) {
    if(shouldThrow) {
        throw std::runtime_error("");
    }
    return ++i;
}


static void noTryCatch(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(i += test(i));
    }
}

static void noThrow(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(i += test(i, false));
        } catch(const std::runtime_error&) {
        }
    }
}

static void throwException(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(i += test(i, true));
        } catch(const std::runtime_error&) {
        }
    }
}


BENCHMARK(noTryCatch);
BENCHMARK(noThrow);
BENCHMARK(throwException);

BENCHMARK_MAIN();

