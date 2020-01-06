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

//δημιουργία μιας δομής δεδομένων τύπου struct με όνομα BSTnode που αποθηκεύει
//τα στοιχεία λέξη, μετάφραση τύπου char array και
//και άλλα στοιχεία τύπου struct τα left, right που συμβολίζουν τα παιδιά του node
struct BSTnode {
    char word[128], translation[128];
    struct BSTnode *left, *right;
};

//αρχικοποιώ την ρίζα τως άδεια
struct BSTnode *root = NULL;

//μια μέθοδος η οποία δέχεται ως είσοδο την τιμή της λέξης και της μετάφρασης που αντιστοιχεί στην
//διεύθυνση παραπομπής της λέξης και της μετάφρασης με χρήση Pointer και δημιουργεί ένα νέο Node
struct BSTnode * createNode(char *word, char *translation) {
    struct BSTnode *newnode;//δημιουργία παραπομπής νέου node τύπου BSTnode struct
    //δημιουργία νέου node τύπου struct BSTnode κατανέμοντας ένα μπλοκ μνήμης επιστρέφοντας έναν pointer
    //στην αρχη του μπλοκ με την χρήση της εντολής malloc
    newnode = (struct BSTnode *)malloc(sizeof(struct BSTnode));
    strcpy(newnode->word, word);//αρχικοποιούμε την τιμή του νέου node για την λέξη
    strcpy(newnode->translation, translation);//και την μετάφραση
    newnode->left = newnode->right = NULL;//αρχικοποιούμε και τα παιδιά του νέου Node ως άδεια
    return newnode;//επιστρέφουμε το νέο node
}

//μια μέθοδος η οποία δέχεται ως είσοδο την τιμή της λέξης και της μετάφρασης που αντιστοιχεί στην
//διεύθυνση παραπομπής της λέξης και της μετάφρασης με χρήση Pointer και προσθέτει ένα νέο node
//κάνοντας έλεγχο αρχικά για μοναδικό κλειδί στο δέδνδρο
void insert(char *word, char *translation) {
    //δημιουργία παραπομπής γονέα, τωρινού και νέου node τύπου BSTnode struct
    struct BSTnode *parent = NULL, *current = NULL, *newnode = NULL;
    int res = 0;
    if (!root) {//αν το δένδρο είναι άδειο
            root = createNode(word, translation);//στην ρίζα εκχωρούνται οι τιμές της λέξης και της μετάφρασης
            return;
    }
    //για κάθε τωρινό Node που δεν είναι άδειο
    for (current = root; current !=NULL;
        //αν για το τωρινό αποτέλεσμα η σύγκριση της εκχωρημένης λέξης
        //και της λέξης που έχουμε για να εκχωρήσουμε είναι μεγαλύτερο του 0
        //τότε πάμε στο δεξί παιδί αλλιώς στο αριστερό
        current = (res > 0) ? current->right : current->left) {
            //η εντολή strcasecmp συγκρίνει δύο λέξεις και επιστρέφει 0 αν είναι ίδιες
            //μικρότερο του 0 αν η 1η λέξη είναι μικρότερη λεξικογραφικά της 2ης
            //μεγαλύτερο του 0 αν η 1η λέξη είναι μεγαλύτερη λεξικογραφικά της 2ης
            res = strcasecmp(word, current->word);
            if (res == 0) {//αν είναι ίδιες οι λέξεις
                printf("Duplicate entry!!\n");
                return;
            }
            parent = current;//ο νέος γονέας γίνεται το τωρινό node
    }
    newnode = createNode(word, translation);//δημιουργώ νέο node
    //αν η λέξη είναι μεγαλύτερη από τον γονέα παέι στο δεξί παιδί
    //αλλιώς πάει στο αριστερό παιδί
    res > 0 ? (parent->right = newnode) : (parent->left = newnode);
    return;
}

