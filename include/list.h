#pragma once

#include "container.h"
#include <initializer_list>

template <typename T>
struct Node {
    Node* prev;
    Node* next;
    T data;
};

template <typename T>
class List : public IContainer <T> {

public:
    List();
    List(std::initializer_list <T> l);
    virtual ~List();

    void push_front(const T& value) override;
    void push_back(const T& value) override;
    void insert(const std::size_t pos, const T& value) override;
    void erase(const std::size_t pos) override;
    std::size_t size() const override;
    T& operator[] (std::size_t pos) const override;

private:
    std::size_t m_size;
    Node<T>* m_first;
    Node<T>* m_last;
};

#include "list.ipp"