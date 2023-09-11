#include <stdexcept>
#include <iostream>

template <typename T>
ForwardList<T>::ForwardList() : IList<T>() {

}

template <typename T>
ForwardList<T>::ForwardList(std::initializer_list <T> l) : IList<T>() {
    for (T value : l) {
        push_back(value);
    }
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other) : IList<T>() {
    *this = other;
}

template <typename T>
ForwardList<T>::ForwardList(ForwardList&& other) : IList<T>() {
    *this = std::move(other);
}

template <typename T>
ForwardList<T>::~ForwardList() {
    clear();
}

template <typename T>
void ForwardList<T>::clear() {
    typename IList<T>::INode* node = this->m_first;
    while (node) {
        typename IList<T>::INode* next = node->next();
        delete node;
        node = next;
    }
    this->m_first = nullptr;
    this->m_last = nullptr;
    this->m_size = 0;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& rhs) {
    if (&rhs != this) {
        ForwardList<T> temp;
        typename IList<T>::INode* rhs_node = rhs.m_first;
        for (std::size_t i = 0; i < rhs.m_size; ++i, rhs_node = rhs_node->next()) {
            temp.push_back(rhs_node->data());
        }
        *this = std::move(temp);
    }
    return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& rhs) {
    if (&rhs != this) {
        clear();
        this->move(&rhs);
    }
    return *this;
}

template <typename T>
void ForwardList<T>::push_front(const T& value) {
    Node* new_node = new Node(this->m_first, value);
    if (!this->m_last) {
        this->m_last = new_node;
    }
    this->m_first = new_node;
    this->m_size++;
}

template <typename T>
void ForwardList<T>::push_back(const T& value) {
    this->push_back_node(new Node(nullptr, value));
    return;
}

template <typename T>
void ForwardList<T>::insert(std::size_t pos, const T& value) {
    if (pos >= this->m_size) {
        throw std::out_of_range("ForwardList: out of range");
    }
    typename IList<T>::INode* prev_node = nullptr;
    typename IList<T>::INode* node = this->m_first;
    for (std::size_t i = 0; i < this->m_size; ++i, prev_node = node, node = node->next()) {
        if (pos == i) {
            Node* new_node = new Node(node, value);
            if (prev_node) {
                prev_node->setNext(new_node);
            } else {
                this->m_first = new_node;
            }
            this->m_size++;
            break;
        }
    }
}

template <typename T>
void ForwardList<T>::erase(std::size_t pos) {
    if (pos >= this->m_size) {
        throw std::out_of_range("ForwardList: out of range");
    }
    typename IList<T>::INode* prev_node = nullptr;
    typename IList<T>::INode* node = this->m_first;
    for (std::size_t i = 0; i < this->m_size; ++i, prev_node = node, node = node->next()) {
        if (pos == i) {
            if (!prev_node) {
                this->m_first = node->next();
            } else {
                prev_node->setNext(node->next());
            }       
            if (!node->next()) {
                this->m_last = prev_node;
            }
            this->m_size--;
            delete node;
            break;
        }
    }
}
