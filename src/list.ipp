#include <stdexcept>
#include <iostream>

template <typename T>
List<T>::List() 
    : m_size{0}
    , m_first{nullptr}
    , m_last{nullptr} {

}

template <typename T>
List<T>::List(std::initializer_list <T> l) 
    : m_size{0}
    , m_first{nullptr}
    , m_last{nullptr} {
    
    for (T value : l) {
        push_back(value);
    }
}

template <typename T>
List<T>::~List() {
    Node<T>* node = m_first;
    while (node) {
        Node<T>* next = node->next;
        delete node;
        node = next;
    }
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node<T>* new_node = new Node<T>{.prev = nullptr, .next = m_first, .data = value};
    if (!m_last) {
        m_last = new_node;
    }
    if (m_first) {
        m_first->prev = new_node;
    }
    m_first = new_node;
    m_size++;
    return;
}

template <typename T>
void List<T>::push_back(const T& value) {
    Node<T>* new_node = new Node<T>{.prev = m_last, .next = nullptr, .data = value};
    if (!m_first) {
        m_first = new_node;
    }
    if (m_last) {
        m_last->next = new_node;
    }
    m_last = new_node;
    m_size++;
    return;
}

template <typename T>
void List<T>::insert(const std::size_t pos, const T& value) {
    if (pos >= m_size) {
        throw std::out_of_range("List: out of range");
    }
    Node<T>* node = m_first;
    for (int i = 0; i < m_size; ++i, node = node->next) {
        if (pos == i) {
            Node<T>* new_node = new Node<T>{.prev = node->prev, .next = node, .data = value};
            if (!node->prev) {
                m_first = new_node;
            } else {
                node->prev->next = new_node;
            }
            node->prev = new_node;
            m_size++;
            break;
        }   
    }
    return;
}

template <typename T>
void List<T>::erase(const std::size_t pos) {
    if (pos >= m_size) {
        throw std::out_of_range("List: out of range");
    }
    Node<T>* node = m_first;
    for (int i = 0; i < m_size; ++i, node = node->next) {
        if (pos == i) {
            if (!node->prev) {
                m_first = node->next;
            } else {
                node->prev->next = node->next;
            }       
            if (!node->next) {
                m_last = node->prev;
            } else {
                node->next->prev = node->prev;
            }
            m_size--;
            delete node;
            break;
        }
    }
    return;
}

template <typename T>
std::size_t List<T>::size() const {
    return m_size;
}

template <typename T>
T& List<T>::operator[] (const std::size_t pos) const {
    if (pos >= m_size) {
        throw std::out_of_range("List: out of range"); 
    }
    Node<T>* node = m_first;
    for (int i = 0; i < m_size; ++i, node = node->next) {
        if (pos == i) {
            break;
        }
    }
    return node->data;
}