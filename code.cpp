#include <stdio.h>
#include <stdlib.h>

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) {
        return 1;
    }
    
    // Use a difference array to track seat changes
    // We'll use 1-based indexing, so we need x+2 elements
    int *diff = (int *)calloc(x + 2, sizeof(int));
    if (diff == NULL) {
        return 1;
    }
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) {
            printf("N\n");
            continue;
        }
        
        // Check if we can accommodate this booking
        // We need to check if there are enough seats available from u to v-1
        
        // Create a copy of the current difference array
        int *temp_diff = (int *)malloc((x + 2) * sizeof(int));
        if (temp_diff == NULL) {
            printf("N\n");
            continue;
        }
        
        for (int j = 0; j <= x + 1; j++) {
            temp_diff[j] = diff[j];
        }
        
        // Apply the potential booking to the temporary difference array
        temp_diff[u] += n;
        temp_diff[v] -= n;
        
        // Check if any segment exceeds capacity
        int can_book = 1;
        int current_seats = 0;
        
        // Check from station 1 to x
        for (int j = 1; j <= x; j++) {
            current_seats += temp_diff[j];
            if (current_seats > k) {
                can_book = 0;
                break;
            }
        }
        
        // Free the temporary array
        free(temp_diff);
        
        if (can_book) {
            // Update the actual difference array
            diff[u] += n;
            diff[v] -= n;
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    // Free the difference array
    free(diff);
    return 0;
}