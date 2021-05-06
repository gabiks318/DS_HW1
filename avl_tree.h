//
// Created by Gabriel on 03/05/2021.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "exceptions.h"

using namespace std;

template<class T>
class AVLTree {
private:
    struct Node {
        Node *right;
        Node *left;
        Node *father;
        int height;
        T data;
    };
    Node *root;
    Node *min;

    Node &insertNode(Node &node, Node &target, Node &father);

    Node* findNode(const Node &node, const T& data) const;

    Node &removeNode(Node &node, Node &target);

    int balanceFactor(const Node &node);

    Node *rollLeftLeft(Node &node);

    Node *rollLeftRight(Node &node);

    Node *rollRightLeft(Node &node);

    Node *rollRightRight(Node &node);

    Node &getMin(const Node &node) const;

    template<class Func>
    void inorder_recursive(Node &node, Func& func);
    int max(int num1, int num2);
    int height(const Node& node) const;

public:
    AVLTree() : root(NULL), min(NULL) {};

    ~AVLTree();

    AVLTree(const AVLTree &avl_tree);

    AVLTree &operator=(const AVLTree &avl_tree);

    void insert(const T &data);

    void remove(T& data);

    template<class Func>
    void inorder(Func& func);

    int getHeight() const;
};

template<class T>
typename AVLTree<T>::Node* AVLTree<T>::findNode(const AVLTree<T>::Node &node, const T& data) const {
    if (node != NULL) {
        if (data == node.data) {
            return node;
        } else {
            if (data > node) {
                return findNode(node.right, data);
            } else {
                return findNode(node.left, data);
            }
        }
    }
    return NULL;
}

template<class T>
void AVLTree<T>::insert(const T &data) {
    if (data == NULL) {
        return;
    }
    if (findNode(*root, data) != NULL) {
        throw NodeExists();
    }

    Node *node = new Node;
    node->data = data;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    node->father = NULL;

    root = insertNode(node, *root, NULL);
    min = getMin(root);

}

template<class T>
typename AVLTree<T>::Node &AVLTree<T>::getMin(const AVLTree<T>::Node &node) const{
    if (node == NULL) {
        return NULL;
    }
    if (node.left == NULL) {
        return &node;
    }

    return getMin(node.left);
}

template<class T>
typename AVLTree<T>::Node &
AVLTree<T>::insertNode(AVLTree<T>::Node &node, AVLTree<T>::Node &target, AVLTree<T>::Node &father) {
    //Inserting the node
    if (target == NULL) {
        node.father = father;
        return node;
    }

    if (node.data < target.data) {
        target.left = insertNode(node, target.left, target);
    } else {
        target.right = insertNode(node, target.right, target);
    }

    //Balancing the tree
    if (balanceFactor(target) > 1) {
        if (balanceFactor(target.left) == 1) {
            return rollLeftLeft(target); //LL
        } else {
            return rollLeftRight(target);//LR
        }
    } else if (balanceFactor(target) < -1) {
        if (balanceFactor(target.right) == 1) {
            return rollRightLeft(target); //RL
        } else {
            return rollRightRight(target); //RR
        }
    }
    target.height = max(height(target.right), height(target.left)) + 1;
    return target;
}

template<class T>
void AVLTree<T>::remove(T& data) {
    if (data == NULL) {
        return;
    }
    Node &node_to_remove = findNode(root, data);

    if (node_to_remove == NULL) {
        throw NodeDoesntExist();
    }

    root = removeNode(node_to_remove, root);
    min = getMin(root);
}



template<class T>
typename AVLTree<T>::Node& AVLTree<T>::removeNode(AVLTree<T>::Node &node, AVLTree<T>::Node &target) {
    if (node == NULL) {
        return NULL;
    }

    if (node.data < target.data) {
        target.left = removeNode(node, target.left);
    } else if (node.data > target.data) {
        target.right = removeNode(node, target.right);
    }

// Delete the node
    if (node.data == target.data) {
        if (!target.right && !target.left) {
            // Leaf
            delete &target;
            return NULL;
        } else if (!target.right) {
            // only right son
                Node* temp = target;
                target = node.right;
                target.father = temp->father;
                delete temp;
                return target;

        } else if (!target.left) {
            // only left son
                Node* temp = target;
                target = node.left;
                target.father = temp->father;
                delete temp;
                return target;
        } else {
        // right and left son exist
            Node *temp = target;
            target = getMin(target.right);
            target.data = temp->data;
            target.right = removeNode(target, target.right);
        }
    }

    target.height = max(height(target.left), height(target.right)) + 1;

    // Balancing the tree
    if (balanceFactor(target) > 1) {
        if (balanceFactor(target.left) == 1) {
            return rollLeftLeft(target); //LL
        } else {
            return rollLeftRight(target);//LR
        }
    } else if (balanceFactor(target) < -1) {
        if (balanceFactor(target.right) == 1) {
            return rollRightLeft(target); //RL
        } else {
            return rollRightRight(target); //RR
        }
    }
    return target;
}





template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollLeftLeft(AVLTree<T>::Node &node) {
    Node *temp = node.left->right;
    node.left->father = node.father;
    node.left->right = node;
    node.father = node.left;
    node.left = temp;

    node.height = max(height(node.right), height(node.left)) + 1;
    node.father->height = max(height(node.father->right), height(node.father->left)) + 1;

    return node.father;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollRightRight(AVLTree<T>::Node &node) {
    Node *temp = node.right->left;
    node.right->father = node.father;
    node.right->left = node;
    node.father = node.left;
    node.right = temp;

    node.height = max(height(node.right), height(node.left)) + 1;
    node.father->height = max(height(node.father->right), height(node.father->left)) + 1;

    return node.father;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollLeftRight(AVLTree<T>::Node &node) {
    node.left = rollRightRight(node.left);
    return rollLeftLeft(node);
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::rollRightLeft(AVLTree<T>::Node &node) {
    node.right = rollLeftLeft(node.right);
    return rollRightRight(node);
}

template<class T>
int AVLTree<T>::balanceFactor(const AVLTree<T>::Node &node) {
    return node.left->height - node.right->height;
}

template<class T>
template<class Func>
void AVLTree<T>::inorder(Func& func) {
    inorder_recursive(root, func);
}

template<class T>
template<class Func>
void AVLTree<T>::inorder_recursive(AVLTree<T>::Node &node, Func& func) {
    if (node == NULL) {
        return;
    }
    inorder_recursive(node.left, func);
    func(node.data);
    inorder_recursive(node.right, func);
}

template<class T>
int AVLTree<T>::getHeight() const {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

template<class T>
int AVLTree<T>::max(int num1, int num2){
    return num1 > num2 ? num1 : num2;
}

template<class T>
int AVLTree<T>::height(const Node& node) const{
    return node == NULL ? -1 : node.height;
}
#endif //DS_HW1_AVL_TREE_H
