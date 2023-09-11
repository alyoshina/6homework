#include <stdexcept>
#include <iostream>

template <typename T>
List<T>::List() : IList<T>() {
}

template <typename T>
List<T>::List(std::initializer_list <T> l) : IList<T>() {
    for (T value : l) {
        push_back(value);
    }
}

template <typename T>
List<T>::List(const List& other) : IList<T>(){
    *this = other;
}

template <typename T>
List<T>::List(List&& other) : IList<T>() {
    *this = std::move(other);
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::clear() {
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
List<T>& List<T>::operator=(const List<T>& rhs) {
    if (&rhs != this) {
        List<T> temp;
        typename IList<T>::INode* rhs_node = rhs.m_first;
        for (std::size_t i = 0; i < rhs.m_size; ++i, rhs_node = rhs_node->next()) {
            temp.push_back(rhs_node->data());
        }
        *this = std::move(temp);
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& rhs) {
    if (&rhs != this) {
        clear();
        this->move(&rhs);
    }
    return *this;
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node* new_node = new Node(nullptr, this->m_first, value);
    if (!this->m_last) {
        this->m_last = new_node;
    }
    if (this->m_first) {
        this->m_first->setPrev(new_node);
    }
    this->m_first = new_node;
    this->m_size++;
}

template <typename T>
void List<T>::push_back(const T& value) {
    this->push_back_node(new Node{this->m_last, nullptr, value});
}

template <typename T>
void List<T>::insert(const std::size_t pos, const T& value) {
    if (pos >= this->m_size) {
        throw std::out_of_range("List: out of range");
    }
    typename IList<T>::INode* node = this->m_first;
    for (std::size_t i = 0; i < this->m_size; ++i, node = node->next()) {
        if (pos == i) {
            Node* new_node = new Node(node->prev(), node, value);
            if (!node->prev()) {
                this->m_first = new_node;
            } else {
                node->prev()->setNext(new_node);
            }
            node->setPrev(new_node);
            this->m_size++;
            break;
        }   
    }
}

template <typename T>
void List<T>::erase(const std::size_t pos) {
    if (pos >= this->m_size) {
        throw std::out_of_range("List: out of range");
    }
    typename IList<T>::INode* node = this->m_first;
    for (std::size_t i = 0; i < this->m_size; ++i, node = node->next()) {
        if (pos == i) {
            if (!node->prev()) {
                this->m_first = node->next();
            } else {
                node->prev()->setNext(node->next());
            }       
            if (!node->next()) {
                this->m_last = node->prev();
            } else {
                node->next()->setPrev(node->prev());
            }
            this->m_size--;
            delete node;
            break;
        }
    }
}