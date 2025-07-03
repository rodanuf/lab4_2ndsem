#pragma once

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
        int height;

    public:
        node();
        node(const T &value);
        ~node();
        node *get_parent();
        node *get_left();
        node *get_right();
        T &get_data() const;
        int get_height();
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
    node *root;

public:
    class bin_iterator
    {
    private:
        node *current;
        std::vector<node *> nodes;
        int recent;

        void build_in_order(node *point);
        void build_pre_order(node *point);
        void build_post_order(node *point);

    public:
        bin_iterator(node *root, std::string order = "in_order");
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
        node *current;
        std::vector<node *> nodes;
        int recent;

    public:
        const_bin_iterator(node *root, std::string order = "in_order");
        const T &operator*() const;
        const_bin_iterator &operator++();
        const_bin_iterator operator++(int);
        const_bin_iterator &operator--();
        const_bin_iterator operator--(int);
        bool operator==(const const_bin_iterator &other) const;
        bool operator!=(const const_bin_iterator &other) const;
    };
    bin_iterator begin(std::string order = "in_order");
    bin_iterator end(std::string order = "in_order");
    const_bin_iterator cbegin(std::string order = "in_order") const;
    const_bin_iterator cend(std::string order = "in_order") const;
    bin_tree();
    bin_tree(const bin_iterator &other);
    ~bin_tree();
    node *get_root() const;
    node *find(const T &value);
    node *find_min();
    node *find_max();
    node *get_parent(node *point);
    void balance();
    void clear();
    bool operator==(const bin_tree &other) const;
    bool operator!=(const bin_tree &other) const;
    bin_tree &operator=(const bin_tree &other);
    bin_tree *insert(const T &value);
    bin_tree *remove(const T &value);
    bin_tree *map(std::function<T(T)> func);
    bin_tree *where(std::function<bool(T)> func);
    bin_tree *merge(const bin_tree &other);
    bin_tree *immutable_merge(const bin_tree &other) const;
};

#include "../templates/bin_tree.tpp"