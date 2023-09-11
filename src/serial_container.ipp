#include <stdexcept>

template <typename T>
Serial<T>::Serial() 
    : m_size{0}
    , m_capasity{0}
    , m_data{nullptr} {

}

template <typename T>
Serial<T>::Serial(std::initializer_list <T> l) : Serial() {
    allocate_memory(l.size());
    std::size_t i = 0;
    for (T e : l) {
        m_data[i] = e;
        i++;
    }
}

template <typename T>
Serial<T>::Serial(const Serial& other) : Serial() {
    *this = other;
}

template <typename T>
Serial<T>::Serial(Serial&& other) : Serial() {
    *this = std::move(other);
}

template <typename T>
Serial<T>::~Serial() {
    clear();
}

template <typename T>
void Serial<T>::clear() {
    delete [] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capasity = 0;
}

template <typename T>
Serial<T>& Serial<T>::operator=(const Serial<T>& rhs) {
    if (&rhs != this) {
        T* data = new T[rhs.m_capasity];
        for (std::size_t i = 0; i < rhs.m_size; ++i) {
            data[i] = rhs.m_data[i];
        }
        clear();
        m_data = data;
        m_size = rhs.m_size;
        m_capasity = rhs.m_capasity;
    }
    return *this;
}

template <typename T>
Serial<T>& Serial<T>::operator=(Serial<T>&& rhs) {
    if (&rhs != this) {
        clear();
        m_data = rhs.m_data;
        rhs.m_data = nullptr;
        m_size = rhs.m_size;
        rhs.m_size = 0;
        m_capasity = rhs.m_capasity;
        rhs.m_capasity = 0;
    }
    return *this;
}

template <typename T>
void Serial<T>::allocate_memory(std::size_t size)
{
    T* data = m_data;
    std::size_t capasity = m_capasity;
    //need increase or reduce capasity
    if ((capasity <= size) 
            || (capasity > size * m_coeff + min_capasity)) {
        capasity = size * m_coeff;
    }
    if (capasity < min_capasity) {
        capasity = min_capasity;
    }
    //change size
    if (m_capasity != capasity) {
        data = new T[capasity];
        std::size_t copy_size = m_size > size ? size : m_size;
        for (std::size_t i = 0; i < copy_size; ++i) {
            data[i] = m_data[i];
        }
        delete [] m_data;
        m_capasity = capasity;
    }
    m_data = data;
    m_size = size;
}

template <typename T>
void Serial<T>::push_front(const T& value) {
    insert(0, value);
}

template <typename T>
void Serial<T>::push_back(const T& value) {
    allocate_memory(m_size + 1);
    m_data[m_size - 1] = value;
}

template <typename T>
void Serial<T>::insert(std::size_t pos, const T& value) {
    if (pos > m_size) {
        throw std::out_of_range("Serial: out of range");
    }
    allocate_memory(m_size + 1);
    for (std::size_t i = m_size - 1; i > pos; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[pos] = value;
}

template <typename T>
void Serial<T>::erase(std::size_t pos) {
    if (pos >= m_size) {
        throw std::out_of_range("Serial: out of range");
    }
    if (m_size > 1) {
        T value = m_data[m_size - 1];
        for (std::size_t i = m_size - 1; i > pos; --i) {
            T temp = m_data[i - 1];
            m_data[i - 1] = value;
            value = temp;
        }
    }
    allocate_memory(m_size - 1);
}

template <typename T>
std::size_t Serial<T>::size() const {
    return m_size;
}

template <typename T>
T& Serial<T>::operator[] (std::size_t pos) const {
    if (pos >= m_size) {
        throw std::out_of_range("Serial: out of range"); 
    }
    return m_data[pos];
}