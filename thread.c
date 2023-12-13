#include <stdio.h>
#include <stdlib.h>

// Define a structure for a threaded binary tree node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate whether the right pointer is threaded
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// Function to perform inorder traversal using threaded binary tree
void inorderTraversal(struct Node* root) {
    struct Node* current = root;

    while (current != NULL) {
        // Find the leftmost node in the current subtree
        while (current->left != NULL) {
            current = current->left;
        }

        // Print the current node's key
        printf("%d ", current->key);

        // Check if the right pointer is threaded or not
        if (current->isThreaded) {
            // Move to the inorder successor
            current = current->right;
        } else {
            // Move to the leftmost node of the right subtree
            current = current->right;

            // Move up the tree until a node with a left child is found
            while (current != NULL && !current->isThreaded) {
                current = current->left;
            }
        }
    }
}

// Function to insert a key into threaded binary tree
struct Node* insert(struct Node* root, int key) {
    struct Node* newNode = createNode(key);

    if (root == NULL) {
        return newNode;
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    // Find the position to insert the new node
    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            if (current->left == NULL) {
                current->left = newNode;
                current->isThreaded = 1; // Set the threaded flag
                newNode->right = current; // Set the right pointer to the inorder predecessor
                break;
            }
            current = current->left;
        } else if (key > current->key) {
            if (current->isThreaded || current->right == NULL) {
                newNode->right = current->right;
                current->right = newNode;
                current->isThreaded = 0; // Reset the threaded flag
                break;
            }
            current = current->right;
        } else {
            // Duplicate keys are not allowed in this example
            free(newNode);
            break;
        }
    }

    return root;
}

// Function to free memory allocated for the threaded binary tree nodes
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;

    // Insert elements into the threaded binary tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Display the inorder traversal of the threaded binary tree
    printf("Inorder traversal of the threaded binary tree: ");
    inorderTraversal(root);
    printf("\n");

    // Free memory allocated for the threaded binary tree nodes
    freeTree(root);

    return 0;
}
