#pragma once

#include "container.h"
#include <initializer_list>

template <typename T>
class Serial : public IContainer <T> {

public:
    Serial();
    Serial(std::initializer_list <T> l);
    Serial(const Serial& other);
    Serial(Serial&& other);
    virtual ~Serial();

    void push_front(const T& value) override;
    void push_back(const T& value) override;
    void insert(std::size_t pos, const T& value) override;
    void erase(std::size_t pos) override;
    void clear() override;
    std::size_t size() const override;
    T& operator[] (std::size_t pos) const override;
    virtual Serial<T>& operator=(const Serial<T>& rhs);
    virtual Serial<T>& operator=(Serial<T>&& rhs);

private:
    std::size_t m_size;
    std::size_t m_capasity;
    const std::size_t min_capasity{5};
    const double m_coeff{1.6};
    T* m_data;
    void allocate_memory(std::size_t size);

public:
    struct Iterator {
        Iterator operator=(const Iterator& rhs) const {
            return Iterator{.index = rhs.index, .data = rhs.data};
        };
        Iterator& operator++() {
            index++;
            return *this;
        };
        bool operator!=(const Iterator& rhs) const {
            return index != rhs.index;
        };
        T operator*() const {
            return get();
        };
        T get() const {
            return data[index];
        };
        std::size_t index{0};
        T* data;
    };

    Iterator begin() const {return Iterator{.index = 0, .data = m_data};};
    Iterator end() const {return Iterator{.index = m_size, .data = m_data};};
};

#include "serial_container.ipp"