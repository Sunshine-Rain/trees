//
//  SimpleQueue.h
//  BinaryTree
//
//  Created by quan on 2018/12/29.
//  Copyright © 2018 quan. All rights reserved.
//

#ifndef SimpleQueue_h
#define SimpleQueue_h

#include <iostream>

#define SimpleQueueDefaultCapacity 16

template <typename T>
class SimpleQueue {
    int _size, _capacity;
    T *_values;
    void expand() {
        T *newValues = new T[_capacity * 2];
        for (int i = 0; i < _size; i ++) newValues[i] = _values[i];
        _capacity *= 2;
        delete [] _values;
        _values = newValues;
    }
public:
    SimpleQueue():_size(0),_capacity(SimpleQueueDefaultCapacity) {
        _values = new T[_capacity];
    }
    ~SimpleQueue() {
        delete [] _values;
    }
    
    bool isEmpty() {
        return _size == 0;
    }
    
    void enqueue(T v) {
        if (_size == _capacity) expand();
        _values[_size++] = v;
    }
    
    T dequeue() {
        if(isEmpty()) assert(0);
        T retValue = _values[0];
        for (int i = 0; i < _size - 1; i++) {
            _values[i] = _values[i + 1];
        }
        _size -= 1;
        return retValue;
    }
};


#endif /* SimpleQueue_h */
