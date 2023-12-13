// //BFS TRAVERSAL 

// #include <stdio.h>
// #include <stdlib.h>

// // Structure for a tree node
// struct Node {
//     int data;
//     struct Node* left;
//     struct Node* right;
// };

// // Function to create a new node
// struct Node* createNode(int data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->left = NULL;
//     newNode->right = NULL;
//     return newNode;
// }

// // Function for breadth-first search (BFS) traversal of a tree
// void BFS(struct Node* root) {
//     if (root == NULL)
//         return;

//     // Create a queue for BFS and enqueue the root
//     struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * 1000); // Assuming a maximum of 1000 nodes
//     int front = 0, rear = 0;
//     queue[rear++] = root;

//     while (front < rear) {
//         struct Node* current = queue[front++];
//         printf("%d ", current->data);

//         // Enqueue the left child
//         if (current->left != NULL)
//             queue[rear++] = current->left;

//         // Enqueue the right child
//         if (current->right != NULL)
//             queue[rear++] = current->right;
//     }

//     free(queue);
// }

// // Function to free memory allocated for the tree nodes
// void freeTree(struct Node* root) {
//     if (root != NULL) {
//         freeTree(root->left);
//         freeTree(root->right);
//         free(root);
//     }
// }

// int main() {
//     // Constructing a sample binary tree
//     struct Node* root = createNode(1);
//     root->left = createNode(2);
//     root->right = createNode(3);
//     root->left->left = createNode(4);
//     root->left->right = createNode(5);
//     root->right->left = createNode(6);
//     root->right->right = createNode(7);

//     // Perform BFS traversal
//     printf("BFS traversal of the tree: ");
//     BFS(root);
//     printf("\n");

//     // Free memory allocated for the tree nodes
//     freeTree(root);

//     return 0;
// }


// DFS TRAVAERSAL 

#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Recursive function for depth-first search (DFS) traversal (preorder)
void recursiveDFS(struct Node* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    recursiveDFS(root->left);
    recursiveDFS(root->right);
}

// Iterative function for depth-first search (DFS) traversal (preorder) using a stack
void iterativeDFS(struct Node* root) {
    if (root == NULL)
        return;

    // Create a stack for DFS
    struct Node** stack = (struct Node**)malloc(sizeof(struct Node*) * 1000); // Assuming a maximum of 1000 nodes
    int top = -1;

    // Push the root to the stack
    stack[++top] = root;

    while (top >= 0) {
        // Pop a node from the stack and print its data
        struct Node* current = stack[top--];
        printf("%d ", current->data);

        // Push the right child first (since we want to process left child first)
        if (current->right != NULL)
            stack[++top] = current->right;

        // Push the left child
        if (current->left != NULL)
            stack[++top] = current->left;
    }

    free(stack);
}

// Function to free memory allocated for the tree nodes
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    // Constructing a sample binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Perform recursive DFS traversal (preorder)
    printf("Recursive DFS (Preorder) traversal of the tree: ");
    recursiveDFS(root);
    printf("\n");

    // Perform iterative DFS traversal (preorder)
    printf("Iterative DFS (Preorder) traversal of the tree: ");
    iterativeDFS(root);
    printf("\n");

    // Free memory allocated for the tree nodes
    freeTree(root);

    return 0;
}
