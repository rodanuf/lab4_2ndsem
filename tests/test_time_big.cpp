#include <benchmark/benchmark.h>
#include "../headers/bin_tree.hpp"
#include <random>
#include <iostream>
#include <vector>

static std::vector<int> generate_random_data_big(size_t size)
{
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 1);
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});
    return data;
}

static void BM_Insert_Big(benchmark::State &state)
{
    size_t n = state.range(0);
    auto data = generate_random_data_big(n);

    for (auto _ : state)
    {
        bin_tree<int> tree;
        for (int val : data)
        {
            tree.insert(val);
        }
        state.PauseTiming();
        tree.clear();
        state.ResumeTiming();
    }
}
BENCHMARK(BM_Insert_Big)->Arg(1e4)->Arg(2e4)->Arg(3e4)->Arg(5e4)->Arg(6e4)->Arg(7e4)->Arg(8e4)->Arg(9e4)->Arg(1e5)->Unit(benchmark::kMillisecond);

static void BM_Remove_Big(benchmark::State &state)
{
    size_t n = state.range(0);
    auto data = generate_random_data_big(n);
    bin_tree<int> tree;

    for (auto _ : state)
    {
        state.PauseTiming();
        for (int val : data)
            tree.insert(val);
        std::shuffle(data.begin(), data.end(), std::mt19937{42});
        state.ResumeTiming();

        for (int val : data)
        {
            tree.remove(val);
        }
    }
}
BENCHMARK(BM_Remove_Big)->Arg(1e4)->Arg(2e4)->Arg(3e4)->Arg(5e4)->Arg(6e4)->Arg(7e4)->Arg(8e4)->Arg(9e4)->Arg(1e5)->Unit(benchmark::kMillisecond);