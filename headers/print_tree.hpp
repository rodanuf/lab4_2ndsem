#pragma once
#include <iostream>

void print_spaces(int count = 4);

template <typename T>
void print_tree(bin_tree<T> &tree, bool is_left, int vertical);

template <typename T>
void print_tree_helper(typename bin_tree<T>::node *node, bool is_left, int vertical);

#include "../templates/print_tree.tpp"