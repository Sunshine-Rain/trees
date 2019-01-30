//
//  BinarySearchTree.hpp
//  BinaryTree
//
//  Created by quan on 2019/1/28.
//  Copyright © 2019 quan. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <stdio.h>
#include "BinaryTree.hpp"

template <typename T>
class BinarySearchTree: public BinaryTree<T> {
    BinaryNodePosi(T) & searchIn(BinaryNodePosi(T) & v, const T& e, BinaryNodePosi(T) & hot);
protected:
    BinaryNodePosi(T) _hot;
    BinaryNodePosi(T) connect34(BinaryNodePosi(T), BinaryNodePosi(T), BinaryNodePosi(T),
                                BinaryNodePosi(T),BinaryNodePosi(T),BinaryNodePosi(T),BinaryNodePosi(T));
    BinaryNodePosi(T) rotateAt(BinaryNodePosi(T) x);
public:
    virtual BinaryNodePosi(T) & search(const T& e);
    virtual BinaryNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};


template <typename T>
BinaryNodePosi(T) & BinarySearchTree<T>::searchIn(BinaryNodePosi(T) & v, const T& e, BinaryNodePosi(T) & hot) {
    if (!v || v->data == e) return v;
    hot = v;
    return searchIn((v->data < e) ? v->rightChild : v->leftChild, e, hot);
}

template <typename T>
BinaryNodePosi(T) & BinarySearchTree<T>::search(const T& e) {
    return searchIn(this->_root, e, _hot = NULL);
}

template <typename T>
BinaryNodePosi(T) BinarySearchTree<T>::insert(const T& e) {
    BinaryNodePosi(T) & posi  = search(e);
    if (posi) return posi;
    
    posi = new BinaryTreeNode<T>(e, _hot);
    this->_size++;
    this->updateHeightAbove(posi);
    return posi;
}

template <typename T>
bool BinarySearchTree<T>::remove(const T& e) {
    BinaryNodePosi(T) & posi  = search(e);
    if (!posi) return false;
    
    removeAt(posi, _hot);
    this->_size--;
    this->updateHeightAbove(posi);
    return true;
}

template <typename T>
static BinaryNodePosi(T) removeAt(BinaryNodePosi(T)& x, BinaryNodePosi(T)& hot) {
    BinaryNodePosi(T) w = x;
    BinaryNodePosi(T) succ = NULL;
    
    if(!HasLChild(*x)) {
        succ = x = x->rightChild;
    }
    else if (!HasRChild(*x)) {
        succ = x = x->leftChild;
    }
    else {
        w = w->succ();
        swap(x->data, w->data);
        BinaryNodePosi(T) u = w->parent;
        ((u == x) ? u->rightChild : u->leftChild) = succ = w->rightChild;
    }
    hot = w->parent;
    if (succ) succ->parent = hot;
    delete w;
    return succ;
}

#endif /* BinarySearchTree_hpp */
