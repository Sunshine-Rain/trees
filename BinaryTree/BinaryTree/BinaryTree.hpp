//
//  BinaryTree.hpp
//  BinaryTree
//
//  Created by quan on 2019/1/21.
//  Copyright © 2019 quan. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include "BinaryTreeNode.hpp"

using namespace std;

template <typename T>
class BinaryTree {
protected:
    int _size; // 规模
    BinaryNodePosi(T) _root; // 根节点
    virtual int updateHeight(BinaryNodePosi(T) x);
    void updateHeightAbove(BinaryNodePosi(T) x); // 更新x及祖先癿高度
public:
    BinaryTree():_size(0),_root(NULL) {}
    ~BinaryTree() { if (_size > 0) remove(_root); }
    
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinaryNodePosi(T) root() const { return _root;}
    BinaryNodePosi(T) insertAsRoot(T const& e);
    BinaryNodePosi(T) insertAsLC(BinaryNodePosi(T) x, T const& e);
    BinaryNodePosi(T) insertAsRC(BinaryNodePosi(T) x, T const& e);
    BinaryNodePosi(T) attachAsLC(BinaryNodePosi(T) x, BinaryTree<T> * &t);
    BinaryNodePosi(T) attachAsRC(BinaryNodePosi(T) x, BinaryTree<T> * &t);
    int remove(BinaryNodePosi(T) x); //删除x处节点为根的子树,返回删除子树的规模(会调用delete)
    BinaryTree<T> * secede(BinaryNodePosi(T) x); // 摘除子树x,并使其变为一颗独立的树
    
    // MARK: 遍历
    void travPre(VST visit) { if (_root) _root->traversePre2(_root, visit); }
    void travInOrder(VST visit) { if (_root) _root->traverseInorder2(_root, visit); }
    void travPost(VST visit) { if (_root) _root->traversePost(_root, visit); }
    void travLevel(VST visit) { if (_root) _root->traverseLevel(_root, visit); }
    
    // MARK: 比较器、判等器
    bool operator > (BinaryTree<T> const& t) {  return _root && t._root && gt(_root, t._root);  }
    bool operator < (BinaryTree<T> const& t) {  return _root && t._root && lt(_root, t._root);  }
    bool operator == (BinaryTree<T> const& t) { return _root && t._root && (_root == t._root); }
    bool operator != (BinaryTree<T> const& t) { return !_root || !t._root || (_root != t._root); }
    
};

// MARK: Height functions
template <typename T>
int BinaryTree<T>::updateHeight(BinaryNodePosi(T) x) {
    return x->height = 1 + max(stature(x->leftChild), stature(x->rightChild));
}

template <typename T>
void BinaryTree<T>::updateHeightAbove(BinaryNodePosi(T) x) {
    int heightBefore;
    while (x) {
        heightBefore = x->height;
        if (heightBefore == updateHeight(x)) break;
        x = x->parent;
    }
}

// MARK: Insert & Attach Functions
template <typename T>
BinaryNodePosi(T) BinaryTree<T>::insertAsRoot(const T &e) {
    _size = 1;
    return _root = new BinaryTreeNode<T>(e);
}

template <typename T>
BinaryNodePosi(T) BinaryTree<T>::insertAsLC(BinaryNodePosi(T) x, const T &e) {
    _size ++;
    x->insertAtLeft(e);
    updateHeightAbove(x);
    return x->leftChild;
}

template <typename T>
BinaryNodePosi(T) BinaryTree<T>::insertAsRC(BinaryNodePosi(T) x, const T &e) {
    _size ++;
    x->insertAtRight(e);
    updateHeightAbove(x);
    return x->rightChild;
}

template <typename T>
BinaryNodePosi(T) BinaryTree<T>::attachAsLC(BinaryNodePosi(T) x, BinaryTree<T> * &t) {
    if (t->_root) {
        _size += t->_size;
        x->leftChild = t->_root;
        t->_root->parent = x;
        updateHeightAbove(x);
        
        t->_root = NULL;
        t->_size = 0;
//        release(t);
        delete t;
        t = NULL;
    }
    return x;
}

template <typename T>
BinaryNodePosi(T) BinaryTree<T>::attachAsRC(BinaryNodePosi(T) x, BinaryTree<T> * &t) {
    if (t->_root) {
        _size += t->_size;
        x->rightChild = t->_root;
        t->_root->parent = x;
        updateHeightAbove(x);
        
        t->_root = NULL;
        t->_size = 0;
//        release(t);
        delete t;
        t = NULL;
    }
    return x;
}

// MARK: remove
template <typename T>
int BinaryTree<T>::remove(BinaryNodePosi(T) x) {
    PointerFromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    x->parent = NULL;
    int n = removeAt(x);
    _size -= n;
    return n;
}

template <typename T>
static int removeAt(BinaryNodePosi(T) x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->leftChild) + removeAt(x->rightChild);
//    release(x->data);
//    release(x);
    delete x;
    return n;
}

// MARK: secede
template <typename T>
BinaryTree<T> * BinaryTree<T>::secede(BinaryNodePosi(T) x) {
    PointerFromParentTo(*x) = NULL;
    updateHeightAbove(x);
    int size = x->size();
    _size -= size;
    
    BinaryTree<T> * tree = new BinaryTree<T>();
    tree->_root = x;
    tree->_size = size;
    x->parent = NULL;
    return tree;
}
#endif /* BinaryTree_hpp */
