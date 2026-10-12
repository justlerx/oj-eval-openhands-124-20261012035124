#include <stdio.h>
#include <vector>

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) {
        return 1;
    }
    
    // Use a difference array to track seat changes
    // We'll use 1-based indexing, so we need x+1 elements
    std::vector<int> diff(x + 2, 0);  // diff[i] = change in seats at station i
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) {
            printf("N\n");
            continue;
        }
        
        // Check if we can accommodate this booking
        // We need to check if there are enough seats available from u to v-1
        
        // Create a copy of the current difference array
        std::vector<int> temp_diff = diff;
        
        // Apply the potential booking to the temporary difference array
        temp_diff[u] += n;
        temp_diff[v] -= n;
        
        // Check if any segment exceeds capacity
        bool can_book = true;
        int current_seats = 0;
        
        // Check from station 1 to x
        for (int j = 1; j <= x; j++) {
            current_seats += temp_diff[j];
            if (current_seats > k) {
                can_book = false;
                break;
            }
        }
        
        if (can_book) {
            // Update the actual difference array
            diff[u] += n;
            diff[v] -= n;
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}