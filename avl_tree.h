//
// Created by Gabriel on 03/05/2021.
//

#ifndef AVL_TREE_H
#define AVL_TREE
using namespace std;

template<class T, class Compare= std::less<T>>
    class AVLTree{
    public:
        AVLTree(Compare func): root(NULL), min(NULL), max(NULL), comp_func(func);
        ~AVLTree()
        AVLTree(const AVLTree& avl_tree);
        AVLTree& operator=(const AVLTree& avl_tree);
        void insert(int key, T data);
        void remove(int key);

        <template Func>
        void inorder(Node* Func func);
    private:
        struct Node{
            Node* right;
            Node* left;
            int key;
            int height;
            T data;
        };
        Compare comp_func;
        Node* root;
        Node* min;
        Node* max;
        Node* insertNode(Node* node, Node* target);
        Node* findNode(Node* node ,int key);
        void removeNode(Node* node);
        void rollLeftLeft();
        void rollLeftRight();
        void rollRightLeft();
        void rollRightRight();


    };

    template<class T>
    void AVLTree<T>::insert(int key, T data){

    }
#endif //DS_HW1_AVL_TREE_H
