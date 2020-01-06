#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <iostream>
#include <queue>

#include<bits/stdc++.h>
#include<iostream>
using namespace std;
#define COUNT 10

// create a struct data structure named BSTnode that it stores
// word elements, char array type translation and
// and other struct elements left, right that symbolize node children
struct BSTnode {
    char word[128], translation[128];
    struct BSTnode *left, *right;
};

// initialize the root as a empty
struct BSTnode *root = NULL;

// a method that accepts the value of the word and the translation corresponding to the input
// Referral address of the word and translation using Pointer and creates a new Node
struct BSTnode * createNode(char *word, char *translation) {
    struct BSTnode *newnode;// create a reference to a new node type BSTnode struct
     // create a new struct node type BSTnode by allocating a memory block returning a pointer
     // at the beginning of the block using the malloc command
    newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newnode->word, word);// initialize the value of the new node for the word
    strcpy(newnode->translation, translation);// and translation
    newnode->left = newnode->right = NULL;// We also initialize the children of the new Node as a license
    return newnode;// return the new node
}

// a method that accepts the value of the word and the translation corresponding to the input
// Referral address of the word and translation using Pointer and adds a new node
// checking first for unique key in tree
void insert(char *word, char *translation) {
    // create parent reference, current and new node type BSTnode struct
    struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
    int res = 0;
    if (!root) {// if the tree is empty
            root = createNode(word, translation);// The word and translation values are assigned to the root
            return;
    }
    // for any current Nodes that are not empty
    for (current = root; current !=NULL;
        // if the comparison of the assigned word for the current result
         // and the word we have to assign is greater than 0
         // then go to the right child otherwise to the left
        current = (res > 0) ? current->right : current->left) {
            // strcasecmp compares two words and returns 0 if they are the same
             // less than 0 if the 1st word is less than the 2nd word
             // greater than 0 if the 1st word is greater than the 2nd word
            res = strcasecmp(word, current->word);
            if (res == 0) {// if the words are the same
                printf("Duplicate entry!!\n");
                return;
            }
            parent = current;// the new parent becomes the current node
    }
    newnode = createNode(word, translation);// create a new node
     // if the word is larger than the parent child in the right child
     // else go to the left kid
    res > 0 ? (parent->right = newnode) : (parent->left = newnode);
    return;
}

// a method that accepts the value of the word corresponding to
// Referral address of the word using Pointer and deletes the node
// containing this word and rebuilding the tree
void deleteNode(char *str) {
    struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
    int flag = 0, res = 0;
    // if the root is not initialized
    if (!root) {
            printf("BST is not present!!\n");
            return;
    }
    current = root;
    //forever
    while (1) {
            // we get the result of comparing the word to be deleted and the word of each Node
            res = strcasecmp(current->word, str);
            // if in this iteration we find the word we stop this loop
            if (res == 0)
                    break;
            flag = res;
            // the new parent becomes the current Node
            parent = current;
            // depending on the result of the comparison of the words go to the right or left child
            current = (res > 0) ? current->left : current->right;
            // if the current node is empty
            if (current == NULL)
                    return;
    }
    // if statements to delete the node
     // if the current node has no right child
    if (current->right == NULL) {
            // the current node is the root and i have no left child
            if (current == root && current->left == NULL) {
                    // release the current Node
                    free(current);
                    // root is empty
                    root = NULL;
                    return;
            // else if the current is the root
            } else if (current == root) {
                    // the root becomes her left child
                    root = current->left;
                    // release the current Node
                    free (current);
                    return;
            }

            flag > 0 ? (parent->left = current->left) :
                        (parent->right = current->left);
    // else if the current Node has a right child
    } else {
            temp = current->right;
            // if there is no left child
            if (!temp->left) {
                    temp->left = current->left;
                    if (current == root) {
                            root = temp;
                            free(current);
                            return;
                    }
                    flag > 0 ? (parent->left = temp) :
                                    (parent->right = temp);
            } else {
                    // else if there is a right and left child
                    struct BSTnode *successor = NULL;
                    while (1) {//forever
                            successor = temp->left;//
                            if (!successor->left)
                                    break;
                            temp = successor;
                    }
                    temp->left = successor->right;
                    successor->left = current->left;
                    successor->right = current->right;
                    if (current == root) {
                            root = successor;// the successor is the root
                            free(current);// release the current node
                            return;
                    }
                    (flag > 0) ? (parent->left = successor) :
                                    (parent->right = successor);
            }
    }
    free (current);
    return;
}

// a method that accepts the value of the word corresponding to
// Refer to the word using Pointer and find the node
// containing this word and displaying it along with its translation
void findElement(char *str) {
    struct BSTnode *temp = NULL;
    int flag = 0, res = 0;
    if (root == NULL) {// if the tree is not initialized
            printf("Binary Search Tree is out of station!!\n");
            return;
    }
    temp = root;
    while (temp) {// as long as there are Nodes
            if ((res = strcasecmp(temp->word, str)) == 0) {// if the result of the comparison is 0
                    // show the word and its translation
                    printf("Word   : %s", str);
                    printf("Translation: %s", temp->translation);
                    flag = 1;
                    break;
            }
            // if the result is greater than 0 go to the left child, otherwise to the right
            temp = (res > 0) ? temp->left : temp->right;
    }
    // if no Node is found
    if (!flag)
            printf("Search Element not found in Binary Search Tree\n");
    return;
}

// a method that accepts the value of the node corresponding to the input
// Root referencing address using Pointer and showing all nodes
void showAll(struct BSTnode *myNode) {
    if (myNode) {// if the tree is initialized
            showAll(myNode->left);// I call the method again by passing the left node
            printf("Word    : %s", myNode->word);
            printf("Translation : %s", myNode->translation);
            printf("\n");
            showAll(myNode->right);// I call the method again by passing the right node
    }
    return;
}
// a method that accepts the value of the node corresponding to the input
// Root referencing address using Pointer and showing all nodes
void printTree(struct BSTnode *myNode, int space) {
        // if the tree is initialized
        if (myNode) {
            // increase the distance between the levels
            space += COUNT;
            // go to the right child
            printTree(myNode->right, space);
            // show the current node
            cout<<endl;
            for (int i = COUNT; i < space; i++)
            cout<<"X";
            cout<<myNode->word<<"\n";

            // go to the left kid
            printTree(myNode->left, space);
        }
        return;
}

// this is the main method
int main() {
    int ch;
    char str[128], translation[128];
    while (1) {// I always display the program functions
            printf("\n1. Insertion\t2. Deletion \t3. Searching \t4. Show all \t5. Print tree \t6. Exit");
            printf("\nEnter your choice:");
            scanf("%d", &ch);
            getchar();
            switch (ch) {
                    case 1:
                            printf("Word to insert:");
                            fgets(str, 100, stdin);
                            printf("Translation:");
                            fgets(translation, 128, stdin);
                            insert(str, translation);
                            break;
                    case 2:
                            printf("Enter the word to delete:");
                            fgets(str, 100, stdin);
                            deleteNode(str);
                            break;
                    case 3:
                            printf("Enter the search word:");
                            fgets(str, 100, stdin);
                            findElement(str);
                            break;
                    case 4:
                            showAll(root);
                            break;
                    case 5:
                            printf("\nPrinting the Binary tree...\n");
                            printTree(root,0);
                            break;
                    case 6:
                            exit(0);
                    default:
                            printf("You have entered wrong option\n");
                            break;
            }
    }
    return 0;
}
