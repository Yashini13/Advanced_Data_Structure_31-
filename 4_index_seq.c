#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

// Structure to represent a student record
struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

// Structure to represent an index entry
struct IndexEntry {
    int rollNumber;
    long int position; // Position of the record in the data file
};

// Function to display a student record
void displayStudent(struct Student student) {
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Name: %s\n", student.name);
    printf("Marks: %.2f\n", student.marks);
}

// Function to display all records in the data file
void displayAllRecords(FILE* dataFile) {
    rewind(dataFile);

    struct Student student;
    while (fread(&student, sizeof(struct Student), 1, dataFile) == 1) {
        displayStudent(student);
        printf("----------\n");
    }
}

// Function to search for a student record by roll number
void searchRecord(FILE* dataFile, int rollNumber) {
    fseek(dataFile, 0, SEEK_SET);

    struct Student student;
    while (fread(&student, sizeof(struct Student), 1, dataFile) == 1) {
        if (student.rollNumber == rollNumber) {
            printf("Record found:\n");
            displayStudent(student);
            return;
        }
    }

    printf("Record with Roll Number %d not found.\n", rollNumber);
}

// Function to insert a new student record
void insertRecord(FILE* dataFile, FILE* indexFile, struct IndexEntry* index, int* totalRecords) {
    struct Student student;

    printf("Enter Roll Number: ");
    scanf("%d", &student.rollNumber);

    // Check if the roll number already exists
    for (int i = 0; i < *totalRecords; ++i) {
        if (index[i].rollNumber == student.rollNumber) {
            printf("Record with Roll Number %d already exists.\n", student.rollNumber);
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", student.name); // Read name with spaces
    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    // Write the record to the data file
    fseek(dataFile, 0, SEEK_END);
    long int position = ftell(dataFile);
    fwrite(&student, sizeof(struct Student), 1, dataFile);

    // Add the index entry to the index file
    index[*totalRecords].rollNumber = student.rollNumber;
    index[*totalRecords].position = position;

    (*totalRecords)++;

    // Sort the index entries based on roll number
    for (int i = 0; i < *totalRecords - 1; ++i) {
        for (int j = i + 1; j < *totalRecords; ++j) {
            if (index[i].rollNumber > index[j].rollNumber) {
                // Swap index entries
                struct IndexEntry temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
        }
    }

    // Write the sorted index entries back to the index file
    rewind(indexFile);
    fwrite(index, sizeof(struct IndexEntry), *totalRecords, indexFile);

    printf("Record inserted successfully.\n");
}

// Function to delete a student record by roll number
void deleteRecord(FILE* dataFile, FILE* indexFile, struct IndexEntry* index, int* totalRecords, int rollNumber) {
    for (int i = 0; i < *totalRecords; ++i) {
        if (index[i].rollNumber == rollNumber) {
            // Read the record from the data file
            fseek(dataFile, index[i].position, SEEK_SET);
            struct Student student;
            fread(&student, sizeof(struct Student), 1, dataFile);

            // Remove the record from the data file
            fseek(dataFile, index[i].position, SEEK_SET);
            fwrite("", 1, sizeof(struct Student), dataFile);

            // Remove the index entry from the index file
            for (int j = i; j < *totalRecords - 1; ++j) {
                index[j] = index[j + 1];
            }

            (*totalRecords)--;

            // Write the updated index entries back to the index file
            rewind(indexFile);
            fwrite(index, sizeof(struct IndexEntry), *totalRecords, indexFile);

            printf("Record with Roll Number %d deleted successfully.\n", rollNumber);
            return;
        }
    }

    printf("Record with Roll Number %d not found.\n", rollNumber);
}

int main() {
    FILE* dataFile = fopen("student_data.dat", "r+b"); // Open data file for reading and writing
    FILE* indexFile = fopen("student_index.dat", "r+b"); // Open index file for reading and writing

    if (dataFile == NULL || indexFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct IndexEntry index[MAX_RECORDS];
    int totalRecords = 0;

    // Read index entries from the index file
    fread(index, sizeof(struct IndexEntry), MAX_RECORDS, indexFile);

    // Count the total number of records
    for (int i = 0; i < MAX_RECORDS; ++i) {
        if (index[i].rollNumber != 0) {
            totalRecords++;
        }
    }

    int choice, rollNumber;

    do {
        printf("\n1. Display all records\n");
        printf("2. Search record by Roll Number\n");
        printf("3. Insert new record\n");
        printf("4. Delete record by Roll Number\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("All Records:\n");
                displayAllRecords(dataFile);
                break;

            case 2:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNumber);
                searchRecord(dataFile, rollNumber);
                break;

            case 3:
                insertRecord(dataFile, indexFile, index, &totalRecords);
                break;

            case 4:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteRecord(dataFile, indexFile, index, &totalRecords, rollNumber);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    // Close files
    fclose(dataFile);
    fclose(indexFile);

    return 0;
}
