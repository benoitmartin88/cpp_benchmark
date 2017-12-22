#include <benchmark/benchmark.h>
#include <map>
#include <unordered_map>

template<typename _T>
_T constructRandomMap(int size) {
    _T m;
    for (int i = 0; i < size; ++i) {
        m.insert({i, i});
    }
    return m;
}

template<typename _T>
static void mapInsert(benchmark::State& state) {
    _T map;
    for(auto _ : state) {
        for(int i=0; i < state.range(0); ++i) {
            benchmark::DoNotOptimize(map.insert({i, i}));
            benchmark::ClobberMemory();
        }
    }
}

template<typename _T>
static void removeInsert(benchmark::State& state) {
    _T map;
    for(auto _ : state) {

        state.PauseTiming();
        map = constructRandomMap<_T>(state.range(0));
        state.ResumeTiming();

        for(int i=0; i < state.range(0); ++i) {
            auto it = map.find(i);
            benchmark::DoNotOptimize(map.erase(it));
        }
    }
}



BENCHMARK_TEMPLATE(mapInsert, std::map<int, int>)
    ->RangeMultiplier(2)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(mapInsert, std::unordered_map<int, int>)
    ->RangeMultiplier(2)->Range(8, 8<<10);

BENCHMARK_TEMPLATE(removeInsert, std::map<int, int>)
    ->RangeMultiplier(2)->Ranges({{8, 8<<10}});

BENCHMARK_TEMPLATE(removeInsert, std::unordered_map<int, int>)
    ->RangeMultiplier(2)->Ranges({{8, 8<<10}});

BENCHMARK_MAIN();

