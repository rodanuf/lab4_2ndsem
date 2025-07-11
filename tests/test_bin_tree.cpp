#include <gtest/gtest.h>
#include "../headers/bin_tree.hpp"

TEST(test_bin_tree_node, base_constructor)
{
    bin_tree<int>::node node;
    EXPECT_EQ(node.get_data(), int());
    EXPECT_EQ(node.get_left(), nullptr);
    EXPECT_EQ(node.get_right(), nullptr);
    EXPECT_EQ(node.get_height(), 0);
}

TEST(test_bin_tree_node, value_constructor)
{
    bin_tree<int>::node node(42);
    EXPECT_EQ(node.get_data(), 42);
    EXPECT_EQ(node.get_left(), nullptr);
    EXPECT_EQ(node.get_right(), nullptr);
    EXPECT_EQ(node.get_height(), 0);
}

TEST(test_bin_tree_node_functions, method_get_parent)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto child = tree.find(3);
    auto parent = child->get_parent(tree.get_root());
    EXPECT_EQ(parent->get_data(), 1);
}

TEST(test_bin_tree_node_functions, method_get_left)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto node = tree.find(2);
    auto node_left = node->get_left();
    EXPECT_EQ(node_left->get_data(), 4);
}

TEST(test_bin_tree_node_functions, method_get_right)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto node = tree.find(2);
    auto node_right = node->get_right();
    EXPECT_EQ(node_right->get_data(), 5);
}

TEST(test_bin_tree_node_functions, method_clone)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto node = tree.find(3);
    auto clone_node = node->clone(node);
    EXPECT_EQ(clone_node->get_data(), 3);
    EXPECT_EQ(clone_node->get_left(), nullptr);
    EXPECT_EQ(clone_node->get_right(), nullptr);
    EXPECT_EQ(clone_node->get_height(), node->get_height());
}

TEST(test_bin_tree_node_functions, method_get_data)
{
    bin_tree<int>::node node(42);
    EXPECT_EQ(node.get_data(), 42);
    const bin_tree<int>::node const_node(100);
    EXPECT_EQ(const_node.get_data(), 100);
}

TEST(test_bin_tree_node_functions, method_get_height)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto node = tree.find(3);
    EXPECT_EQ(node->get_height(), 1);
}

TEST(test_bin_tree_node_functions, method_set_left)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto node = tree.find(3);
    bin_tree<int>::node *new_left_node = new bin_tree<int>::node(6);
    node->set_left(new_left_node);
    EXPECT_EQ(node->get_left()->get_data(), 6);
}

TEST(test_bin_tree_node_functions, method_set_right)
{
    bin_tree<int> tree = {1, 2, 3, 4, 5};
    auto node = tree.find(3);
    bin_tree<int>::node *new_right_node = new bin_tree<int>::node(6);
    node->set_right(new_right_node);
    EXPECT_EQ(node->get_right()->get_data(), 6);
}

TEST(test_bin_tree_node, method_set_data)
{
    bin_tree<int>::node node(42);
    node.set_data(100);
    EXPECT_EQ(node.get_data(), 100);
}

TEST(test_bin_tree_node, method_set_height)
{
    bin_tree<int>::node node(42);
    node.set_height(2);
    EXPECT_EQ(node.get_height(), 2);
}

TEST(test_bin_tree_node, method_is_leaf)
{
    bin_tree<int>::node node(42);
    EXPECT_TRUE(node.is_leaf());
    node.set_left(new bin_tree<int>::node(10));
    EXPECT_FALSE(node.is_leaf());
}

TEST(test_bin_tree_node_operators, operator_equality)
{
    bin_tree<int>::node node_one(42);
    bin_tree<int>::node node_two(42);
    EXPECT_TRUE(node_one == node_two);
    node_two.set_data(100);
    EXPECT_FALSE(node_one == node_two);
}

TEST(test_bin_tree_node_operators, operator_nonequality)
{
    bin_tree<int>::node node_one(42);
    bin_tree<int>::node node_two(42);
    EXPECT_FALSE(node_one != node_two);
    node_two.set_data(100);
    EXPECT_TRUE(node_one != node_two);
}

TEST(test_bin_tree_node_operators, operator_less)
{
    bin_tree<int>::node node_one(10);
    bin_tree<int>::node node_two(20);
    EXPECT_TRUE(node_one < node_two);
    EXPECT_FALSE(node_two < node_one);
}

TEST(test_bin_tree_node_operators, operator_greater)
{
    bin_tree<int>::node node_one(20);
    bin_tree<int>::node node_two(10);
    EXPECT_TRUE(node_one > node_two);
    EXPECT_FALSE(node_two > node_one);
}

TEST(test_bin_tree_node_operators, operator_assignment)
{
    bin_tree<int>::node node_one(42);
    node_one.set_left(new bin_tree<int>::node(10));
    bin_tree<int>::node node_two;
    node_two = node_one;
    EXPECT_EQ(node_two.get_data(), 42);
    EXPECT_NE(node_two.get_left(), nullptr);
    EXPECT_EQ(node_two.get_left()->get_data(), 10);
}

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

TEST(test_bin_tree_functions, method_map)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto new_tree = tree.map([](int x)
                             { return x * 2; });
    auto it = new_tree->begin("in_order");
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 6);
}

TEST(test_bin_tree_functions, method_where)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    auto new_tree = tree.where([](int x)
                               { return x % 2 == 1; });
    auto it = new_tree->begin("in_order");
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 1);
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

TEST(test_bin_tree_functions, method_reduce)
{
    bin_tree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    int sum = tree.reduce([](int a, int b)
                          { return a + b; }, 0);
    EXPECT_EQ(sum, 6);
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