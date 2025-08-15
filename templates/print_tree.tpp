#include "../headers/bin_tree.hpp"

inline void print_spaces(int count)
{
    for (int i = 0; i < count; i++)
    {
        std::cout << " ";
    }
}

inline void print_lines(int count)
{
    for (int i = 0; i < count; i++)
    {
        std::cout << "|";
    }
}

template <typename T>
void print_tree(bin_tree<T> &tree, bool is_left, int vertical)
{
    print_tree_helper<T>(tree.get_root(), is_left, vertical);
}

template <typename T>
void print_tree_helper(typename bin_tree<T>::node *point, bool is_left, int vertical)
{
    typename bin_tree<T>::node *current = point;
    if (!is_left && !current->is_leaf())
    {
        vertical++;
    }
    std::cout << current->get_data();
    if (current->get_right())
    {
        std::cout << "----";
        print_tree_helper<T>(current->get_right(), false, vertical);
    }
    if (!is_left && current->get_left())
    {
        std::cout << std::endl;
        bin_tree<T> *tree = new bin_tree<T>(current);
        for (int d = 0; d < tree->find_last_node()->get_height() - current->get_height(); d++)
        {
            print_lines();
            for (int i = 0; i < vertical; i++)
            {
                print_spaces();
                print_lines();
            }
            std::cout << std::endl;
        }
        print_lines();
        for (int i = 0; i < vertical - 1; i++)
        {
            print_spaces();
            print_lines();
        }
        print_spaces();
        vertical--;
        delete tree;
        print_tree_helper<T>(current->get_left(), false, vertical);
    }
    if (is_left && current->get_left())
    {
        std::cout << std::endl;
        print_lines();
        std::cout << std::endl;
        print_lines();
        std::cout << std::endl;
        vertical = 0;
        print_tree_helper<T>(current->get_left(), true, vertical);
        std::cout << std::endl;
    }
}
