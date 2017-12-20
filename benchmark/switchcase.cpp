#include <benchmark/benchmark.h>
#include <functional>


enum TestEnum {
    TEST1=0, TEST2, TEST3
};

std::function<TestEnum()> r = [] {
    return static_cast<TestEnum>(rand() % TEST3+1); // enum length is last element+1 (enum starts at 0)
};

static uint64_t single() {
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
}

static uint64_t multiple() {
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<uint64_t>(TEST1); break;
        case TEST2: return static_cast<uint64_t>(TEST2); break;
        case TEST3: return static_cast<uint64_t>(TEST3); break;
        default: return 0;
    }
}


static void singleSwitchCase(benchmark::State& state) {
//    srand(time(NULL));
    for (auto _ : state) {
        benchmark::DoNotOptimize(single());
    }
}

static void multipleSwitchCase(benchmark::State& state) {
//    srand(time(NULL));
    for (auto _ : state) {
        benchmark::DoNotOptimize(multiple());
    }
}



BENCHMARK(singleSwitchCase);
BENCHMARK(multipleSwitchCase);

BENCHMARK_MAIN();

