#include "../ui_headers/ui.hpp"
#include "../headers/bin_tree.hpp"
#include "../ui_headers/io_functions.hpp"

using namespace std;

void check_input(int &choice)
{
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Invalid input: programm cann't read letters");
    }
}

void run_types_menu()
{
    int type_choice;
    while (true)
    {
        cout << "===Main menu===" << endl;
        cout << "Choose data type: " << endl;
        cout << "1. Integer" << endl;
        cout << "2. Double" << endl;
        cout << "3. String" << endl;
        cout << "4. Complex" << endl;
        cout << "5. Student" << endl;
        cout << "6. Professor" << endl;
        cout << "0. Exit " << endl;
        try
        {
            check_input(type_choice);
            switch (type_choice)
            {
            case 1:
                set_tree_type<int>();
                break;
            case 2:
                set_tree_type<double>();
                break;
            case 3:
                set_tree_type<string>();
                break;
            case 4:
                set_tree_type<complex>();
                break;
            case 5:
                set_tree_type<student>();
                break;
            case 6:
                set_tree_type<professor>();
                break;
            case 0:
                exit(0);
            default:
                throw invalid_argument("Invalid choice");
                cout << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
            continue;
        }
    }
}

template <typename T>
void set_tree_type()
{
    bin_tree<T> *tree = new bin_tree<T>();
    if (tree)
    {
        run_tree_menu(tree);
    }
}
template <typename T>
void run_tree_menu(bin_tree<T> *tree)
{
    int choice;
    T element;
    int index;
    int count;
    bin_tree<T> *buffer_tree = nullptr;
    while (true)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n=== Tree Menu ===" << endl;
        cout << "Choose option: " << endl;
        cout << "1. Get root" << endl;
        cout << "2. Get min element" << endl;
        cout << "3. Get max element" << endl;
        cout << "4. Get parent" << endl;
        cout << "5. Clear" << endl;
        cout << "6. Add element " << endl;
        cout << "7. Remove element" << endl;
        cout << "8. Concat with another " << endl;
        cout << "9. Immutable add element" << endl;
        cout << "10. Immutable remove element " << endl;
        cout << "11. Immutable concat with another " << endl;
        cout << "12. Print tree " << endl;
        cout << "13. Print all tree " << endl;
        cout << "0. Return to previous menu" << endl;

        try
        {
            check_input(choice);
            switch (choice)
            {
            case 1:
            {
                cout << "Root: " << tree->get_root()->get_data() << endl;
                break;
            }
            case 2:
            {

                cout << "Min element: " << tree->find_min()->get_data() << endl;
                break;
            }
            case 3:
            {
                cout << "Max element: " << tree->find_max()->get_data() << endl;
            }
            case 4:
            {
                cout << "Choose element: ";
                cin >> element;
                cout << "Parent: " << tree->find(element)->get_parent()->get_data() << endl;
                break;
            }
            case 5:
            {
                tree->clear();
                if (tree->is_empty())
                {
                    cout << "Tree is empty" << endl;
                }
                break;
            }
            case 6:
            {
                cout << "Input element: ";
                cin >> element;
                tree = tree->insert(element);
                cout << "Elemnt added." << endl;
                std::cout << "Inserted: " << element << ", root = " << tree->get_root()->get_data() << std::endl;
                break;
            }
            case 7:
            {
                cout << "Choose element: ";
                cin >> element;
                tree = tree->remove(element);
                cout << "Element deleted." << endl;
                break;
            }
            case 8:
            {
                cout << "Creating a new tree to concat..." << endl;
                bin_tree<T> *other = new bin_tree<T>();
                cout << "Input count of elements: ";
                cin >> count;
                for (int i = 0; i < count; ++i)
                {
                    cout << "Element " << i << ": ";
                    cin >> element;
                    other = other->insert(element);
                }
                tree = tree->concat(*other);
                cout << "Trees were concatenated." << endl;
                delete other;
                break;
            }
            case 9:
            {
                cout << "Input element: " << endl;
                cin >> element;
                buffer_tree = tree->immutable_insert(element);
                cout << "Element added." << endl;
                break;
            }
            case 10:
            {
                cout << "Choose element: ";
                cin >> element;
                buffer_tree = tree->immutable_remove(element);
                cout << "Element added." << endl;
                break;
            }
            case 11:
            {
                cout << "Creating a new sequence to concat..." << endl;
                bin_tree<T> *other = new bin_tree<T>();
                cout << "Input count of elements: ";
                cin >> count;
                for (int i = 0; i < count; ++i)
                {
                    cout << "Element" << i << ": ";
                    cin >> element;
                    other = other->insert(element);
                }
                buffer_tree = tree->immutable_concat(*other);
                cout << "Trees were concatenated." << endl;
                delete other;
                break;
            }
            case 12:
            {
                cout << "Tree: " << std::endl;
                print_tree(*tree, true, 0);
                cout << endl;
                break;
            }
            case 13:
            {
                cout << "Tree: ";
                print_tree(*tree, true, 0);
                cout << endl;
                if (*buffer_tree != nullptr)
                {
                    cout << "Buffer tree: ";
                    print_tree(*buffer_tree, true, 0);
                    cout << endl;
                }
                break;
            }
            case 0:
            {
                delete tree;
                return;
            }
            default:
            {
                throw invalid_argument("Invalid choice");
                cout << endl;
            }
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
}
