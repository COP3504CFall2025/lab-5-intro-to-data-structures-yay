#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABQ(){
        array_ = new T[1];
        curr_size_ = 0;
        capacity_ = 1;
    };
    explicit ABQ(const size_t capacity){
        array_ = new T[capacity];
        curr_size_ = 0;
        capacity_ = capacity;
    };
    ABQ(const ABQ& other){
        array_ = new T[other.capacity_];
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        for(size_t i = 0; i < curr_size_; ++i){
            array_[i] = other.array_[i];
        }
    };
    ABQ& operator=(const ABQ& rhs){
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
    ABQ(ABQ&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    };
    ABQ& operator=(ABQ&& rhs) noexcept{
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
    ~ABQ() noexcept override{
        delete[] array_;
        array_ = nullptr;
        curr_size_ = 0;
        capacity_ = 0;
    };

    // Get the number of items in the ABQ
    [[nodiscard]] size_t getSize() const noexcept override{
        return curr_size_;
    };

    // Get the max size of the ABQ
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    };

    // Return underlying data for the queue
    [[nodiscard]] T* getData() const noexcept{
        return array_;
    };

    // Add item to the queue
    void enqueue(const T& data) override{
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
            throw std::runtime_error("Empty queue");
        }
        return array_[0];
    };

    T dequeue() override{
        if (curr_size_ == 0){
            throw std::runtime_error("Empty queue");
        }
        T data = array_[0];
        for (size_t i = 0; i < curr_size_ - 1; ++i) {
            array_[i] = array_[i + 1];
        }
        curr_size_--;
        
        if (curr_size_*4 <= capacity_) {
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