#include <stdexcept>

template <typename T>
Serial<T>::Serial() 
    : m_size{0}
    , m_data{nullptr} {

}

template <typename T>
Serial<T>::Serial(std::initializer_list <T> l) 
    : m_size{l.size()}
    , m_data{new T[l.size()]} {

    int i = 0;
    for (T e : l) {
        m_data[i] = e;
        i++;
    }
}

template <typename T>
Serial<T>::~Serial() {
    delete [] m_data;
}

template <typename T>
void Serial<T>::push_front(const T& value) {
    insert(0, value);
    return;
}

template <typename T>
void Serial<T>::push_back(const T& value) {
    T* new_data = new T[m_size + 1];
    for (size_t i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }
    new_data[m_size] = value;
    delete [] m_data;
    m_data = new_data;
    m_size++;
    return;
}

template <typename T>
void Serial<T>::insert(const std::size_t pos, const T& value) {
    if (pos > m_size) {
        throw std::out_of_range("Serial: out of range");
    }
    T* new_data = new T[m_size + 1];
    for (size_t i = 0; i < pos; ++i) {
        new_data[i] = m_data[i];
    }
    new_data[pos] = value;
    for (size_t i = pos; i < m_size; ++i) {
        new_data[i + 1] = m_data[i];
    }
    m_size++;
    delete [] m_data;
    m_data = new_data;
    return;
}

template <typename T>
void Serial<T>::erase(const std::size_t pos) {
    if (pos >= m_size) {
        throw std::out_of_range("Serial: out of range");
    }
    T* new_data = new T[m_size - 1];
    for (size_t i = 0; i < pos; ++i) {
        new_data[i] = m_data[i];
    }    
    for (size_t i = pos + 1; i < m_size; ++i) {
        new_data[i - 1] = m_data[i];
    }
    m_size--;
    delete [] m_data;
    m_data = new_data;
    return;
}

template <typename T>
std::size_t Serial<T>::size() const {
    return m_size;
}

template <typename T>
T& Serial<T>::operator[] (const std::size_t pos) const {
    if (pos >= m_size) {
        throw std::out_of_range("Serial: out of range"); 
    }
    return m_data[pos];
}
