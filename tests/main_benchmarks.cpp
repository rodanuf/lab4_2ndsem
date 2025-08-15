#include <benchmark/benchmark.h>
#include "../headers/bin_tree.hpp"

#include "test_time_big.cpp"

int main(int argc, char **argv)
{
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    return 0;
}