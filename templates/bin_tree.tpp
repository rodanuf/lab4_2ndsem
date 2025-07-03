#include <vector>
#include <string>
#include <queue>
#include <stack>
#include "../headers/bin_tree.hpp"

template <typename T>
bin_tree<T>::node::node() : data(T()), left(nullptr), right(nullptr) {}

template <typename T>
bin_tree<T>::node::node(const T &value) : data(data), left(nullptr), right(nullptr) {}

template <typename T>
bin_tree<T>::node::~node()
{
    if (left)
    {
        delete left;
    }
    if (right)
    {
        delete right;
    }
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::get_parent()
{
    if (!root)
    {
        return nullptr;
    }
    node *current = root;
    node *parent = nullptr;
    while (current != this)
    {
        parent = current;
        if (current->data > this->data)
        {
            current = current->get_left();
        }
        else
        {
            current = current->get_right();
        }
    }
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::get_left()
{
    return left;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::get_right()
{
    return right;
}

template <typename T>
T &bin_tree<T>::node::get_data() const
{
    return data;
}

template <typename T>
int bin_tree<T>::node::get_height()
{
    return height;
}

template <typename T>
void bin_tree<T>::node::set_left(node *left)
{
    this->left = left;
}

template <typename T>
void bin_tree<T>::node::set_right(node *right)
{
    this->right = right;
}

template <typename T>
void bin_tree<T>::node::set_data(const T &data)
{
    this->data = data;
}

template <typename T>
void bin_tree<T>::node::set_height(int height)
{
    this->height = height;
}

template <typename T>
bool bin_tree<T>::node::is_leaf() const
{
    return (!left && !right);
}

template <typename T>
bool bin_tree<T>::node::operator==(const node &other) const
{
    return (data == other.data) && (right == other.right) && (left == other.left);
}

template <typename T>
bool bin_tree<T>::node::operator!=(const node &other) const
{
    return (data != other.data) || (right != other.right) || (left != other.left);
}

template <typename T>
bool bin_tree<T>::node::operator<(const node &other) const
{
    return data < other.data;
}

template <typename T>
bool bin_tree<T>::node::operator>(const node &other) const
{
    return data > other.data;
}

template <typename T>
typename bin_tree<T>::node &bin_tree<T>::node::operator=(const node &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete left;
    delete right;
    data = other.data;
    left = other.left;
    right = other.right;
    return *this;
}

template <typename T>
void bin_tree<T>::bin_iterator::build_in_order(node *point)
{
    if (!node)
    {
        return;
    }
    buildInOrder(node->getLeft());
    nodes.push_back(node);
    buildInOrder(node->getRight());
}

template <typename T>
void bin_tree<T>::bin_iterator::build_pre_order(node *point)
{
    if (!point)
    {
        return;
    }
    std::stack<node *> st;
    node *current = point;
    while (current || !st.empty())
    {
        nodes.push_back(current);
        current = st.top();
        st.pop();
        if (current->right)
        {
            st.push(current->right);
        }
        if (current->left)
        {
            st.push(current->left);
        }
    }
}

template <typename T>
bin_tree<T>::bin_iterator::bin_iterator(node *root, std::string order)
{
}