#include <benchmark/benchmark.h>
#include "../headers/bin_tree.hpp"
#include <random>
#include <iostream>
#include <vector>

static std::vector<int> generate_random_data_large(size_t size)
{
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 1);
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});
    return data;
}

static void BM_Insert_Large(benchmark::State &state)
{
    size_t n = state.range(0);
    auto data = generate_random_data_large(n);

    for (auto _ : state)
    {
        std::cout << "BM_Example iteration..." << std::endl;
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
BENCHMARK(BM_Insert_Large)->Arg(1e6)->Arg(2e6)->Arg(4e6)->Arg(6e6)->Arg(8e6)->Arg(1e7)->Arg(2e7)->Arg(4e7)->Arg(6e7)->Arg(8e7)->Arg(1e8)->Unit(benchmark::kMillisecond);

static void BM_Remove_Large(benchmark::State &state)
{
    size_t n = state.range(0);
    auto data = generate_random_data_large(n);
    bin_tree<int> tree;

    for (auto _ : state)
    {
        std::cout << "BM_Example iteration..." << std::endl;
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
BENCHMARK(BM_Remove_Large)->Arg(1e6)->Arg(2e6)->Arg(4e6)->Arg(6e6)->Arg(8e6)->Arg(1e7)->Arg(2e7)->Arg(4e7)->Arg(6e7)->Arg(8e7)->Arg(1e8)->Unit(benchmark::kMillisecond);