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

//���������� ���� ����� ��������� ����� struct �� ����� BSTnode ��� ����������
//�� �������� ����, ��������� ����� char array ���
//��� ���� �������� ����� struct �� left, right ��� ����������� �� ������ ��� node
struct BSTnode {
    char word[128], translation[128];
    struct BSTnode *left, *right;
};

//���������� ��� ���� ��� �����
struct BSTnode *root = NULL;

//��� ������� � ����� ������� �� ������ ��� ���� ��� ����� ��� ��� ���������� ��� ����������� ����
//��������� ���������� ��� ����� ��� ��� ���������� �� ����� Pointer ��� ���������� ��� ��� Node
struct BSTnode * createNode(char *word, char *translation) {
    struct BSTnode *newnode;//���������� ���������� ���� node ����� BSTnode struct
    //���������� ���� node ����� struct BSTnode ������������ ��� ����� ������ ������������� ���� pointer
    //���� ���� ��� ����� �� ��� ����� ��� ������� malloc
    newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newnode->word, word);//������������� ��� ���� ��� ���� node ��� ��� ����
    strcpy(newnode->translation, translation);//��� ��� ���������
    newnode->left = newnode->right = NULL;//������������� ��� �� ������ ��� ���� Node �� �����
    return newnode;//������������ �� ��� node
}

//��� ������� � ����� ������� �� ������ ��� ���� ��� ����� ��� ��� ���������� ��� ����������� ����
//��������� ���������� ��� ����� ��� ��� ���������� �� ����� Pointer ��� ��������� ��� ��� node
//�������� ������ ������ ��� �������� ������ ��� �������
void insert(char *word, char *translation) {
    //���������� ���������� �����, ������� ��� ���� node ����� BSTnode struct
    struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
    int res = 0;
    if (!root) {//�� �� ������ ����� �����
            root = createNode(word, translation);//���� ���� ����������� �� ����� ��� ����� ��� ��� ����������
            return;
    }
    //��� ���� ������ Node ��� ��� ����� �����
    for (current = root; current !=NULL;
        //�� ��� �� ������ ���������� � �������� ��� ����������� �����
        //��� ��� ����� ��� ������ ��� �� ����������� ����� ���������� ��� 0
        //���� ���� ��� ���� ����� ������ ��� ��������
        current = (res > 0) ? current->right : current->left) {
            //� ������ strcasecmp ��������� ��� ������ ��� ���������� 0 �� ����� �����
            //��������� ��� 0 �� � 1� ���� ����� ��������� ������������� ��� 2��
            //���������� ��� 0 �� � 1� ���� ����� ���������� ������������� ��� 2��
            res = strcasecmp(word, current->word);
            if (res == 0) {//�� ����� ����� �� ������
                printf("Duplicate entry!!\n");
                return;
            }
            parent = current;//� ���� ������ ������� �� ������ node
    }
    newnode = createNode(word, translation);//��������� ��� node
    //�� � ���� ����� ���������� ��� ��� ����� ���� ��� ���� �����
    //������ ���� ��� �������� �����
    res > 0 ? (parent->right = newnode) : (parent->left = newnode);
    return;
}