//μια μέθοδος η οποία δέχεται ως είσοδο την τιμή της λέξης που αντιστοιχεί στην
//διεύθυνση παραπομπής της λέξης με χρήση Pointer και διαγράφει το node
//που περιέχει αυτήν την λέξη και ξαναφτιάχνει το δένδρο
void deleteNode(char *str) {
    struct BSTnode *parent = NULL, *current = NULL, *temp = NULL;
    int flag = 0, res = 0;
    //αν η ρίζα δεν έχει αρχικοποιηθεί
    if (!root) {
            printf("BST is not present!!\n");
            return;
    }
    current = root;
    //για πάντα
    while (1) {
            //παίρνουμε το αποτέλεσμα της σύγκρισης της λέξης προς διαγραφή και της λέξης κάθε Node
            res = strcasecmp(current->word, str);
            //αν σε αυτήν την επανάληψη βρήκαμε την λέξη σταματάμε αυτόν τον βρόγχο
            if (res == 0)
                    break;
            flag = res;
            //ο νέος γονέας γίνεται το τωρινό Node
            parent = current;
            //ανάλογα από το αποτέλεσμα της σύγκρισης των λέξεων πάμε στο δεξί ή αριστερό παιδί
            current = (res > 0) ? current->left : current->right;
            //αν το τωρινό node είναι άδειο
            if (current == NULL)
                    return;
    }
    //if δηλώσεις για διαγραφή του node
    //αν το τωρινό node δεν έχει δεξί παιδί
    if (current->right == NULL) {
            //το τωρινό node είναι η ρίζα και δεν έχω αριστερό παιδί
            if (current == root && current->left == NULL) {
                    //ελευθερώνω το τωρινό Node
                    free(current);
                    //η ρίζα αδειάζει
                    root = NULL;
                    return;
            //αλλιώς αν το τωρινό είναι η ρίζα
            } else if (current == root) {
                    //η ρίζα γίνεται το αριστερό παιδί της
                    root = current->left;
                    //ελευθερώνω το τωρινό Node
                    free (current);
                    return;
            }

            flag > 0 ? (parent->left = current->left) :
                        (parent->right = current->left);
    //αλλιώς αν το τωρινό Node έχει δεξί παιδί
    } else {
            temp = current->right;
            //αν δεν υπάρχει αριστερό παιδί
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
                    //αλλίως αν υπάρχει κα ιδεξί και αριστερό παιδί
                    struct BSTnode *successor = NULL;
                    while (1) {//για πάντα
                            successor = temp->left;//
                            if (!successor->left)
                                    break;
                            temp = successor;
                    }
                    temp->left = successor->right;
                    successor->left = current->left;
                    successor->right = current->right;
                    if (current == root) {
                            root = successor;//ο διάδοχος είναι η ρίζα
                            free(current);//ελευθερώνω το τωρινό node
                            return;
                    }
                    (flag > 0) ? (parent->left = successor) :
                                    (parent->right = successor);
            }
    }
    free (current);
    return;
}

//μια μέθοδος η οποία δέχεται ως είσοδο την τιμή της λέξης που αντιστοιχεί στην
//διεύθυνση παραπομπής της λέξης με χρήση Pointer και βρίσκει το node
//που περιέχει αυτήν την λέξη και την εμφανίζει μαζί με την μετάφρασή της
void findElement(char *str) {
    struct BSTnode *temp = NULL;
    int flag = 0, res = 0;
    if (root == NULL) {//αν δεν έχει αρχικοποιηθεί το δένδρο
            printf("Binary Search Tree is out of station!!\n");
            return;
    }
    temp = root;
    while (temp) {//όσο υπάρχουν Nodes
            if ((res = strcasecmp(temp->word, str)) == 0) {//αν το αποτέλεσμα της σύγκρισης είναι 0
                    //εμφανίζω την λέξη και τη μετάφρασή της
                    printf("Word   : %s", str);
                    printf("Translation: %s", temp->translation);
                    flag = 1;
                    break;
            }
            //αν το αποτέλεσμα είναι μεγαλύτερο του 0 πάω στο αριστερό παιδί, αλλιώς στο δεξί
            temp = (res > 0) ? temp->left : temp->right;
    }
    //αν δεν έχει βρεθεί κάποιο Node
    if (!flag)
            printf("Search Element not found in Binary Search Tree\n");
    return;
}

//μια μέθοδος η οποία δέχεται ως είσοδο την τιμή του node που αντιστοιχεί στην
//διεύθυνση παραπομπής της ρίζας με χρήση Pointer και εμφανίζει όλα τα nodes
void showAll(struct BSTnode *myNode) {
    if (myNode) {//αν έχει αρχικοποιηθεί το δένδρο
            showAll(myNode->left);//ξανακαλώ την μέθοδο περνώντας το αριστερό node
            printf("Word    : %s", myNode->word);
            printf("Translation : %s", myNode->translation);
            printf("\n");
            showAll(myNode->right);//ξανακαλώ την μέθοδο περνώντας το δεξί node
    }
    return;
}
//μια μέθοδος η οποία δέχεται ως είσοδο την τιμή του node που αντιστοιχεί στην
//διεύθυνση παραπομπής της ρίζας με χρήση Pointer και εμφανίζει όλα τα nodes
void printTree(struct BSTnode *myNode, int space) {
        //αν έχει αρχικοποιηθεί το δένδρο
        if (myNode) {
            //αυξάνω την απόσταση μεταξύ των επιπέδων
            space += COUNT;
            //πηγαίνω στο δεξί παιδί
            printTree(myNode->right, space);
            // εμφανίζω το τωρινό node
            cout<<endl;
            for (int i = COUNT; i < space; i++)
            cout<<"X";
            cout<<myNode->word<<"\n";

            //πηγαίνω στο αριστερό παιδί
            printTree(myNode->left, space);
        }
        return;
}

//αυτή είναι η main μέθοδος
int main() {
    int ch;
    char str[128], translation[128];
    while (1) {//για πάντα εμφανίζω τις λειτουργίες του προγράμματος
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
