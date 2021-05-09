// Generic AVL Tree //

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "exceptions.h"
#include <iostream>
using namespace std;


template<class T>
class AVLTree {
private:
    // Tree fields
    struct Node {
        Node *right;
        Node *left;
        Node *father;
        int height;
        T* data;
    };
    Node *root;
    Node *min;
    int size;

    // Node Functions
    Node* initNode(const T& data);
    Node* insertNode(Node *node, Node *target, Node *father);
    Node* findNode(Node *node, const T& data);
    Node* removeNode(Node *node, Node *target);
    Node* getMin(Node *node) const;
    int balanceFactor(Node *node) const;
    int height(const Node* node) const;

    // Roll Functions
    Node *rollLeftLeft(Node *node);
    Node *rollLeftRight(Node *node);
    Node *rollRightLeft(Node *node);
    Node *rollRightRight(Node *node);


    // Tree Traversals
    template<class Func>
    void inorder_aux(Node *node, Func& func, int* limit);
    template<class Func>
    void reverseInorder_aux(Node* node, Func& func, Node* last, int* limit);
    void printTree_aux(Node* node) const;

    // Constructor, Destructor helper functions
    Node* sortedInit_aux(T data_arr[], int start, int end, AVLTree<T>::Node* father);
    Node* copyNode(Node* node);
    void empty_aux(Node* node);

    // Aux functions
    int max(int num1, int num2);
public:
    // Constructors, Destructor, Assignment
    AVLTree() : root(NULL), min(NULL), size(0) {};
    AVLTree(const AVLTree<T>& tree);
    AVLTree &operator=(const AVLTree<T> &tree);
    void sortedArrayInit(T data_arr[], int n);
    ~AVLTree(){
        empty();
    }

    // Interface Functions
    void insert(const T& data);
    T* find(const T& data);
    void remove(const T& data);
    int getHeight() const;
    void empty();
    void printTree() const;
    bool isEmpty() const;

    template<class Func>
    void inorder(Func& func, int limit=-1);

    template<class Func>
    void reverseInorder(Func& func, int limit=-1);
};

// Constructors, Destructor, Assignment ---------------------

template<class T>
AVLTree<T>::AVLTree(const AVLTree<T>& tree){
    root = copyNode(tree.root);
    size = tree.size;
    min = getMin(root);
}

template<class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T> &tree){
    empty();
    root = copyNode(tree.root);
    size = tree.size;
    min = getMin(root);
    return *this;
}

template<class T>
void AVLTree<T>::sortedArrayInit(T data_arr[], int n) {
    if(size > 0)
        throw TreeHasData();
    root = sortedInit_aux(data_arr, 0, n - 1, NULL);
    size = n;
}

// Interface Functions -------------------------------

template<class T>
void AVLTree<T>::insert(const T& data) {
    if (&data == NULL) {
        return;
    }
    if (findNode(root, data) != NULL) {
        throw NodeExists();
    }

    Node *node = initNode(data);

    root = insertNode(node, root, NULL);
    min = getMin(root);
    size++;
}

template<class T>
T* AVLTree<T>::find(const T& data){
    Node* node = findNode(root, data);
    if(node == NULL)
        throw NodeDoesntExist();
    return node->data;
}

template<class T>
void AVLTree<T>::remove(const T& data) {
    if (&data == NULL || size == 0) {
        return;
    }
    Node* node_to_remove = findNode(root, data);

    if (node_to_remove == NULL) {
        throw NodeDoesntExist();
    }

    root = removeNode(node_to_remove, root);
    min = getMin(root);
    size--;
}

template<class T>
void AVLTree<T>::empty() {
    empty_aux(root);
    root = NULL;
}

