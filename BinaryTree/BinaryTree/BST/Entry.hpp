//
//  Entry.hpp
//  BinaryTree
//
//  Created by quan on 2019/1/16.
//  Copyright © 2019 quan. All rights reserved.
//

#ifndef Entry_hpp
#define Entry_hpp

#include <stdio.h>

/**
 *  BST 词条
 */
template <typename K, typename V>
struct Entry {
    K key;
    V value;
    
    // 基本构造
    Entry(K key, V value):key(key), value(value) {}
    // 基于复制的构造
    Entry(Entry<K, V> const& e):key(e.key), value(e.value) {}
    
    // MARK: 运算符重载
    bool operator > (Entry<K, V> const& e) { return key > e.key; }
    bool operator < (Entry<K, V> const& e) { return key < e.key; }
    bool operator == (Entry<K, V> const& e) { return key == e.key; }
    bool operator != (Entry<K, V> const& e) { return key != e.key; }
};

#endif /* Entry_hpp */
