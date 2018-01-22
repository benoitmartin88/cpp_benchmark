#include <benchmark/benchmark.h>
#include <iostream>

struct BaseNoVirt {
    BaseNoVirt(uint64_t& nbCtor, uint64_t& nbDtor) : nbDtor(nbDtor) {
        ++nbCtor;
    }
    ~BaseNoVirt() noexcept {
        ++nbDtor;
    }
    void foo() {
    }
    uint64_t& nbDtor;
};

struct BaseVirt {
    BaseVirt(uint64_t& nbCtor, uint64_t& nbDtor) : nbDtor(nbDtor) {
        ++nbCtor;
    }
    virtual ~BaseVirt() noexcept {
        ++nbDtor;
    }
    virtual void foo() {
    }
//    virtual void bar() = 0;
    uint64_t& nbDtor;
};

struct ChildNoVirt : public BaseNoVirt {
    ChildNoVirt(uint64_t& nbCtor, uint64_t& nbDtor) : BaseNoVirt(nbCtor, nbDtor) {
    }
    ~ChildNoVirt() {
        assert(false);  // should not be called, Base is not virtual
    }
};

struct ChildVirt : public BaseVirt {
    ChildVirt(uint64_t& nbCtor, uint64_t& nbDtor) : BaseVirt(nbCtor, nbDtor) {
    }
    virtual void foo() {
    }
};


struct MyFixture : public benchmark::Fixture {
    uint64_t nbCtor = 0;
    uint64_t nbDtor = 0;
};


BENCHMARK_F(MyFixture, NoVirtualDtor)(benchmark::State& state) {
    for(auto _ : state) {
        state.PauseTiming();
        BaseNoVirt c(nbCtor, nbDtor);
        state.ResumeTiming();

//        c.~BaseNoVirt() is called at the end of scope
    }

    assert(nbCtor == nbDtor);
}

BENCHMARK_F(MyFixture, VirtualDtor)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BaseVirt c(nbCtor, nbDtor);
        state.ResumeTiming();

//        c.~BaseVirt() is called at the end of scope
    }

    assert(nbCtor == nbDtor);
}

BENCHMARK_F(MyFixture, ChildPtrNoVirtualDtor)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BaseNoVirt* c = new ChildNoVirt(nbCtor, nbDtor);
        state.ResumeTiming();

        delete c;
    }

    assert(nbCtor == nbDtor);
}

BENCHMARK_F(MyFixture, ChildPtrVirtualDtor)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BaseVirt* c = new ChildVirt(nbCtor, nbDtor);
        state.ResumeTiming();
        
        delete c;
    }

    assert(nbCtor == nbDtor);
}

BENCHMARK_F(MyFixture, BasePtrNoVirtualMethod)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BaseNoVirt* c = new BaseNoVirt(nbCtor, nbDtor);
        state.ResumeTiming();

        c->foo();
        
        state.PauseTiming();
        delete c;
        state.ResumeTiming();
    }

    assert(nbCtor == nbDtor);
}

BENCHMARK_F(MyFixture, BasePtrVirtualMethod)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BaseVirt* c = new BaseVirt(nbCtor, nbDtor);
        state.ResumeTiming();

        c->foo();
        
        state.PauseTiming();
        delete c;
        state.ResumeTiming();
    }

    assert(nbCtor == nbDtor);
}

BENCHMARK_F(MyFixture, ChildPtrVirtualMethod)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        BaseVirt* c = new ChildVirt(nbCtor, nbDtor);
        state.ResumeTiming();

        c->foo();
        
        state.PauseTiming();
        delete c;
        state.ResumeTiming();
    }

    assert(nbCtor == nbDtor);
}



BENCHMARK_MAIN();

