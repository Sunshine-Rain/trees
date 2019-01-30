//
//  BinaryTreeNode.hpp
//  BinaryTree
//
//  Created by quan on 2018/12/28.
//  Copyright © 2018 quan. All rights reserved.
//

#ifndef BinaryTreeNode_hpp
#define BinaryTreeNode_hpp

#include <stdio.h>
#include <iostream>
#include "SimpleStack.h"
#include "SimpleQueue.h"

#define BinaryNodePosi(T) BinaryTreeNode<T> *
#define stature(p) ((p) ? (p->height) : -1)  // 节点高度（空树高度为-1）
typedef enum { RB_RED, RB_BLACK } RBColor; // 节点颜色
typedef void (*VST)(void * data);

// MARK: BinaryTreeNode状态与性质判断
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->leftChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rightChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).leftChild)
#define HasRChild(x) ((x).rightChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))

// MARK:  与BinaryTreeNode具有特定关系的节点及指针
#define sibling(p)  (\
IsLChild(*(p)) ? \
(p)->parent->rightClid : \
(p)->parent->leftClid  \
)  // 兄弟

#define uncle(x) ( \
IsLChild(*((x)->parent)) ? \
(x)->parent->parent->rightChild : \
(x)->parent->parent->leftChild \
)  // 叔叔

#define PointerFromParentTo(x) ( \
IsRoot(x) ? _root : ( \
IsLChild(x) ? (x).parent->leftChild : (x).parent->rightChild \
)\
) // 来自父亲的指针


template <typename T>
struct BinaryTreeNode {
    T data;
    BinaryNodePosi(T) parent;
    BinaryNodePosi(T) leftChild;
    BinaryNodePosi(T) rightChild;
    int height;
    int npl; // NULL Path Length (左式堆，可用height代替)
    RBColor color; // 颜色（红黑树）
    
    // MARK: Constructor
    BinaryTreeNode():parent(NULL),leftChild(NULL),rightChild(NULL),height(0),npl(0),color(RB_RED) {
        
    }
    BinaryTreeNode(T data, BinaryNodePosi(T) parent = NULL, BinaryNodePosi(T) lChild = NULL, BinaryNodePosi(T) rClild = NULL, int height = 0, int npl = 0, RBColor color = RB_RED):data(data),parent(parent),leftChild(lChild),rightChild(rClild),height(height),npl(npl),color(color) {
    }
    
    // MARK: 操作接口
    //统计当前节点后代总数
    int size() {
        return innerSize(this);
    }
    
    int innerSize(BinaryNodePosi(T) node) {
        if (!node) return 0;
        return 1 + innerSize(node->leftChild) + innerSize(node->rightChild);
    }
    
    BinaryNodePosi(T) insertAtLeft(T const & data) {
        return leftChild = new BinaryTreeNode(data, this);
    }
    
    BinaryNodePosi(T) insertAtRight(T const & data) {
        return rightChild = new BinaryTreeNode(data, this);
    }
    
    // 中序遍历的直接后继
    BinaryNodePosi(T) succ() {
        BinaryTreeNode *node = this;
        if(!node) return NULL;
        
        // 1、有右孩子
        if (HasRChild(*this)) {
            node = node->rightChild;
            while(node->leftChild) {
                node = node->leftChild;
            }
            return node;
        }
        
        // 2、暗含了上一个if的else (没有右孩子，自身是左孩子)
        if (IsLChild(*this)) return this->parent;
        
        // 3、没有右孩子，自身是右孩子
        node = this->parent;
        while (node) {
            if (IsLChild(*node)) break;
            node = node->parent;
        }
        return node ? node->parent : NULL;
    }
    
    // MARK: 先序遍历
    // 1.递归遍历
    void traversePre1(BinaryNodePosi(T) node, VST visit) {
        if (node == NULL) return;
        visit((void *)&node->data);
        traversePre1(node->leftChild, visit);
        traversePre1(node->rightChild, visit);
    }
    
    // 2.利用栈迭代遍历
    void traversePre2(BinaryNodePosi(T) node, VST visit) {
        SimpleStack<BinaryNodePosi(T)> *stack = new SimpleStack<BinaryNodePosi(T)>();
        while (node != NULL) {
            visit((void *)&node->data);
            if (node->rightChild) stack->push(node->rightChild);
            if (node->leftChild) stack->push(node->leftChild);
            if (stack->isEmpty()) break;
            node = stack->pop();
        }
        delete stack;
    }
    
     void alongLefttraverse(BinaryNodePosi(T) node, SimpleStack<BinaryNodePosi(T)> & stack, VST visit) {
        while (node) {
            visit((void *)&node->data);
            if (node->rightChild) stack.push(node->rightChild);
            node = node->leftChild;
        }
    }
    
    // 3.利用辅助栈和alongLefttraverse函数
    void traversePre3(BinaryNodePosi(T) node, VST visit) {
        SimpleStack<BinaryNodePosi(T)> *stack = new SimpleStack<BinaryNodePosi(T)>();
        while (node != NULL) {
            alongLefttraverse(node, *stack, visit);
            if (stack->isEmpty()) break;
            node = stack->pop();
        }
        delete stack;
    }
    
    // MARK: 中序遍历
    // 1.递归
    void traverseInorder1(BinaryNodePosi(T) node, VST visit) {
        if (!node) return;
        if (node->leftChild) traverseInorder1(node->leftChild, visit);
        visit((void *)&node->data);
        if (node->rightChild) traverseInorder1(node->rightChild, visit);
    }
    
    void traverseInorderAlongLeft(BinaryNodePosi(T) node, SimpleStack<BinaryNodePosi(T)> & stack) {
        while (node) {
            stack.push(node);
            node = node->leftChild;
        }
    }
    
    // 2. 迭代版本实现  分摊时间复杂度 O(n)
    void traverseInorder2(BinaryNodePosi(T) node, VST visit) {
        SimpleStack<BinaryNodePosi(T)> *stack = new SimpleStack<BinaryNodePosi(T)>();
        while (true) {
            traverseInorderAlongLeft(node, *stack);
            if (stack->isEmpty()) break;
            node = stack->pop();
            visit((void *)&node->data);
            node = node->rightChild;
        }
        delete stack;
    }
    
    //MARK: 后序遍历
    void traversePost(BinaryNodePosi(T) node, VST visit) {
        if (!node) return;
        if (node->leftChild) traversePost(node->leftChild, visit);
        if (node->rightChild) traversePost(node->rightChild, visit);
        visit((void *)&node->data);
    }
    
    // MARK: 层次遍历
    void traverseLevel(BinaryNodePosi(T) node, VST visit) {
        SimpleQueue<BinaryNodePosi(T)> queue;
        while (node) {
            visit((void *)&node->data);
            if (node->leftChild) queue.enqueue(node->leftChild);
            if (node->rightChild) queue.enqueue(node->rightChild);
            if (queue.isEmpty()) break;
            node = queue.dequeue();
        }
    }
    
    // MARK: 运算符重载
    bool operator > (BinaryTreeNode const& bn) { return data > bn.data; }
    bool operator < (BinaryTreeNode const& bn) { return data < bn.data; }
    bool operator == (BinaryTreeNode const& bn) { return data == bn.data; }
    bool operator != (BinaryTreeNode const& bn) { return data != bn.data; }
};


#endif /* BinaryTreeNode_hpp */