template<class T>
int AVLTree<T>::getHeight()const{
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

template<class T>
void AVLTree<T>::printTree() const {
    printTree_aux(root);
}

template<class T>
template<class Func>
void AVLTree<T>::inorder(Func& func, int limit) {
    int iterations = size;
    if(limit >= 0){
        iterations = limit;
    }
    inorder_aux(root, func, &iterations);
}

template<class T>
template<class Func>
void AVLTree<T>::reverseInorder(Func& func,int limit) {
    int iterations = size;
    if(limit >= 0){
        iterations = limit;
    }
    reverseInorder_aux(min, func,NULL, &iterations);
}

template<class T>
bool AVLTree<T>::isEmpty() const{
    return size == 0;
}

// Node Functions ---------------------------------------------

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::initNode(const T& data){
    Node* node = new Node;
    node->data = new T(data);
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    node->father = NULL;
    return node;
}

template<class T>
typename AVLTree<T>::Node*
AVLTree<T>::insertNode(AVLTree<T>::Node *node, AVLTree<T>::Node *target, AVLTree<T>::Node *father) {
    //Inserting the node
    if (target == NULL) {
        node->father = father;
        return node;
    }

    if (*node->data < *target->data) {
        target->left = insertNode(node, target->left, target);
    } else {
        target->right = insertNode(node, target->right, target);
    }

    //Balancing the tree
    if (balanceFactor(target) > 1) {
        if (balanceFactor(target->left) == 1) {
            return rollLeftLeft(target); //LL
        } else {
            return rollLeftRight(target);//LR
        }
    } else if (balanceFactor(target) < -1) {
        if (balanceFactor(target->right) == 1) {
            return rollRightLeft(target); //RL
        } else {
            return rollRightRight(target); //RR
        }
    }
    target->height = max(height(target->right), height(target->left)) + 1;
    return target;
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::removeNode(AVLTree<T>::Node *node, AVLTree<T>::Node *target) {
    if (node == NULL) {
        return NULL;
    }
    // Delete the node
    if (*node->data == *target->data) {
        if (!target->right && !target->left) {
            // Leaf
            delete target->data;
            delete target;
            return NULL;
        } else if (!target->right) {
            // Only right son
            Node* temp = target;
            target = target->left;
            delete temp->data;
            delete temp;
            return target;

        } else if (!target->left) {
            // Only left son
            Node* temp = target;
            target = target->right;
            delete temp->data;
            delete temp;
            return target;
        } else {
            // right and left son exist
            Node *temp = getMin(target->right);
            delete target->data;
            target->data = new T(*temp->data);
            target->right = removeNode(target, target->right);
        }
    } else if (*node->data < *target->data) {
        target->left = removeNode(node, target->left);
    } else {
        target->right = removeNode(node, target->right);
    }


    target->height = max(height(target->left), height(target->right)) + 1;

    // Balancing the tree
    if (balanceFactor(target) > 1) {
        if (balanceFactor(target->left) == 1) {
            return rollLeftLeft(target); //LL
        } else {
            return rollLeftRight(target);//LR
        }
    } else if (balanceFactor(target) < -1) {
        if (balanceFactor(target->right) == 1) {
            return rollRightLeft(target); //RL
        } else {
            return rollRightRight(target); //RR
        }
    }
    return target;
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::findNode(AVLTree<T>::Node* node, const T& data){
    if (node != NULL) {
        if (data == *node->data) {
            return node;
        } else {
            if (data > *node->data) {
                return findNode(node->right, data);
            } else {
                return findNode(node->left, data);
            }
        }
    }
    return NULL;
}

template<class T>
int AVLTree<T>::balanceFactor(AVLTree<T>::Node *node) const {
    return height(node->left) - height(node->right);
}

template<class T>
int AVLTree<T>::height(const Node* node) const{
    return node == NULL ? -1 : node->height;
}



template<class T>
typename AVLTree<T>::Node* AVLTree<T>::getMin(AVLTree<T>::Node* node) const{
    if (node == NULL) {
        return NULL;
    }
    if (node->left == NULL) {
        return node;
    }

    return getMin(node->left);
}


// Roll Functions------------------------------

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollLeftLeft(AVLTree<T>::Node *node) {
    Node *temp = node->left;
    node->left->father = node->father;
    node->father = temp;
    node->left = node->father->right;
    node->father->right = node;

    node->height = max(height(node->right), height(node->left)) + 1;
    if(node->father) {
        node->father->height = max(height(node->father->right), height(node->father->left)) + 1;
    }
    return node->father;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollRightRight(AVLTree<T>::Node *node) {
    Node *temp = node->right;
    node->right->father = node->father;
    node->father = temp;
    node->right = node->father->left;
    node->father->left = node;

    node->height = max(height(node->right), height(node->left)) + 1;
    if(node->father){
        node->father->height = max(height(node->father->right), height(node->father->left)) + 1;
    }

    return node->father;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollLeftRight(AVLTree<T>::Node *node) {
    node->left = rollRightRight(node->left);
    return rollLeftLeft(node);
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollRightLeft(AVLTree<T>::Node *node) {
    node->right = rollLeftLeft(node->right);
    return rollRightRight(node);
}

// Tree Traversals----------------------------------------------------

template<class T>
template<class Func>
void AVLTree<T>::inorder_aux(AVLTree<T>::Node *node, Func& func, int* limit) {
    if (node == NULL || (*limit) <= 0) {
        return;
    }
    inorder_aux(node->left, func, limit);
    if((*limit) <= 0)
        return;
    if(func(node->data))
        (*limit)--;
    if((*limit) <= 0)
        return;
    inorder_aux(node->right, func, limit);
}

template<class T>
template<class Func>
void AVLTree<T>::reverseInorder_aux(AVLTree<T>::Node* node, Func& func, AVLTree<T>::Node* last, int* limit){
    if(node == NULL || (*limit) <= 0)
        return;
    if(node->father == last)
        reverseInorder_aux(node->left, func, node, limit);
    if((*limit) <= 0)
        return;
    if(func(node->data))
        (*limit)--;
    if((*limit) <= 0)
        return;
    reverseInorder_aux(node->right, func, node, limit);
    if((*limit) <= 0)
        return;
    if(node->father != last)
        reverseInorder_aux(node->father, func, node, limit);
}

template<class T>
void AVLTree<T>::printTree_aux(AVLTree<T>::Node* node) const {
    if(node == NULL)
        return;
    printTree_aux(node->left);
    std::cout << *node->data << " BF: " << balanceFactor(node) << " Height: " << height(node) << std::endl;
    printTree_aux(node->right);
}

// Constructor, Destructor helper functions--------------------------------------------

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::sortedInit_aux(T data_arr[], int start, int end, AVLTree<T>::Node* father){
    if(start > end)
        return NULL;

    int mid = (start+end)/2;
    Node *node = initNode(data_arr[mid]);
    node->father = father;
    node->left = sortedInit_aux(data_arr, start, mid -1, node);
    node->right = sortedInit_aux(data_arr, mid + 1, end, node);
    node->height = max(height(node->right), height(node->left)) + 1;
    return node;
}

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::copyNode(AVLTree<T>::Node* node){
    if(node == NULL){
        return NULL;
    }
    Node* left = copyNode(node->left);
    Node* right = copyNode(node->right);

    Node* new_node = initNode(*node->data);
    new_node->father = node->father;
    new_node->left = left;
    new_node->right = right;
    new_node->height = max(height(new_node->right), height(new_node->left)) + 1;
    return new_node;
}


template<class T>
void AVLTree<T>::empty_aux(AVLTree<T>::Node* node) {
    if(node == NULL){
        return;
    }

    if(node->left){
        empty_aux(node->left);
    }
    if(node->right){
        empty_aux(node->right);
    }
    delete node->data;
    delete node;
}

// Aux functions---------------------------------------------------

template<class T>
int AVLTree<T>::max(int num1, int num2){
    return num1 > num2 ? num1 : num2;
}

#endif //DS_HW1_AVL_TREE_H
