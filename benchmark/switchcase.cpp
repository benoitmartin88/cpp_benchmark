#include <benchmark/benchmark.h>
#include <functional>


enum TestEnum {
    TEST1=0, TEST2, TEST3
};

std::function<TestEnum()> r = [] {
//    TestEnum e = static_cast<TestEnum>(rand() % TEST3+1); // enum length is last element+1 (enum starts at 0)
    return TEST3;
};


template<typename _T>
static _T singleIf() {
    auto i = r();
    if(i != TEST1 && i != TEST2 && i != TEST3) {
        return static_cast<_T>(TEST1);
    }

    return rand();
}

template<typename _T>
static _T singleSwitch() {
    switch(r()) {
        case TEST1: return static_cast<_T>(TEST1); break;
        case TEST2: return static_cast<_T>(TEST2); break;
        case TEST3: break;
        default: return 0;
    }

    return rand();
}

template<typename _T>
static _T multipleSwitch() {
    switch(r()) {
        case TEST1: return static_cast<_T>(TEST1); break;
        case TEST2: return static_cast<_T>(TEST2); break;
        case TEST3: break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<_T>(TEST1); break;
        case TEST2: return static_cast<_T>(TEST2); break;
        case TEST3: break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<_T>(TEST1); break;
        case TEST2: return static_cast<_T>(TEST2); break;
        case TEST3: break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<_T>(TEST1); break;
        case TEST2: return static_cast<_T>(TEST2); break;
        case TEST3: break;
        default: return 0;
    }
    switch(r()) {
        case TEST1: return static_cast<_T>(TEST1); break;
        case TEST2: return static_cast<_T>(TEST2); break;
        case TEST3: break;
        default: return 0;
    }

    return rand();
}


static void singleSwitchCase8(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(singleSwitch<uint8_t>());
    }
}

static void singleSwitchCase64(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(singleSwitch<uint64_t>());
    }
}

static void singleIf64(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(singleIf<uint64_t>());
    }
}

static void multipleSwitchCase(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(multipleSwitch<uint8_t>());
    }
}



BENCHMARK(singleSwitchCase8);
BENCHMARK(singleSwitchCase64);
BENCHMARK(singleIf64);
BENCHMARK(multipleSwitchCase);

BENCHMARK_MAIN();

