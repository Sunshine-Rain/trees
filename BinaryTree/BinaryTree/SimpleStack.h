//
//  SimpleStack.h
//  BinaryTree
//
//  Created by quan on 2018/12/28.
//  Copyright © 2018 quan. All rights reserved.
//

#ifndef SimpleStack_h
#define SimpleStack_h

#include <iostream>
#include <assert.h>

#define SimpleStackDefaultCap 16

template <typename T>
class SimpleStack {
    T * _values;
    int _size, _capacity, _currentIndex;
public:
    SimpleStack():_size(0),_capacity(SimpleStackDefaultCap),_currentIndex(0) {
        _values = new T[_capacity];
    }
    
    ~SimpleStack() {
        delete [] _values;
    }
    
    void push(T &value) {
        if (_size == _capacity) {
            // 扩容
            T *newValues = new T[_capacity * 2];
            for (int i = 0; i < _size; i++) newValues[i] = _values[i];
            delete [] _values;
            _values = newValues;
            _capacity *= 2;
        }
        _values[_size ++] = value;
    }
    
    T & pop() {
        if (isEmpty()) assert(0);
        return _values[--_size];
    }
    
    int size() {
        return _size;
    }
    
    bool isEmpty() {
        return _size == 0;
    }
    
};


#endif /* SimpleStack_h */
