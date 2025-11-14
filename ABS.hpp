#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(){
        array_ = new T[1];
        curr_size_ = 0;
        capacity_ = 1;
    };
    explicit ABS(const size_t capacity){
        array_ = new T[capacity];
        curr_size_ = 0;
        capacity_ = capacity;
    };
    ABS(const ABS& other){
        array_ = new T[other.capacity_];
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        for(size_t i = 0; i < curr_size_; ++i){
            array_[i] = other.array_[i];
        }
    };
    ABS& operator=(const ABS& rhs){
        if(this == &rhs){
            return *this;
        }
        T* temp = new T[rhs.capacity_];
        delete[] array_;

        this->array_ = temp;
        this->curr_size_ = rhs.curr_size_;
        this->capacity_ = rhs.capacity_;
        for(size_t i = 0; i < curr_size_; ++i){
            array_[i] = rhs.array_[i];
        }

        return *this;
    };
    ABS(ABS&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    };
    ABS& operator=(ABS&& rhs) noexcept{
        if(this == &rhs){
            return *this;
        }
        delete[] array_;

        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;
        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;

        return *this;
    };
    ~ABS() noexcept override{
        delete[] array_;
        array_ = nullptr;
        curr_size_ = 0;
        capacity_ = 0;
    };

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{
        return curr_size_;
    };

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    };

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{
        return array_;
    };

    // Push item onto the stack
    void push(const T& data) override{
        if (curr_size_ == capacity_) {
            T* temp = new T[capacity_ * scale_factor_];
            for (size_t i = 0; i < curr_size_; ++i) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            capacity_ *= scale_factor_;
        }
        array_[curr_size_] = data;
        curr_size_++;
    };

    T peek() const override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty stack");
        }
        return array_[curr_size_ - 1];
    };

    T pop() override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty stack");
        }
        T data = array_[curr_size_ - 1];
        curr_size_--;
        
        if (curr_size_ > 0 && curr_size_ <= capacity_ / 4) {
            size_t new_capacity = capacity_ / scale_factor_;
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < curr_size_; ++i) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            capacity_ = new_capacity;
        }
        
        return data;
    };

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
