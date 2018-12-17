#include <benchmark/benchmark.h>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <iostream>


void allocate(benchmark::State& state) {
    char* c;
    std::vector<double> data;
    for (auto _ : state) {
        auto start = std::chrono::high_resolution_clock::now();
        benchmark::DoNotOptimize(c = static_cast<char*>(malloc(state.range(0))));
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        state.SetIterationTime(elapsed.count());

        free(c);
        
        data.push_back(elapsed.count());
    }

    assert(data.size() == state.iterations());

    state.counters["min"] = benchmark::Counter(*(std::min_element(data.begin(), data.end())), benchmark::Counter::kAvgThreads);
    state.counters["max"] = benchmark::Counter(*(std::max_element(data.begin(), data.end())), benchmark::Counter::kAvgThreads);

    std::sort(data.begin(), data.end());
    state.counters["50"] = benchmark::Counter(data[0.50*data.size()], benchmark::Counter::kAvgThreads);
    state.counters["75"] = benchmark::Counter(data[0.75*data.size()], benchmark::Counter::kAvgThreads);
    state.counters["99"] = benchmark::Counter(data[0.99*data.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.9"] = benchmark::Counter(data[0.999*data.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.99"] = benchmark::Counter(data[0.9999*data.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.999"] = benchmark::Counter(data[0.99999*data.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.9999"] = benchmark::Counter(data[0.999999*data.size()], benchmark::Counter::kAvgThreads);
    
    data.clear();   // clear map
}

BENCHMARK(allocate)
    ->UseManualTime()
    ->RangeMultiplier(2)->Range(1, 65536);

BENCHMARK(allocate)
    ->UseManualTime()
    ->RangeMultiplier(2)->Range(1, 65536)
    ->Threads(2);

BENCHMARK(allocate)
    ->UseManualTime()
    ->RangeMultiplier(2)->Range(1, 65536)
    ->Threads(4);

BENCHMARK_MAIN();

