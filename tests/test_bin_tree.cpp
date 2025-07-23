#include <gtest/gtest.h>
#include <iostream>
#include "sequence.hpp"
#include "array_sequence.hpp"
#include "stack.hpp"
#include "../headers/bin_tree.hpp"

TEST(test_bin_tree_iterator, base_constructor_iterator)
{
    bin_tree<int> tree;
    tree.insert(42);
    auto it = tree.begin("in_order");
    EXPECT_EQ(*it, 42);
}

TEST(test_bin_tree_iterator, copy_constructor_iterator)
{
    bin_tree<int> tree;
    tree.insert(42);
    auto it_one = tree.begin("in_order");
    auto it_two = it_one;
    EXPECT_EQ(it_two, it_one);
}

TEST(test_bin_tree_iterator_operators, pref_operator_increment)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.begin("in_order");
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(++empty_it, std::out_of_range);
}

TEST(test_bin_tree_iterator_operators, post_operator_increment)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.begin("in_order");
    EXPECT_EQ(*it, 2);
    auto old_it = it++;
    EXPECT_EQ(*old_it, 2);
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(empty_it++, std::out_of_range);
}

TEST(test_bin_tree_iterator_operators, pref_operator_decrement)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.begin("in_order");
    it++;
    it++;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(--empty_it, std::out_of_range);
}

TEST(test_bin_tree_iterator_operators, post_operator_decrement)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.begin("in_order");
    it++;
    it++;
    EXPECT_EQ(*it, 3);
    auto old_it = it--;
    EXPECT_EQ(*old_it, 3);
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(empty_it--, std::out_of_range);
}

TEST(test_bin_tree_iterator_operators, operator_equality)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it_one = tree.begin("in_order");
    auto it_two = tree.begin("in_order");
    EXPECT_TRUE(it_one == it_two);
    ++it_one;
    EXPECT_FALSE(it_one == it_two);
}

TEST(test_bin_tree_iterator_operators, operator_nonequality)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it_one = tree.begin("in_order");
    auto it_two = tree.begin("in_order");
    EXPECT_FALSE(it_one != it_two);
    ++it_one;
    EXPECT_TRUE(it_one != it_two);
}

TEST(test_bin_tree_iterator_operators, method_begin)
{
    bin_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    auto it = tree.begin("in_order");
    EXPECT_EQ(*it, 20);
}

TEST(test_bin_tree_iterator_operators, method_end)
{
    bin_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    auto it = tree.end("in_order");
    --it;
    EXPECT_EQ(*it, 30);
}

TEST(test_bin_tree_const_iterator, base_constructor_iterator)
{
    bin_tree<int> tree;
    tree.insert(42);
    auto it = tree.cbegin("in_order");
    EXPECT_EQ(*it, 42);
}

TEST(test_bin_tree_const_iterator, copy_constructor_iterator)
{
    bin_tree<int> tree;
    tree.insert(42);
    auto it_one = tree.cbegin("in_order");
    auto it_two = it_one;
    EXPECT_EQ(it_two, it_one);
}

TEST(test_bin_tree_const_iterator_operators, pref_operator_increment)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.cbegin("in_order");
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(++empty_it, std::out_of_range);
}

TEST(test_bin_tree_const_iterator_operators, post_operator_increment)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.cbegin("in_order");
    EXPECT_EQ(*it, 2);
    auto old_it = it++;
    EXPECT_EQ(*old_it, 2);
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(empty_it++, std::out_of_range);
}

TEST(test_bin_tree_const_iterator_operators, pref_operator_decrement)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.cbegin("in_order");
    it++;
    it++;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(--empty_it, std::out_of_range);
}

TEST(test_bin_tree_const_iterator_operators, post_operator_decrement)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it = tree.cbegin("in_order");
    it++;
    it++;
    EXPECT_EQ(*it, 3);
    auto old_it = it--;
    EXPECT_EQ(*old_it, 3);
    EXPECT_EQ(*it, 1);
    bin_tree<int> empty_tree;
    auto empty_it = empty_tree.begin("in_order");
    EXPECT_THROW(empty_it--, std::out_of_range);
}

TEST(test_bin_tree_const_iterator_operators, operator_equality)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it_one = tree.cbegin("in_order");
    auto it_two = tree.cbegin("in_order");
    EXPECT_TRUE(it_one == it_two);
    ++it_one;
    EXPECT_FALSE(it_one == it_two);
}

TEST(test_bin_tree_const_iterator_operators, operator_nonequality)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto it_one = tree.cbegin("in_order");
    auto it_two = tree.cbegin("in_order");
    EXPECT_FALSE(it_one != it_two);
    ++it_one;
    EXPECT_TRUE(it_one != it_two);
}

