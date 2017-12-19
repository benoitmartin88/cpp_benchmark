#include <benchmark/benchmark.h>
#include <exception>
#include <typeinfo>


static int test(uint64_t i) {
    return ++i;
}

static int test(uint64_t i, bool shouldThrow) {
    if(shouldThrow) {
        throw std::runtime_error("");
    }
    return ++i;
}


static void basicMethodCall(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(i += test(i));
    }
}

static void methodCallWithoutThrow(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(i += test(i, false));
        } catch(const std::runtime_error&) {
        }
    }
}

static void methodCallWithThrowAndSingleCatch(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(i += test(i, true));
        } catch(const std::runtime_error&) {
        }
    }
}

static void methodCallWithThrowAndSingleCatchAll(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(i += test(i, true));
        } catch(...) {
        }
    }
}

static void methodCallWithThrowAndMultipleCatch(benchmark::State& state) {
    uint64_t i=0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(i += test(i, true));
        } catch(const std::domain_error&) {
        } catch(const std::invalid_argument&) {
        } catch(const std::length_error&) {
        } catch(const std::out_of_range&) {
        } catch(const std::bad_typeid&) {
        } catch(const std::bad_cast&) {
        } catch(const std::bad_alloc&) {
        } catch(const std::bad_exception&) {
        } catch(const std::runtime_error&) {
        } catch(...) {
        }
    }
}


BENCHMARK(basicMethodCall);
BENCHMARK(methodCallWithoutThrow);
BENCHMARK(methodCallWithThrowAndSingleCatch);
BENCHMARK(methodCallWithThrowAndSingleCatchAll);
BENCHMARK(methodCallWithThrowAndMultipleCatch);

BENCHMARK_MAIN();

