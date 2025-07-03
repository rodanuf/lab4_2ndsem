#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <stdexcept>
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
void bin_tree<T>::bin_iterator::build_post_order(node *point)
{
    if (!point)
    {
        return;
    }
    std::stack<node *> st;
    node *current = point;
    node *last = nullptr;
    while (current || !st.empty())
    {
        if (current)
        {
            st.push(current);
            current = current->left;
        }
        else
        {
            node *peek = st.top();
            if (peek->right && last != peek->right)
            {
                current = peek->right;
            }
            else
            {
                nodes.push_back(peek);
                last = peek;
                st.pop();
            }
        }
    }
}

template <typename T>
bin_tree<T>::bin_iterator::bin_iterator(node *root, std::string order) : recent(0)
{
    if (root)
    {
        if (order == "in_order")
        {
            build_in_order(root);
        }
        else if (order == "pre_order")
        {
            build_pre_order(root);
        }
        else if (order == "post_order")
        {
            build_post_order(root);
        }
        else
        {
            throw std::invalid_argument("Invalid order");
        }
    }
}

template <typename T>
T &bin_tree<T>::bin_iterator::operator*()
{
    if (nodes.empty() || recent >= nodes.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    return nodes[recent]->get_data();
}

template <typename T>
typename bin_tree<T>::bin_iterator &bin_tree<T>::bin_iterator::operator++()
{
    if (nodes.empty() || recent >= nodes.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    recent++;
    return *this;
}

template <typename T>
typename bin_tree<T>::bin_iterator bin_tree<T>::bin_iterator::operator++(int)
{
    if (nodes.empty() || recent >= nodes.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    bin_iterator temp = *this;
    recent++;
    return temp;
}

template <typename T>
typename bin_tree<T>::bin_iterator &bin_tree<T>::bin_iterator::operator--()
{
    if (nodes.empty() || recent <= 0)
    {
        throw std::out_of_range("Iterator out of range");
    }
    recent--;
    return *this;
}

template <typename T>
typename bin_tree<T>::bin_iterator bin_tree<T>::bin_iterator::operator--(int)
{
    if (nodes.empty() || recent <= 0)
    {
        throw std::out_of_range("Iterator out of range");
    }
    bin_iterator temp = *this;
    recent--;
    return temp;
}

template <typename T>
bool bin_tree<T>::bin_iterator::operator==(const bin_iterator &other) const
{
    return recent == other.recent;
}

template <typename T>
bool bin_tree<T>::bin_iterator::operator!=(const bin_iterator &other) const
{
    if (nodes.empty() || other.nodes.empty())
    {
        return true;
    }
    if (nodes.empty() && other.nodes.empty())
    {
        return false;
    }
    return recent != other.recent;
}