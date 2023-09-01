#include <iostream>
#include "serial_container.h"
#include "list.h"


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
void trim(IContainer<T>& v, std::initializer_list <int> l) {
    int dec = 0;
    for (int i : l) {
        v.erase(i - dec);
        dec++;
    }
}

template <typename T>
void test(const char* name, IContainer<T>& v)
{
    std::cout << name << ": " << v << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    trim(v, {2, 4, 6});
    std::cout << "erase 3, 5, 7, result: " << v << std::endl;

    v.push_front(10);
    std::cout << "push front value 10, result: " << v << std::endl;

    v.insert(v.size()/2, 20);
    std::cout << "add element 20 to the middle, result: " << v << std::endl;

    v.push_back(30);
    std::cout << "add element 30 to the end, result: " << v << std::endl;
}

int main(int argc, char **argv) {
    Serial<int> serial{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    List<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    test("serial", serial);
    test("list", list);
}