#include <iostream>
#include "serial_container.h"
#include "list.h"
#include "forward_list.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, IContainer<T>& v) {
    int size = static_cast<int> (v.size());
    for (int i = 0; i < size - 1 ; ++i) {
        os << v[i] << ", ";
    }
    if (v.size()) {
        os << v[size - 1] << " ";
    }
    return os; 
}

template <typename T>
class ContainerTest {
public:
    ContainerTest(const char* name, T *container) : cont(container) {
        test(name);
        iterTest(name);
    };
    ~ ContainerTest() {
        delete cont;
    };
    void trim(std::initializer_list <int> l) {
        int dec = 0;
        for (int i : l) {
            cont->erase(i - dec);
            dec++;
        }
    };
    void test(const char* name) {
        std::cout << "\n";
        std::cout << name << ": " << *cont << std::endl;
        std::cout << "size: " << cont->size() << std::endl;

        trim({2, 4, 6});
        std::cout << "erase 3, 5, 7, result: " << *cont << std::endl;

        cont->push_front(10);
        std::cout << "push front value 10, result: " << *cont << std::endl;

        cont->insert(cont->size()/2, 20);
        std::cout << "add element 20 to the middle, result: " << *cont << std::endl;

        cont->push_back(30);
        std::cout << "add element 30 to the end, result: " << *cont << std::endl;
    };
    void iterTest(const char* name) {
        std::cout << "iterator use: ";
        for (auto iter = cont->begin(); iter != cont->end(); ++iter) {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    };

private:
    T* cont;
};

int main(int argc, char **argv) {
    ContainerTest("serial", new Serial<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    ContainerTest("list", new List<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    ContainerTest("forwardList", new ForwardList<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
}