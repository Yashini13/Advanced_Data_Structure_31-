#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to find the set of an element in a disjoint set
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// Function to perform union of two sets
void unionSets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare edges based on their weights (used for sorting)
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to find the minimum spanning tree using Kruskal's algorithm
void kruskalMST(struct Edge edges[], int V, int E) {
    // Allocate memory for the subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Sort the edges in non-decreasing order by their weights
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    // Initialize the result (minimum spanning tree)
    struct Edge* result = (struct Edge*)malloc((V - 1) * sizeof(struct Edge));

    // Index used to pick the next edge for result
    int i = 0;

    // Index used to pick the next edge from sorted edges
    int e = 0;

    // Construct the minimum spanning tree
    while (i < V - 1 && e < E) {
        struct Edge nextEdge = edges[e++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // If including this edge doesn't cause a cycle, add it to the result
        if (x != y) {
            result[i++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    // Display the minimum spanning tree
    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");
    for (int j = 0; j < V - 1; ++j) {
        printf("%d -- %d : %d\n", result[j].src, result[j].dest, result[j].weight);
    }

    // Free allocated memory
    free(subsets);
    free(result);
}

int main() {
    // Example graph representation with 4 vertices and 5 edges
    int V = 4;
    int E = 5;
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Find the minimum spanning tree
    kruskalMST(edges, V, E);

    return 0;
}
