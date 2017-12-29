
This project uses Google Benchmark to test basic C++ functionalities.



# Dependencies
This project depends on Google Test and Google Benchmark.
Both of these dependencies are expressed as git submodules.


# Build
``` bash
$ clone git@github.com:benoitmartin88/cpp_benchmark.git
$ cd cpp_benchmark
$ git submodule update --init --recursive
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release .. && make

# list built files
$ ls benchmark
# run a bench
$ ./benchmark/trycatch
```
