#pragma once
#include <limits>
#include <memory>
#include "../headers/bin_tree.hpp"

void check_input(int &choice);
void run_types_menu();
template <typename T>
void set_tree_type();
template <typename T>
void run_tree_menu(bin_tree<T> *tree);