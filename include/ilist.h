#pragma once

#include "container.h"
#include <initializer_list>
#include <iostream>

template <typename T>
class IList : public IContainer <T> {

public:
    IList();
    virtual ~IList() = default;

    virtual void push_front(const T& value) = 0;
    virtual void push_back(const T& value) {std::cout << "push_back IList" << std::endl;}; //=0
    virtual void insert(const std::size_t pos, const T& value) = 0;
    virtual void erase(const std::size_t pos) = 0;
    virtual void clear() = 0;
    std::size_t size() const override;
    T& operator[] (std::size_t pos) const override;
    IList<T>& operator=(IList<T>&& rhs);

protected:
    class INode {

    public:
        INode() {};
        virtual INode* prev() = 0;
        virtual INode* next() = 0;
        virtual T& data() = 0;
        virtual void setPrev(INode* v) = 0;
        virtual void setNext(INode* v) = 0;
        virtual void setData(T v) = 0;
    };
    
    std::size_t m_size;
    INode* m_first;
    INode* m_last;
    void move(IList<T>* rhs);
    void push_back_node(INode* n);

public:
    struct Iterator {
        Iterator operator=(const Iterator& rhs) const {
            return Iterator{.data = rhs.data};
        };
        Iterator& operator++() {
            data = data->next();
            return *this;
        };
        bool operator!=(const Iterator& rhs) const {
            return data != rhs.data;
        };
        T operator*() const {
            return data->data();
        };
        T get() const {
            return data->data();
        };
        INode* data;
    };

    Iterator begin() const {return Iterator{.data = m_first};};
    Iterator end() const {return Iterator{.data = m_last->next()};};
};

#include "ilist.ipp"