#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
 
#define MAX_N 10 // Maximum number of cities 
 
// Function to find the minimum value in row[i] excluding the i-th city 
int minRow(int matrix[MAX_N][MAX_N], int row, int exclude, int n) { 
    int min = INT_MAX; 
    for (int j = 0; j < n; j++) { 
        if (j != exclude && matrix[row][j] < min) { 
            min = matrix[row][j]; 
        } 
    } 
    return min; 
} 
 
// Function to find the minimum value in col[j] excluding the j-th city 
int minCol(int matrix[MAX_N][MAX_N], int col, int exclude, int n) { 
    int min = INT_MAX; 
    for (int i = 0; i < n; i++) { 
        if (i != exclude && matrix[i][col] < min) { 
            min = matrix[i][col]; 
        } 
    } 
    return min; 
}
// Function to reduce each row and column by their minimum value 
void reduceMatrix(int matrix[MAX_N][MAX_N], int rowReduce[MAX_N], int colReduce[MAX_N], int 
n) { 
    for (int i = 0; i < n; i++) { 
        rowReduce[i] = minRow(matrix, i, -1, n); // Calculate the minimum for each row 
        for (int j = 0; j < n; j++) { 
            matrix[i][j] -= rowReduce[i]; 
        } 
    } 
 
    for (int j = 0; j < n; j++) { 
        colReduce[j] = minCol(matrix, j, -1, n); // Calculate the minimum for each column 
        for (int i = 0; i < n; i++) { 
            matrix[i][j] -= colReduce[j]; 
        } 
    } 
} 
 
// Recursive function to solve TSP using branch and bound 
void tspBranchBound(int matrix[MAX_N][MAX_N], int rowReduce[MAX_N], int colReduce[MAX_N], 
int level, int path[MAX_N], int visited[MAX_N], int bound, int cost, int* minCost, int n) { 
    if (level == n) { 
        // If all cities have been visited 
        if (cost + matrix[path[level - 1]][path[0]] < *minCost) { 
            *minCost = cost + matrix[path[level - 1]][path[0]]; // Update minimum cost 
        } 
        return; 
    } 
 for (int i = 0; i < n; i++) { 
        if (!visited[i]) { 
            int newBound = bound; 
            int newCost = cost; 
            int temp = bound; 
 
            bound -= rowReduce[path[level - 1]]; 
            bound -= colReduce[i]; 
 
            if (level == 1) { 
                bound += ((minRow(matrix, path[level - 1], i, n)) / 2); 
            } else { 
                bound += ((minRow(matrix, path[level - 1], -1, n)) / 2); 
            } 
 
            if (bound + cost < *minCost) { 
                path[level] = i; 
                visited[i] = 1; 
 
                if (level == 1) { 
                    newCost = matrix[path[level - 1]][i]; 
                } else { 
                    newCost = cost + matrix[path[level - 1]][i]; 
                } 
 
                tspBranchBound(matrix, rowReduce, colReduce, level + 1, path, visited, bound, newCost, 
minCost, n); 
            } 
 
            // Reset visited array and path
   visited[i] = 0; 
            for (int j = 0; j < n; j++) { 
                path[j] = -1; 
            } 
 
            bound = temp; 
        } 
    } 
} 
 
// Function to solve TSP using branch and bound 
int solveTSP(int matrix[MAX_N][MAX_N], int n) { 
    int rowReduce[MAX_N], colReduce[MAX_N]; 
    int path[MAX_N]; 
    int visited[MAX_N]; 
    int bound = 0; 
    int minCost = INT_MAX; 
 
    // Initialize visited array and path 
    for (int i = 0; i < n; i++) { 
        visited[i] = 0; 
        path[i] = -1; 
    } 
 
    // Reduce the matrix 
    reduceMatrix(matrix, rowReduce, colReduce, n); 
 
    // Set initial bound 
    for (int i = 0; i < n; i++) { 
        bound += (rowReduce[i] + colReduce[i]);
    } 
 
    // Round bound to an integer 
    bound = (bound % 2 == 0) ? bound / 2 : bound / 2 + 1; 
 
    // Start from the first city 
    visited[0] = 1; 
    path[0] = 0; 
 
    // Call the recursive function to solve TSP 
    tspBranchBound(matrix, rowReduce, colReduce, 1, path, visited, bound, 0, &minCost, n); 
 
    return minCost; 
} 
 
int main() { 
    int n; 
    printf("Enter the number of cities (maximum %d): ", MAX_N); 
    scanf("%d", &n); 
 
    if (n < 2 || n > MAX_N) { 
        printf("Invalid number of cities.\n"); 
        return 1; 
    } 
 
    // Distance matrix representing the distances between cities 
    int matrix[MAX_N][MAX_N]; 
    printf("Enter the distance matrix (%d x %d):\n", n, n); 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
 scanf("%d", &matrix[i][j]); 
        } 
    } 
 
    printf("Minimum cost for TSP is: %d\n", solveTSP(matrix, n)); 
 
    return 0; 
}