#include <stdio.h>
#include <stdlib.h>

// Define a structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to display the elements of the linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to insert a new element in sorted order
struct Node* insertSorted(struct Node* head, int data) {
    struct Node* newNode = createNode(data);

    // If the list is empty or the new node should be inserted at the beginning
    if (head == NULL || data < head->data) {
        newNode->next = head;
        return newNode;
    }

    // Traverse the list to find the correct position to insert the new node
    struct Node* current = head;
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }

    // Insert the new node in the sorted order
    newNode->next = current->next;
    current->next = newNode;

    return head;
}

// Function to delete a specific element from the linked list
struct Node* deleteElement(struct Node* head, int data) {
    // If the list is empty, return NULL
    if (head == NULL) {
        return NULL;
    }

    // If the element to be deleted is at the beginning of the list
    if (head->data == data) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    // Traverse the list to find the element to be deleted
    struct Node* current = head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    // If the element is not found, return the original list
    if (current->next == NULL) {
        return head;
    }

    // Delete the node containing the element
    struct Node* temp = current->next;
    current->next = current->next->next;
    free(temp);

    return head;
}

// Function to free memory allocated for the linked list nodes
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;

    // Insert elements in sorted order
    head = insertSorted(head, 30);
    head = insertSorted(head, 10);
    head = insertSorted(head, 50);
    head = insertSorted(head, 20);

    // Display the sorted linked list
    printf("Sorted Linked List: ");
    displayList(head);

    // Insert a new element in sorted order
    int elementToInsert = 25;
    printf("Inserting %d in sorted order.\n", elementToInsert);
    head = insertSorted(head, elementToInsert);

    // Display the updated linked list
    printf("Updated Linked List: ");
    displayList(head);

    // Delete an element from the linked list
    int elementToDelete = 30;
    printf("Deleting %d from the linked list.\n", elementToDelete);
    head = deleteElement(head, elementToDelete);

    // Display the updated linked list
    printf("Updated Linked List: ");
    displayList(head);

    // Free memory allocated for the linked list nodes
    freeList(head);

    return 0;
}
