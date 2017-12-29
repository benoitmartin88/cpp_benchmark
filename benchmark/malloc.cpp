#include <benchmark/benchmark.h>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <iostream>


struct MyFixture : public benchmark::Fixture {
    std::unordered_map<uint16_t, std::vector<double>> data;
};

BENCHMARK_DEFINE_F(MyFixture, allocate)(benchmark::State& state) {
    char* c;
    for (auto _ : state) {
        auto start = std::chrono::high_resolution_clock::now();
        benchmark::DoNotOptimize(c = static_cast<char*>(malloc(state.range(0))));
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        state.SetIterationTime(elapsed.count());

        free(c);

        data[state.thread_index].push_back(elapsed.count());
    }

//    std::cout << "> data.size()=" << data.size() << std::endl;
//    std::cout << "> data[state.thread_index].size()=" << data[state.thread_index].size() << std::endl;

    auto& v = data[state.thread_index];

    double min = *(std::min_element(v.begin(), v.end()));
    double max = *(std::max_element(v.begin(), v.end()));

    state.counters["min"] = min;
    state.counters["max"] = max;
    state.counters["spread"] = max - min;

    std::sort(v.begin(), v.end());
    state.counters["99"] = v[0.99*v.size()];
    state.counters["99.9"] = v[0.999*v.size()];
    state.counters["99.99"] = v[0.9999*v.size()];
    state.counters["99.999"] = v[0.99999*v.size()];
    state.counters["99.9999"] = v[0.999999*v.size()];
    
    data.clear();   // clear map
}

BENCHMARK_REGISTER_F(MyFixture, allocate)
    ->UseManualTime()
    ->RangeMultiplier(2)->Range(1, 1024000<<10);

/*
BENCHMARK(allocate)
    ->ComputeStatistics("spread", [](const std::vector<double>& v) -> double {
        auto max = *(std::max_element(std::begin(v), std::end(v)));
        auto min = *(std::min_element(std::begin(v), std::end(v)));
        return max - min;
    })
    ->RangeMultiplier(2)->Range(1, 1024000<<10);


BENCHMARK(allocate)
    ->ComputeStatistics("spread", [](const std::vector<double>& v) -> double {
        auto max = *(std::max_element(std::begin(v), std::end(v)));
        auto min = *(std::min_element(std::begin(v), std::end(v)));
        return max - min;
    })
    ->RangeMultiplier(2)->Range(1, 1024000<<10)
    ->Threads(2)
    ->UseRealTime();
*/
BENCHMARK_MAIN();

