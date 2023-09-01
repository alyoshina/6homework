#pragma once

#include "container.h"
#include <initializer_list>

template <typename T>
class Serial : public IContainer <T> {

public:
    Serial();
    Serial(std::initializer_list <T> l);
    virtual ~Serial();

    void push_front(const T& value) override;
    void push_back(const T& value) override;
    void insert(const std::size_t pos, const T& value) override;
    void erase(const std::size_t pos) override;
    std::size_t size() const override;
    T& operator[] (std::size_t pos) const override;

private:
    std::size_t m_size;
    T* m_data;
};

#include "serial_container.ipp"