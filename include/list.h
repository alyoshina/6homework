#pragma once

#include "ilist.h"

template <typename T>
class List : public IList <T> {

public:
    List();
    List(std::initializer_list <T> l);
    List(const List& other);
    List(List&& other);
    virtual ~List();

    void push_front(const T& value) override;
    void push_back(const T& value) override;
    void insert(std::size_t pos, const T& value) override;
    void erase(std::size_t pos) override;
    void clear() override;
    virtual List<T>& operator=(const List<T>& rhs);
    virtual List<T>& operator=(List<T>&& rhs);

protected:
    class Node : public IList<T>::INode {

    public:
        Node(typename IList<T>::INode* p, typename IList<T>::INode* n, T d)
            : m_prev(p)
            , m_next(n)
            , m_data(d) { };
        ~Node() {};
        typename IList<T>::INode* prev() { return m_prev; };
        typename IList<T>::INode* next() { return m_next; };
        T& data() { return m_data; };
        void setData(T v) { m_data = v; };
        void setPrev(typename IList<T>::INode* v) { m_prev = v; };
        void setNext(typename IList<T>::INode* v) { m_next = v; };

    private:
        typename IList<T>::INode* m_prev;
        typename IList<T>::INode* m_next;
        T m_data;
    };
};

#include "list.ipp"