TEST(test_bin_tree_const_iterator_operators, method_begin)
{
    bin_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    auto it = tree.cbegin("in_order");
    EXPECT_EQ(*it, 20);
}

TEST(test_bin_tree_const_iterator_operators, method_end)
{
    bin_tree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    auto it = tree.cend("in_order");
    --it;
    EXPECT_EQ(*it, 30);
}

TEST(test_bin_tree, basic_constructor)
{
    bin_tree<int> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(test_bin_tree, copy_constructor)
{
    bin_tree<int> tree_one;
    tree_one.insert(1);
    tree_one.insert(2);
    tree_one.insert(3);
    bin_tree<int> tree_two(tree_one);
    EXPECT_FALSE(tree_two.is_empty());
    auto it = tree_two.begin("in_order");
    EXPECT_EQ(*it, 2);
}

TEST(test_bin_tree_operators, operator_equality)
{
    bin_tree<int> tree_one;
    tree_one.insert(1);
    tree_one.insert(2);
    tree_one.insert(3);
    bin_tree<int> tree_two;
    tree_two.insert(1);
    tree_two.insert(2);
    tree_two.insert(3);
    EXPECT_TRUE(tree_one == tree_two);
    tree_two.insert(4);
    EXPECT_FALSE(tree_one == tree_two);
}

TEST(test_bin_tree_operators, operator_nonequality)
{
    bin_tree<int> tree_one;
    tree_one.insert(1);
    tree_one.insert(2);
    tree_one.insert(3);
    bin_tree<int> tree_two;
    tree_two.insert(1);
    tree_two.insert(2);
    tree_two.insert(3);
    EXPECT_FALSE(tree_one != tree_two);
    tree_two.insert(4);
    EXPECT_TRUE(tree_one != tree_two);
}

TEST(test_bin_tree_functions, method_insert)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    EXPECT_FALSE(tree.is_empty());
    auto it = tree.begin("in_order");
    EXPECT_EQ(*it, 2);
}

TEST(test_bin_tree_functions, method_remove)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.remove(2);
    auto it = tree.begin("in_order");
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(test_bin_tree_functions, method_find)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto node = tree.find(2);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->get_data(), 2);
}

TEST(test_bin_tree_functions, method_find_min)
{
    bin_tree<int> tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    auto node = tree.find_min();
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->get_data(), 1);
}

TEST(test_bin_tree_functions, method_find_max)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    auto node = tree.find_max();
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->get_data(), 3);
}

TEST(test_bin_tree_functions, method_clear)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(test_bin_tree_functions, method_is_empty)
{
    bin_tree<int> tree;
    EXPECT_TRUE(tree.is_empty());
    tree.insert(1);
    EXPECT_FALSE(tree.is_empty());
}

TEST(test_bin_tree_functions, method_get_subtree)
{
    bin_tree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    auto subtree = tree.get_subtree(1);
    EXPECT_NE(subtree, nullptr);
    EXPECT_EQ(subtree->find(1)->get_data(), 1);
}

TEST(test_bin_tree_functions, method_concat)
{
    bin_tree<int> tree_one;
    tree_one.insert(1);
    tree_one.insert(2);
    tree_one.insert(3);
    bin_tree<int> tree_two;
    tree_two.insert(4);
    tree_two.insert(5);
    tree_two.insert(6);
    tree_one.concat(tree_two);
    auto it = tree_one.begin("in_order");
    EXPECT_EQ(*it, 4);
    ++it;
    ++it;
    EXPECT_EQ(*it, 5);
}

TEST(test_bin_tree_functions, method_immutable_insert)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    auto new_tree = tree.immutable_insert(3);
    EXPECT_EQ(tree.find(3), nullptr);
    EXPECT_NE(new_tree->find(3), nullptr);
}

TEST(test_bin_tree_functions, method_immutable_remove)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto new_tree = tree.immutable_remove(2);
    EXPECT_NE(tree.find(2), nullptr);
    EXPECT_EQ(new_tree->find(2), nullptr);
}

TEST(test_bin_tree_functions, method_immutable_concat)
{
    bin_tree<int> tree_one;
    tree_one.insert(1);
    tree_one.insert(2);
    bin_tree<int> tree_two;
    tree_two.insert(3);
    tree_two.insert(4);
    auto new_tree = tree_one.immutable_concat(tree_two);
    EXPECT_EQ(tree_one.find(3), nullptr);
    EXPECT_NE(new_tree->find(3), nullptr);
}