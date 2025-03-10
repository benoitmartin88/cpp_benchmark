
#include <benchmark/benchmark.h>
#include <Kokkos_Core.hpp>
#include <chrono>
#include <iostream>


void deep_copy(benchmark::State& state) {

    std::vector<double> timers;

    for (auto _ : state) {
        // Contiguous Device View
        Kokkos::View<char*, Kokkos::LayoutLeft> data("a", state.range(0));
        
        auto start = std::chrono::high_resolution_clock::now();
        // Deep Copy Scalar into every element of a view
        //benchmark::DoNotOptimize(Kokkos::deep_copy(data, "b"));
        Kokkos::deep_copy(data, 'b');
        auto end = std::chrono::high_resolution_clock::now();

        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        state.SetIterationTime(elapsed.count());

        
        timers.push_back(elapsed.count());
    }

    assert(timers.size() == state.iterations());

    state.counters["min"] = benchmark::Counter(*(std::min_element(timers.begin(), timers.end())), benchmark::Counter::kAvgThreads);
    state.counters["max"] = benchmark::Counter(*(std::max_element(timers.begin(), timers.end())), benchmark::Counter::kAvgThreads);

    std::sort(timers.begin(), timers.end());
    state.counters["50"] = benchmark::Counter(timers[0.50*timers.size()], benchmark::Counter::kAvgThreads);
    state.counters["75"] = benchmark::Counter(timers[0.75*timers.size()], benchmark::Counter::kAvgThreads);
    state.counters["99"] = benchmark::Counter(timers[0.99*timers.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.9"] = benchmark::Counter(timers[0.999*timers.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.99"] = benchmark::Counter(timers[0.9999*timers.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.999"] = benchmark::Counter(timers[0.99999*timers.size()], benchmark::Counter::kAvgThreads);
    state.counters["99.9999"] = benchmark::Counter(timers[0.999999*timers.size()], benchmark::Counter::kAvgThreads);
    
    timers.clear();   // clear map
}


int main(int argc, char** argv) {
  Kokkos::initialize(argc, argv);

  BENCHMARK(deep_copy)
    ->UseManualTime()
    ->RangeMultiplier(2)->Range(1, 65536);

    //these entries are from BENCHMARK_MAIN
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();

  Kokkos::finalize();
}
