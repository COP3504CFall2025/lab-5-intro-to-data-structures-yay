#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLDQ(){
        list = LinkedList<T>();
    };

    // Insertion
    void pushFront(const T& item) override{
        list.addHead(item);
    };
    void pushBack(const T& item) override{
        list.addTail(item);
    };

    // Deletion
    T popFront() override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    };
    T popBack() override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }
        T data = list.getTail()->data;
        list.removeTail();
        return data;
    };

    // Access
    const T& front() const override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }
        return list.getHead()->data;
    };
    const T& back() const override{
        if (list.getCount() == 0){
            throw std::runtime_error("Empty deque");
        }
        return list.getTail()->data;
    };

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    };
};