//��� ������� � ����� ������� �� ������ ��� ���� ��� ����� ��� ����������� ����
//��������� ���������� ��� ����� �� ����� Pointer ��� ��������� �� node
//��� �������� ����� ��� ���� ��� ������������ �� ������
void deleteNode(char *str) {
    struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
    int flag = 0, res = 0;
    //�� � ���� ��� ���� �������������
    if (!root) {
            printf("BST is not present!!\n");
            return;
    }
    current = root;
    //��� �����
    while (1) {
            //��������� �� ���������� ��� ��������� ��� ����� ���� �������� ��� ��� ����� ���� Node
            res = strcasecmp(current->word, str);
            //�� �� ����� ��� ��������� ������� ��� ���� ��������� ����� ��� ������
            if (res == 0)
                    break;
            flag = res;
            //� ���� ������ ������� �� ������ Node
            parent = current;
            //������� ��� �� ���������� ��� ��������� ��� ������ ���� ��� ���� � �������� �����
            current = (res > 0) ? current->left : current->right;
            //�� �� ������ node ����� �����
            if (current == NULL)
                    return;
    }
    //if �������� ��� �������� ��� node
    //�� �� ������ node ��� ���� ���� �����
    if (current->right == NULL) {
            //�� ������ node ����� � ���� ��� ��� ��� �������� �����
            if (current == root && current->left == NULL) {
                    //���������� �� ������ Node
                    free(current);
                    //� ���� ��������
                    root = NULL;
                    return;
            //������ �� �� ������ ����� � ����
            } else if (current == root) {
                    //� ���� ������� �� �������� ����� ���
                    root = current->left;
                    //���������� �� ������ Node
                    free (current);
                    return;
            }

            flag > 0 ? (parent->left = current->left) :
                        (parent->right = current->left);
    //������ �� �� ������ Node ���� ���� �����
    } else {
            temp = current->right;
            //�� ��� ������� �������� �����
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
                    //������ �� ������� �� ����� ��� �������� �����
                    struct BSTnode *successor = NULL;
                    while (1) {//��� �����
                            successor = temp->left;//
                            if (!successor->left)
                                    break;
                            temp = successor;
                    }
                    temp->left = successor->right;
                    successor->left = current->left;
                    successor->right = current->right;
                    if (current == root) {
                            root = successor;//� �������� ����� � ����
                            free(current);//���������� �� ������ node
                            return;
                    }
                    (flag > 0) ? (parent->left = successor) :
                                    (parent->right = successor);
            }
    }
    free (current);
    return;
}

//��� ������� � ����� ������� �� ������ ��� ���� ��� ����� ��� ����������� ����
//��������� ���������� ��� ����� �� ����� Pointer ��� ������� �� node
//��� �������� ����� ��� ���� ��� ��� ��������� ���� �� ��� ��������� ���
void findElement(char *str) {
    struct BSTnode *temp = NULL;
    int flag = 0, res = 0;
    if (root == NULL) {//�� ��� ���� ������������� �� ������
            printf("Binary Search Tree is out of station!!\n");
            return;
    }
    temp = root;
    while (temp) {//��� �������� Nodes
            if ((res = strcasecmp(temp->word, str)) == 0) {//�� �� ���������� ��� ��������� ����� 0
                    //�������� ��� ���� ��� �� ��������� ���
                    printf("Word   : %s", str);
                    printf("Translation: %s", temp->translation);
                    flag = 1;
                    break;
            }
            //�� �� ���������� ����� ���������� ��� 0 ��� ��� �������� �����, ������ ��� ����
            temp = (res > 0) ? temp->left : temp->right;
    }
    //�� ��� ���� ������ ������ Node
    if (!flag)
            printf("Search Element not found in Binary Search Tree\n");
    return;
}

//��� ������� � ����� ������� �� ������ ��� ���� ��� node ��� ����������� ����
//��������� ���������� ��� ����� �� ����� Pointer ��� ��������� ��� �� nodes
void showAll(struct BSTnode *myNode) {
    if (myNode) {//�� ���� ������������� �� ������
            showAll(myNode->left);//�������� ��� ������ ��������� �� �������� node
            printf("Word    : %s", myNode->word);
            printf("Translation : %s", myNode->translation);
            printf("\n");
            showAll(myNode->right);//�������� ��� ������ ��������� �� ���� node
    }
    return;
}
//��� ������� � ����� ������� �� ������ ��� ���� ��� node ��� ����������� ����
//��������� ���������� ��� ����� �� ����� Pointer ��� ��������� ��� �� nodes
void printTree(struct BSTnode *myNode, int space) {
        //�� ���� ������������� �� ������
        if (myNode) {
            //������ ��� �������� ������ ��� ��������
            space += COUNT;
            //������� ��� ���� �����
            printTree(myNode->right, space);
            // �������� �� ������ node
            cout<<endl;
            for (int i = COUNT; i < space; i++)
            cout<<"X";
            cout<<myNode->word<<"\n";

            //������� ��� �������� �����
            printTree(myNode->left, space);
        }
        return;
}

//���� ����� � main �������
int main() {
    int ch;
    char str[128], translation[128];
    while (1) {//��� ����� �������� ��� ����������� ��� ������������
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
