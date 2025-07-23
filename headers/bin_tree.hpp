#pragma once
#include "array_sequence.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <string>
#include <functional>
#include <initializer_list>

template <typename T>
class bin_tree;

template <typename T>
void print_tree_helper(typename bin_tree<T>::node *, bool, int);

template <typename T>
class bin_tree
{
private:
    class node
    {
    private:
        T data;
        node *left;
        node *right;
        node *parent;
        int height;

    public:
        node();
        node(const T &value);
        ~node();

        node *get_parent();
        const node *get_parent() const;
        node *get_left();
        const node *get_left() const;
        node *get_right();
        const node *get_right() const;
        node *clone(const node *point);
        const node *clone(const node *point) const;

        T &get_data();
        const T &get_data() const;

        int get_height();

        void set_parent(node *parent);
        void set_left(node *left);
        void set_right(node *right);
        void set_data(const T &value);
        void set_height(int value);

        bool is_leaf() const;
        bool operator==(const node &other) const;
        bool operator!=(const node &other) const;

        node &operator=(const node &other);
    };

    node *root;
    node *last_node;

public:
    class bin_iterator
    {
    private:
        array_sequence<node *> nodes;
        int recent;

        void build_in_order(node *point);
        void build_pre_order(node *point);
        void build_post_order(node *point);
        void build_level_order(node *point);

    public:
        bin_iterator(node *root, std::string order = "level_order");

        void set_to_end();

        T &operator*();

        bin_iterator &operator++();
        bin_iterator operator++(int);
        bin_iterator &operator--();
        bin_iterator operator--(int);
        bin_iterator &operator=(const bin_iterator &other);

        bool operator==(const bin_iterator &other) const;
        bool operator!=(const bin_iterator &other) const;
    };
    class const_bin_iterator
    {
    private:
        array_sequence<const node *> nodes;
        int recent;

        void build_in_order(const node *point);
        void build_pre_order(const node *point);
        void build_post_order(const node *point);
        void build_level_order(const node *point);

    public:
        const_bin_iterator(const node *root, std::string order = "level_order");

        void set_to_end();

        const T &operator*() const;

        const_bin_iterator &operator++();
        const_bin_iterator operator++(int);
        const_bin_iterator &operator--();
        const_bin_iterator operator--(int);
        const_bin_iterator &operator=(const const_bin_iterator &other);

        bool operator==(const const_bin_iterator &other) const;
        bool operator!=(const const_bin_iterator &other) const;
    };

    bin_iterator begin(std::string order = "level_order");
    bin_iterator end(std::string order = "level_order");
    const_bin_iterator cbegin(std::string order = "level_order") const;
    const_bin_iterator cend(std::string order = "level_order") const;

private:
    void bubble_up(node *point);
    void bubble_down(node *point);

    T reduce(std::function<T(T, T)> func, T init);

    bin_tree &operator+(const bin_tree &other) const;
    bin_tree &operator=(const bin_tree &other);

    bin_tree *map(std::function<T(T)> func);
    bin_tree *where(std::function<bool(T)> func);
    bin_tree *immutable_map(std::function<T(T)> func) const;

    friend void print_tree_helper<T>(typename bin_tree<T>::node *, bool, int);

public:
    bin_tree();
    bin_tree(const node *point);
    bin_tree(const int &size);
    bin_tree(const T *data, const int &size);
    bin_tree(const std::initializer_list<T> &list);
    bin_tree(const bin_tree &other);
    ~bin_tree();

    node *get_root();
    const node *get_root() const;
    node *find(const T &value);
    const node *find(const T &value) const;
    node *find_min();
    const node *find_min() const;
    node *find_max();
    const node *find_max() const;
    node *find_last_node();
    const node *find_last_node() const;
    node *get_parent(node *point);
    const node *get_parent(node *point) const;

    void clear();

    bool is_empty() const;
    bool operator==(const bin_tree &other) const;
    bool operator!=(const bin_tree &other) const;

    bin_tree *insert(const T &value);
    bin_tree *remove(const T &value);
    bin_tree *get_subtree(const T &value) const;
    bin_tree *get_left_subtree() const;
    bin_tree *get_right_subtree() const;
    bin_tree *concat(const bin_tree &other);
    bin_tree *immutable_insert(const T &value) const;
    bin_tree *immutable_remove(const T &value) const;
    bin_tree *immutable_concat(const bin_tree &other) const;
};

#include "print_tree.hpp"
#include "../templates/bin_tree.tpp"