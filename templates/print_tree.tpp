#include <iostream>
#include "../headers/bin_tree.hpp"

using namespace std;

template <typename T>
void print_tree(typename bin_tree<T>::node *point, bool is_left, int vertical)
{
    typename bin_tree<T>::node *current = point;
    if (!is_left && !current->is_leaf())
    {
        vertical++;
    }
    cout << current->get_data();
    if (current->get_right())
    {
        cout << "----";
        print_tree(current->get_right(), false, vertical);
    }
    if (!is_left && current->get_left())
    {
        cout << endl;
        bin_tree<T> tree = bin_tree<T>(current);
        for (int d = 0; d < tree->find_last_node()->get_height() - current->get_root()->get_height(); d++)
        {
            cout << "|";
            for (int i = 0; i < vertical; i++)
            {
                cout << "    |";
            }
            cout << endl;
        }
        cout << "|";
        for (int i = 0; i < vertical - 1; i++)
        {
            cout << "    |";
        }
        cout << "    ";
        vertical--;
        print_tree(current->get_left(), false, vertical);
    }
    if (is_left && current->get_left())
    {
        cout << endl;
        std::cout << "|" << endl;
        std::cout << "|" << endl;
        vertical = 0;
        print_tree(current->get_root()->get_left(), true, vertical);
        cout << endl;
    }
}
