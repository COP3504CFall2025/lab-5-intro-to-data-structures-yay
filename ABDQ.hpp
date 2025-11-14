#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABDQ : public DequeInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABDQ(){
        array_ = new T[4];
        curr_size_ = 0;
        capacity_ = 4;
        front_ = 0;
        back_ = 0;
    };
    explicit ABDQ(const size_t capacity){
        array_ = new T[capacity];
        curr_size_ = 0;
        capacity_ = capacity;
        front_ = 0;
        back_ = 0;
    };
    ABDQ(const ABDQ& other){
        array_ = new T[other.capacity_];
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        for(size_t i = 0; i < capacity_; ++i){
            array_[i] = other.array_[i];
        }
    };
    ABDQ& operator=(const ABDQ& rhs){
        if(this == &rhs){
            return *this;
        }
        T* temp = new T[rhs.capacity_];
        delete[] array_;

        this->array_ = temp;
        this->curr_size_ = rhs.curr_size_;
        this->capacity_ = rhs.capacity_;
        this->front_ = rhs.front_;
        this->back_ = rhs.back_;
        for(size_t i = 0; i < capacity_; ++i){
            array_[i] = rhs.array_[i];
        }

        return *this;
    };
    ABDQ(ABDQ&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    };
    ABDQ& operator=(ABDQ&& rhs) noexcept{
        if(this == &rhs){
            return *this;
        }
        delete[] array_;

        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        rhs.front_ = 0;
        rhs.back_ = 0;

        return *this;
    };
    ~ABDQ() noexcept override{
        delete[] array_;
        array_ = nullptr;
        curr_size_ = 0;
        capacity_ = 0;
        front_ = 0;
        back_ = 0;
    };

    // Get the number of items in the ABDQ
    [[nodiscard]] size_t getSize() const noexcept override{
        return curr_size_;
    };

    // Get the max size of the ABDQ
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    };

    // Return underlying data for the deque
    [[nodiscard]] T* getData() const noexcept{
        return array_;
    };

    // Add item to front of deque
    void pushFront(const T& data) override{
        if (curr_size_ == capacity_) {
            T* temp = new T[capacity_ * scale_factor_];
            for (size_t i = 0; i < curr_size_; ++i) {
                temp[i] = array_[(front_ + i) % capacity_];
            }
            delete[] array_;
            array_ = temp;
            front_ = 0;
            back_ = curr_size_;
            capacity_ *= scale_factor_;
        }
        front_ = (front_ - 1 + capacity_) % capacity_;
        array_[front_] = data;
        curr_size_++;
    };

    // Add item to back of deque
    void pushBack(const T& data) override{
        if (curr_size_ == capacity_) {
            T* temp = new T[capacity_ * scale_factor_];
            for (size_t i = 0; i < curr_size_; ++i) {
                temp[i] = array_[(front_ + i) % capacity_];
            }
            delete[] array_;
            array_ = temp;
            front_ = 0;
            back_ = curr_size_;
            capacity_ *= scale_factor_;
        }
        array_[back_] = data;
        back_ = (back_ + 1) % capacity_;
        curr_size_++;
    };

    // Remove and return front element
    T popFront() override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty deque");
        }
        T data = array_[front_];
        front_ = (front_ + 1) % capacity_;
        curr_size_--;
        if (curr_size_ * 4 <= capacity_) {
            size_t new_capacity = capacity_ / scale_factor_;
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < curr_size_; ++i) {
                temp[i] = array_[(front_ + i) % capacity_];
            }
            delete[] array_;
            array_ = temp;
            front_ = 0;
            back_ = curr_size_;
            capacity_ = new_capacity;
        }
        return data;
    };

    // Remove and return back element
    T popBack() override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty deque");
        }
        back_ = (back_ - 1 + capacity_) % capacity_;
        T data = array_[back_];
        curr_size_--;
        if (curr_size_ * 4 <= capacity_ && capacity_ > 4) {
            size_t new_capacity = capacity_ / scale_factor_;
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < curr_size_; ++i) {
                temp[i] = array_[(front_ + i) % capacity_];
            }
            delete[] array_;
            array_ = temp;
            front_ = 0;
            back_ = curr_size_;
            capacity_ = new_capacity;
        }
        return data;
    };

    // Access front element
    const T& front() const override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty deque");
        }
        return array_[front_];
    };

    // Access back element
    const T& back() const override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty deque");
        }
        return array_[(back_ - 1 + capacity_) % capacity_];
    };

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    size_t front_;
    size_t back_;
    static constexpr size_t scale_factor_ = 2;
};