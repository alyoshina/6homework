#pragma once

template <typename T>
class IContainer {

public:
    IContainer() {};
    virtual ~IContainer() {};

    virtual void push_front(const T& value) = 0;
    virtual void push_back(const T& value) = 0;
    virtual void insert(const std::size_t pos, const T& value) = 0;
    virtual void erase(const std::size_t pos) = 0;
    virtual std::size_t size() const = 0;
    virtual T& operator [] (std::size_t pos) const = 0;
};

