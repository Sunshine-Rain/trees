//
//  main.cpp
//  BinaryTree
//
//  Created by quan on 2018/12/28.
//  Copyright © 2018 quan. All rights reserved.
//

#include <iostream>
#include "BinaryTree.hpp"
#include "BST/Entry.hpp"
#include "BST/BinarySearchTree.hpp"

using namespace std;


template<typename T>
class TestClass {
    static void visit(void * data) {
        std::cout << *((T*)data) << " ";
    }
    
    static void visit2(void * data) {
        std::cout << ((Entry<int, int>*)data)->value << " ";
    }
public:
    void testTraverse() {
        BinaryTree<char> *tree = new BinaryTree<char>();
        BinaryNodePosi(char) root = tree->insertAsRoot('a');
        BinaryNodePosi(char) nodeB = tree->insertAsLC(root, 'b');
        BinaryNodePosi(char) nodeC = tree->insertAsRC(root, 'c');
        BinaryNodePosi(char) nodeD = tree->insertAsLC(nodeB, 'd');
        BinaryNodePosi(char) nodeE = tree->insertAsRC(nodeB, 'e');
        BinaryNodePosi(char) nodeF = tree->insertAsLC(nodeC, 'f');
        BinaryNodePosi(char) nodeG = tree->insertAsRC(nodeC, 'g');
        nodeF->insertAtLeft('i')->insertAtRight('j');
        BinaryNodePosi(char) nodeK = nodeG->insertAtLeft('k');
        nodeK->insertAtLeft('l');
        nodeK->insertAtRight('m');
        
        cout << "先序遍历1：";
        root->traversePre1(root, &visit);
        cout << endl;
        
        cout << "先序遍历2：";
        tree->travPre(&visit);
        cout << "   ";
        root->traversePre2(root, &visit);
        cout << endl;
        
        cout << "先序遍历3：";
        root->traversePre3(root, &visit);
        cout << endl;
        
        
        cout << "中序遍历1：";
        root->traverseInorder1(root, &visit);
        cout << endl;
        
        cout << "中序遍历2：";
        tree->travInOrder(&visit);
        cout << "   ";
        root->traverseInorder2(root, &visit);
        cout << endl;
        
        cout << "后序遍历 ：";
        tree->travPost(&visit);
        cout << "   ";
        root->traversePost(root, &visit);
        cout << endl;
        
        cout << "层次遍历 ：";
        tree->travLevel(&visit);
        cout << "   ";
        root->traverseLevel(root, &visit);
        cout << endl;
    }
    
    void testBST() {
        BinarySearchTree<Entry<int, int>>  *bst = new BinarySearchTree<Entry<int, int>>();
        BinaryNodePosi(T) root = bst->insertAsRoot(*(new Entry<int, int>(10, 10)));
        
        BinaryNodePosi(T) node4 = bst->insertAsLC(root, *(new Entry<int, int>(4, 4)));
        BinaryNodePosi(T) node15 = bst->insertAsRC(root,*(new Entry<int, int>(15, 15)));

        BinaryNodePosi(T) node3 = bst->insertAsLC(node4, *(new Entry<int, int>(3, 3)));
        BinaryNodePosi(T) node6 = bst->insertAsRC(node4,*(new Entry<int, int>(6, 6)));
        
        BinaryNodePosi(T) node12 = bst->insertAsLC(node15, *(new Entry<int, int>(12, 12)));
        BinaryNodePosi(T) node20 = bst->insertAsRC(node15,*(new Entry<int, int>(20, 20)));
        
        BinaryNodePosi(T) node5 = bst->insertAsLC(node6, *(new Entry<int, int>(5, 5)));
        BinaryNodePosi(T) node8 = bst->insertAsRC(node6,*(new Entry<int, int>(8, 8)));
        
        BinaryNodePosi(T) node2 = bst->insertAsLC(node3, *(new Entry<int, int>(2, 2)));
        
        cout << "+++++++++++++++++++++++ 中序遍历 +++++++++++++++++++++++" << endl;
        bst->travInOrder(&visit2);
        cout << endl;
        
        cout << "+++++++++++++++++++++++ 后继测试 +++++++++++++++++++++++" << endl;
        BinaryNodePosi(T) temp = node2;
        while (temp) {
            cout << ((Entry<int, int>)temp->data).value;
            cout << "的后继是";
            if (temp->succ()) {
                cout << ((Entry<int, int>)(temp->succ()->data)).value << endl;
            }
            temp = temp->succ();
        }
        cout << endl;
        
        cout << "+++++++++++++++++++++++ Search 8 +++++++++++++++++++++++" << endl;
        BinaryNodePosi(T) posi = bst->search(*(new Entry<int, int>(8,8)));
        cout << ((Entry<int, int>)posi->data).value << endl;
        
        cout << "+++++++++++++++++++++++ insert 25 +++++++++++++++++++++++" << endl;
        bst->insert(*(new Entry<int, int>(25,25)));
        bst->travInOrder(&visit2);
        cout << endl;
        cout << "+++++++++++++++++++++++ insert 11 +++++++++++++++++++++++" << endl;
        bst->insert(*(new Entry<int, int>(11,11)));
        bst->travInOrder(&visit2);
        cout << endl;
        
        cout << "+++++++++++++++++++++++ remove 11 +++++++++++++++++++++++" << endl;
        bst->remove(*(new Entry<int, int>(11,11)));
        bst->travInOrder(&visit2);
        cout << endl;
        cout << "+++++++++++++++++++++++ remove 25 +++++++++++++++++++++++" << endl;
        bst->remove(*(new Entry<int, int>(25,25)));
        bst->travInOrder(&visit2);
        cout << endl;
        
    }
};

int main(int argc, const char * argv[]) {
    
    // test start
//    TestClass<char> testObj;
//    testObj.testTraverse();   // 遍历测试
    
    TestClass<Entry<int, int>> testBST;
    testBST.testBST();
    
    
    return 0;
}
