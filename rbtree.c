#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"
#include "utility.h"


struct node* newNode(int val) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = NULL;
    newNode->val = val;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

struct node* rotateLeft(struct node* root, struct node* n) {
    if(root == NULL||n == NULL)
    	return root;
    bool isRoot = false;
    if (root == n) {
        isRoot = true;
    }
    if(n->right == NULL)
    	return root;
    struct node* rightLeftChild = n->right->left;
    struct node* parent = n->parent;

    bool isLeftChild = false;
    if (!isRoot) {
        if (n == parent->left) {
            isLeftChild = true;
        }
    }

    n->parent = n->right;
    n->right = rightLeftChild;
    if(rightLeftChild != NULL)
        rightLeftChild->parent = n;
    n->parent->left = n;
    n->parent->parent = parent;

    if (isRoot) {
        root = n->parent;
        root->parent = NULL;
    }
    else {
        if (isLeftChild) {
            parent->left = n->parent;
        }
        else {
            parent->right = n->parent;
        }
    }

    return root;
}

struct node* rotateRight(struct node* root, struct node* n) {
    if(root == NULL||n == NULL)
    	return root;
    bool isRoot = false;
    if (root == n) {
        isRoot = true;
    }
    if(n->left == NULL)
    	return root;
    struct node* leftRightChild = n->left->right;
    struct node* parent = n->parent;
    
    bool isLeftChild = false;
    if (!isRoot) {
        if (n == n->parent->left) {
            isLeftChild = true;
        }
    }

    n->parent = n->left;
    n->left = leftRightChild;
    if(leftRightChild != NULL)
        leftRightChild->parent = n;
    n->parent->right = n;
    n->parent->parent = parent;

    if (isRoot) {
        root = n->parent;
        root->parent = NULL;
    }
    else {
        if (isLeftChild) {
            parent->left = n->parent;
        }
        else {
            parent->right = n->parent;
        }
    }

    return root;
}

struct node* insertRB(struct node* root, struct node* newNode) {
    struct node* iterator = root;
    bool goLeft = false;
    struct node* p_iterator = NULL;
    while (iterator != NULL) {
        if (iterator->val >= newNode->val) {
            p_iterator = iterator;
            goLeft = true;
            iterator = iterator->left;
        }
        else {
            p_iterator = iterator;
            goLeft = false;
            iterator = iterator->right;
        }
    }
    if (root == NULL) {
        root = newNode;
        root->color = BLACK;
        return root;
    }
    else {
        if (goLeft) {
            p_iterator->left = newNode;
            newNode->parent = p_iterator;
        }
        else {
            p_iterator->right = newNode;
            newNode->parent = p_iterator;
        }
    }
    //iterate_in_order(root, print_val);
    //printf("End of this Insertion before balance\n");
    root = balance(root, newNode);
    //iterate_in_order(root, print_val);
    //printf("End of this Insertion after balance\n");
    root->color = BLACK;
    return root;
}
struct node *balance(struct node* root, struct node* newNode) {
    if(newNode->parent == NULL || newNode-> parent->color == BLACK)
    	return root;
    if (newNode->parent->parent == NULL)
        return root;
    // case 1: parent is the left child of its parent
    if (newNode->parent == newNode->parent->parent->left) {
        // case 1.1 uncle is red
        if(newNode->parent->parent->right!=NULL){
            if (newNode->parent->parent->right->color == RED) {
            	newNode->parent->color = BLACK;
            	newNode->parent->parent->right->color = BLACK;
            	newNode->parent->parent->color = RED;
            	root = balance(root, newNode->parent->parent);
            	return root;
            }
    }
        // case 1.2 uncle is black or doesnt exist and newNode is a right child
        if ((newNode->parent->parent->right == NULL || newNode->parent->parent->right->color == BLACK) && newNode == newNode->parent->right) {
            root = rotateLeft(root, newNode->parent);
            root = balance(root, newNode->left);
            return root;
        }
        // case 1.3 uncle is black and newNode is a left child
        if ((newNode->parent->parent->right == NULL || newNode->parent->parent->right->color == BLACK)  && newNode == newNode->parent->left) {
            newNode->parent->color = BLACK;
            newNode->parent->parent->color = RED;
            root = rotateRight(root, newNode->parent->parent);
            return root;
        }
    }
    // case 2: parent is the right child of its parent
    if (newNode->parent == newNode->parent->parent->right) {
        // case 2.1 uncle is red
        if (newNode->parent->parent->left!=NULL) {
            if (newNode->parent->parent->left->color == RED) {
            	newNode->parent->color = BLACK;
            	newNode->parent->parent->left->color = BLACK;
            	newNode->parent->parent->color = RED;
            	root = balance(root, newNode->parent->parent);
            	return root;
            }
        }
        // case 2.2 uncle is black and newNode is a left child
        if ((newNode->parent->parent->left == NULL || newNode->parent->parent->left->color == BLACK) && newNode == newNode->parent->left) {
            root = rotateRight(root, newNode->parent);
            root = balance(root, newNode->right);
            return root;
        }
        // case 2.3 uncle is black and newNode is a right child
        if ((newNode->parent->parent->left == NULL || newNode->parent->parent->left->color == BLACK) && newNode == newNode->parent->right) {
            newNode->parent->color = BLACK;
            newNode->parent->parent->color = RED;
            root = rotateLeft(root, newNode->parent->parent);
            return root;
        }
    }
    return root;
}

