#pragma once

#include "ilist.h"

template <typename T>
class ForwardList : public IList <T> {

public:
    ForwardList();
    ForwardList(std::initializer_list <T> l);
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other);
    virtual ~ForwardList();

    void push_front(const T& value) override;
    void push_back(const T& value) override;
    void insert(std::size_t pos, const T& value) override;
    void erase(std::size_t pos) override;
    void clear() override;
    virtual ForwardList<T>& operator=(const ForwardList<T>& rhs);
    virtual ForwardList<T>& operator=(ForwardList<T>&& rhs);

protected:
    class Node : public IList<T>::INode {

    public:
        Node(typename IList<T>::INode* n, T d)
            : m_next(n)
            , m_data(d) { };
        ~Node() {};
        typename IList<T>::INode* prev() { return nullptr; };
        typename IList<T>::INode* next() { return m_next; };
        T& data() { return m_data; };
        void setData(T v) { m_data = v; };
        void setPrev(typename IList<T>::INode* v) { };
        void setNext(typename IList<T>::INode* v) { m_next = v; };

    private:
        typename IList<T>::INode* m_next;
        T m_data;
    };
};

#include "forward_list.ipp"