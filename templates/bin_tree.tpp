#include <stdexcept>
#include "../headers/bin_tree.hpp"

template <typename T>
bin_tree<T>::node::node() : data(T()), left(nullptr), right(nullptr), height(0) {}

template <typename T>
bin_tree<T>::node::node(const T &value) : data(value), left(nullptr), right(nullptr), height(0) {}

template <typename T>
bin_tree<T>::node::~node() = default;

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::get_parent(node *root) const
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
    return parent;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::get_left()
{
    return left;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::node::get_left() const
{
    return left;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::get_right()
{
    return right;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::node::get_right() const
{
    return right;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::node::clone(const node *point)
{
    if (!point)
    {
        return nullptr;
    }
    node *new_node = new node(point->data);
    new_node->height = point->height;
    new_node->left = clone(point->left);
    new_node->right = clone(point->right);
    return new_node;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::node::clone(const node *point) const
{
    if (!point)
    {
        return nullptr;
    }
    node *new_node = new node(point->data);
    new_node->height = point->height;
    new_node->left = clone(point->left);
    new_node->right = clone(point->right);
    return new_node;
}

template <typename T>
T &bin_tree<T>::node::get_data()
{
    return data;
}

template <typename T>
const T &bin_tree<T>::node::get_data() const
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
    if (left)
    {
        left->height = this->height + 1;
    }
}

template <typename T>
void bin_tree<T>::node::set_right(node *right)
{
    this->right = right;
    if (right)
    {
        right->height = this->height + 1;
    }
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
    if (!point)
    {
        return;
    }
    std::stack<node *> st;
    node *current = point;
    while (current || !st.empty())
    {
        if (current)
        {
            st.push(current);
            current = current->get_left();
        }
        else
        {
            current = st.top();
            nodes.push_back(current);
            st.pop();
            current = current->get_right();
        }
    }
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
        if (current->get_right())
        {
            st.push(current->get_right());
        }
        if (current->get_left())
        {
            st.push(current->get_left());
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
            current = current->get_left();
        }
        else
        {
            node *peek = st.top();
            if (peek->get_right() && last != peek->get_right())
            {
                current = peek->get_right();
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
void bin_tree<T>::bin_iterator::build_level_order(node *point)
{
    if (!point)
    {
        return;
    }
    std::queue<node *> q;
    q.push(point);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        nodes.push_back(current);
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
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
        else if (order == "level_order")
        {
            build_level_order(root);
        }
        else
        {
            throw std::invalid_argument("Invalid order");
        }
    }
}

template <typename T>
void bin_tree<T>::bin_iterator::set_to_end()
{
    recent = nodes.size();
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

template <typename T>
typename bin_tree<T>::bin_iterator bin_tree<T>::begin(std::string order)
{
    return bin_iterator(root, order);
}

template <typename T>
typename bin_tree<T>::bin_iterator bin_tree<T>::end(std::string order)
{
    bin_iterator it(nullptr, order);
    if (root)
    {
        it = bin_iterator(root, order);
        it.set_to_end();
    }
    return it;
}

template <typename T>
void bin_tree<T>::const_bin_iterator::build_in_order(const node *point)
{
    if (!point)
    {
        return;
    }
    std::stack<const node *> st;
    const node *current = point;
    while (current || !st.empty())
    {
        if (current)
        {
            st.push(current);
            current = current->get_left();
        }
        else
        {
            current = st.top();
            nodes.push_back(current);
            st.pop();
            current = current->get_right();
        }
    }
}

template <typename T>
void bin_tree<T>::const_bin_iterator::build_pre_order(const node *point)
{
    if (!point)
    {
        return;
    }
    std::stack<const node *> st;
    const node *current = point;
    while (current || !st.empty())
    {
        nodes.push_back(current);
        current = st.top();
        st.pop();
        if (current->get_right())
        {
            st.push(current->get_right());
        }
        if (current->get_left())
        {
            st.push(current->get_left());
        }
    }
}

template <typename T>
void bin_tree<T>::const_bin_iterator::build_post_order(const node *point)
{
    if (!point)
    {
        return;
    }
    std::stack<const node *> st;
    const node *current = point;
    const node *last = nullptr;
    while (current || !st.empty())
    {
        if (current)
        {
            st.push(current);
            current = current->get_left();
        }
        else
        {
            const node *peek = st.top();
            if (peek->get_right() && last != peek->get_right())
            {
                current = peek->get_right();
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
void bin_tree<T>::const_bin_iterator::build_level_order(const node *point)
{
    if (!point)
    {
        return;
    }
    std::queue<const node *> q;
    q.push(point);
    while (!q.empty())
    {
        const node *current = q.front();
        q.pop();
        nodes.push_back(current);
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
}

template <typename T>
bin_tree<T>::const_bin_iterator::const_bin_iterator(const node *root, std::string order) : recent(0)
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
        else if (order == "level_order")
        {
            build_level_order(root);
        }
        else
        {
            throw std::invalid_argument("Invalid order");
        }
    }
}

template <typename T>
void bin_tree<T>::const_bin_iterator::set_to_end()
{
    recent = nodes.size();
}

template <typename T>
const T &bin_tree<T>::const_bin_iterator::operator*() const
{
    if (nodes.empty() || recent >= nodes.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    return nodes[recent]->get_data();
}

template <typename T>
typename bin_tree<T>::const_bin_iterator &bin_tree<T>::const_bin_iterator::operator++()
{
    if (nodes.empty() || recent >= nodes.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    recent++;
    return *this;
}

template <typename T>
typename bin_tree<T>::const_bin_iterator bin_tree<T>::const_bin_iterator::operator++(int)
{
    if (nodes.empty() || recent >= nodes.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    const_bin_iterator temp = *this;
    recent++;
    return temp;
}

template <typename T>
typename bin_tree<T>::const_bin_iterator &bin_tree<T>::const_bin_iterator::operator--()
{
    if (nodes.empty() || recent <= 0)
    {
        throw std::out_of_range("Iterator out of range");
    }
    recent--;
    return *this;
}

template <typename T>
typename bin_tree<T>::const_bin_iterator bin_tree<T>::const_bin_iterator::operator--(int)
{
    if (nodes.empty() || recent <= 0)
    {
        throw std::out_of_range("Iterator out of range");
    }
    const_bin_iterator temp = *this;
    recent--;
    return temp;
}

template <typename T>
bool bin_tree<T>::const_bin_iterator::operator==(const const_bin_iterator &other) const
{
    return recent == other.recent;
}

template <typename T>
bool bin_tree<T>::const_bin_iterator::operator!=(const const_bin_iterator &other) const
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

template <typename T>
typename bin_tree<T>::const_bin_iterator bin_tree<T>::cbegin(std::string order) const
{
    return const_bin_iterator(root, order);
}

template <typename T>
typename bin_tree<T>::const_bin_iterator bin_tree<T>::cend(std::string order) const
{
    const_bin_iterator it(nullptr, order);
    if (root)
    {
        it = const_bin_iterator(root, order);
        it.set_to_end();
    }
    return it;
}

template <typename T>
bin_tree<T>::bin_tree() : root(nullptr) {}

template <typename T>
bin_tree<T>::bin_tree(const node *root) : root(nullptr)
{
    if (root == nullptr)
    {
        throw std::invalid_argument("Root is nullptr");
    }
    this->root->clone(root);
}

template <typename T>
bin_tree<T>::bin_tree(const int &size) : root(nullptr)
{
    if (size < 0)
    {
        throw std::invalid_argument("Size cann't be negative");
    }
    for (int i = 0; i < size; i++)
    {
        this->insert(T());
    }
}

template <typename T>
bin_tree<T>::bin_tree(const T *data, const int &size) : root(nullptr)
{
    if (data == nullptr && size > 0)
    {
        throw std::invalid_argument("array is empty");
    }
    if (size < 0)
    {
        throw std::invalid_argument("Size cann't be negative");
    }
    for (int i = 0; i < size; i++)
    {
        this->insert(data[i]);
    }
}

template <typename T>
bin_tree<T>::bin_tree(const std::initializer_list<T> &list) : root(nullptr)
{
    for (int i = 0; i < list.size(); i++)
    {
        this->insert(*(list.begin() + i));
    }
}

template <typename T>
bin_tree<T>::bin_tree(const bin_tree<T> &other) : root(nullptr)
{
    if (other.root)
    {
        root = root->clone(other.root);
    }
}

template <typename T>
bin_tree<T>::~bin_tree()
{
    clear();
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::get_root()
{
    return root;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::get_root() const
{
    return root;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::find(const T &value)
{
    if (!root)
    {
        return nullptr;
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (current->get_data() == value)
        {
            return current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
    return nullptr;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::find(const T &value) const
{
    if (!root)
    {
        return nullptr;
    }
    std::queue<const node *> q;
    q.push(root);
    while (!q.empty())
    {
        const node *current = q.front();
        q.pop();
        if (current->get_data() == value)
        {
            return current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::find_min()
{
    if (!root)
    {
        return nullptr;
    }
    std::queue<node *> q;
    q.push(root);
    node *min = root;
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (current->get_data() < min->get_data())
        {
            min = current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
    return min;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::find_min() const
{
    if (!root)
    {
        return nullptr;
    }
    std::queue<const node *> q;
    q.push(root);
    const node *min = root;
    while (!q.empty())
    {
        const node *current = q.front();
        q.pop();
        if (current->get_data() < min->get_data())
        {
            min = current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
    return min;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::find_max()
{
    if (!root)
    {
        return nullptr;
    }
    std::queue<node *> q;
    q.push(root);
    node *max = root;
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (current->get_data() > max->get_data())
        {
            max = current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
    return max;
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::find_max() const
{
    if (!root)
    {
        return nullptr;
    }
    std::queue<const node *> q;
    q.push(root);
    const node *max = root;
    while (!q.empty())
    {
        const node *current = q.front();
        q.pop();
        if (current->get_data() > max->get_data())
        {
            max = current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
    return max;
}

template <typename T>
typename bin_tree<T>::node *bin_tree<T>::get_parent(node *point)
{
    if (!root || !point)
    {
        return nullptr;
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (current->get_left() == point || current->get_right() == point)
        {
            return current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
}

template <typename T>
const typename bin_tree<T>::node *bin_tree<T>::get_parent(node *point) const
{
    if (!root || !point)
    {
        return nullptr;
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (current->get_left() == point || current->get_right() == point)
        {
            return current;
        }
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
}

template <typename T>
void bin_tree<T>::clear()
{
    if (!root)
    {
        return;
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
        delete current;
    }
    root = nullptr;
}

template <typename T>
bool bin_tree<T>::is_empty() const
{
    if (!root)
    {
        return true;
    }
    return false;
}

template <typename T>
bool bin_tree<T>::operator==(const bin_tree<T> &other) const
{
    if (!root && !other.root)
    {
        return true;
    }
    if (!root || !other.root)
    {
        return false;
    }
    std::queue<node *> q1, q2;
    q1.push(root);
    q2.push(other.root);
    while (!q1.empty() && !q2.empty())
    {
        node *current1 = q1.front();
        q1.pop();
        node *current2 = q2.front();
        q2.pop();
        if (current1->get_data() != current2->get_data())
        {
            return false;
        }
        if (current1->get_left() && current2->get_left())
        {
            q1.push(current1->get_left());
            q2.push(current2->get_left());
        }
        else if (current1->get_left() || current2->get_left())
        {
            return false;
        }
        if (current1->get_right() && current2->get_right())
        {
            q1.push(current1->get_right());
            q2.push(current2->get_right());
        }
        else if (current1->get_right() || current2->get_right())
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool bin_tree<T>::operator!=(const bin_tree<T> &other) const
{
    return !(*this == other);
}

template <typename T>
T bin_tree<T>::reduce(std::function<T(T, T)> func, T init)
{
    for (auto it = cbegin("level_order"); it != cend("level_order"); ++it)
    {
        init = func(init, *it);
    }
    return init;
}

template <typename T>
typename bin_tree<T>::bin_tree &bin_tree<T>::operator+(const bin_tree &other) const
{
    bin_tree<T> *result_tree = new bin_tree(*this);
    result_tree->concat(other);
    return *result_tree;
}

template <typename T>
typename bin_tree<T>::bin_tree &bin_tree<T>::operator=(const bin_tree<T> &other)
{
    if (this != &other)
    {
        clear();
        if (other.root)
        {
            root = root->clone(other.root);
        }
    }
    return *this;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::insert(const T &value)
{
    if (!root)
    {
        root = new node(value);
        return this;
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        if (!current->get_left())
        {
            current->set_left(new node(value));
            return this;
        }
        else
        {
            q.push(current->get_left());
        }
        if (!current->get_right())
        {
            current->set_right(new node(value));
            return this;
        }
        else
        {
            q.push(current->get_right());
        }
    }
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::remove(const T &value)
{
    node *to_remove = find(value);
    if (!to_remove)
    {
        throw std::runtime_error("Value not found");
    }
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
    std::queue<node *> q;
    q.push(root);
    node *parent = nullptr;
    node *current = nullptr;
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        if (current->get_left())
        {
            q.push(current->get_left());
            parent = current;
        }
        if (current->get_right())
        {
            q.push(current->get_right());
            parent = current;
        }
    }
    if (to_remove == current)
    {
        if (parent)
        {
            if (parent->get_left() == current)
            {
                parent->set_left(nullptr);
            }
            else
            {
                parent->set_right(nullptr);
            }
        }
        else
        {
            root = nullptr;
        }
        delete current;
        return this;
    }
    to_remove->set_data(current->get_data());
    if (parent)
    {
        if (parent->get_left() == current)
        {
            parent->set_left(nullptr);
        }
        else
        {
            parent->set_right(nullptr);
        }
    }
    delete current;
    return this;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::get_subtree(const T &value) const
{
    const node *node = find(value);
    if (!node)
    {
        throw std::runtime_error("Value is missing");
    }
    bin_tree<T> *result = new bin_tree<T>();
    result->root = result->root->clone(node);
    return result;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::map(std::function<T(T)> func)
{
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
    std::queue<node *> q;
    q.push(root);
    while (!q.empty())
    {
        node *current = q.front();
        q.pop();
        current->set_data(func(current->get_data()));
        if (current->get_left())
        {
            q.push(current->get_left());
        }
        if (current->get_right())
        {
            q.push(current->get_right());
        }
    }
    return this;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::where(std::function<bool(T)> func)
{
    if (!root)
    {
        throw std::runtime_error("Tree is empty");
    }
    bin_tree<T> *result = new bin_tree<T>();
    for (auto it = cbegin(); it != cend(); ++it)
    {
        if (func(*it))
        {
            result->insert(*it);
        }
    }
    return result;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::concat(const bin_tree &other)
{
    for (auto it = other.cbegin(); it != other.cend(); ++it)
    {
        insert(*it);
    }
    return this;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::immutable_insert(const T &value) const
{
    bin_tree<T> *result = new bin_tree<T>(*this);
    result->insert(value);
    return result;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::immutable_remove(const T &value) const
{
    bin_tree<T> *result = new bin_tree<T>(*this);
    result->remove(value);
    return result;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::immutable_map(std::function<T(T)> func) const
{
    bin_tree<T> *result = new bin_tree<T>();
    for (auto it = cbegin(); it != cend(); ++it)
    {
        result->insert(func(*it));
    }
    return result;
}

template <typename T>
typename bin_tree<T>::bin_tree *bin_tree<T>::immutable_concat(const bin_tree &other) const
{
    bin_tree<T> *result = new bin_tree<T>(*this);
    for (auto it = other.cbegin(); it != other.cend(); ++it)
    {
        result->insert(*it);
    }
    return result;
}