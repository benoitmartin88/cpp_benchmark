#include <benchmark/benchmark.h>

static void stringCreation(benchmark::State& state) {
    for (auto _ : state) {
        std::string empty_string;
    }
}

static void stringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state) {
        std::string copy(x);
    }
}


BENCHMARK(stringCreation);
BENCHMARK(stringCopy);

BENCHMARK_MAIN();

