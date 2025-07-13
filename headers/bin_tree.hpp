#pragma once
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <functional>
#include <initializer_list>

template <typename T>
class bin_tree
{
public:
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
        bool operator<(const node &other) const;
        bool operator>(const node &other) const;
        node &operator=(const node &other);
    };

private:
    node *root;

public:
    class bin_iterator
    {
    private:
        std::vector<node *> nodes;
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
        bool operator==(const bin_iterator &other) const;
        bool operator!=(const bin_iterator &other) const;
    };
    class const_bin_iterator
    {
    private:
        std::vector<const node *> nodes;
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
        bool operator==(const const_bin_iterator &other) const;
        bool operator!=(const const_bin_iterator &other) const;
    };
    bin_iterator begin(std::string order = "level_order");
    bin_iterator end(std::string order = "level_order");
    const_bin_iterator cbegin(std::string order = "level_order") const;
    const_bin_iterator cend(std::string order = "level_order") const;
    bin_tree();
    bin_tree(const node *root);
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
    node *get_parent(node *point);
    const node *get_parent(node *point) const;
    void clear();
    void bubble_up(node *point);
    void bubble_down(node *point);
    bool is_empty() const;
    bool operator==(const bin_tree &other) const;
    bool operator!=(const bin_tree &other) const;
    T reduce(std::function<T(T, T)> func, T init);
    bin_tree &operator+(const bin_tree &other) const;
    bin_tree &operator=(const bin_tree &other);
    bin_tree *insert(const T &value);
    bin_tree *remove(const T &value);
    bin_tree *get_subtree(const T &value) const;
    bin_tree *map(std::function<T(T)> func);
    bin_tree *where(std::function<bool(T)> func);
    bin_tree *concat(const bin_tree &other);
    bin_tree *immutable_insert(const T &value) const;
    bin_tree *immutable_remove(const T &value) const;
    bin_tree *immutable_map(std::function<T(T)> func) const;
    bin_tree *immutable_concat(const bin_tree &other) const;
};

#include "../templates/bin_tree.tpp"