#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // Map to store the number of seats that start/end at each station
    map<int, int> seat_changes;
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if we can accommodate this booking
        // We need to check if there are enough seats available from u to v-1
        
        // Create a vector of all relevant stations for this query
        vector<int> stations;
        stations.push_back(u);
        stations.push_back(v);
        
        // Add all keys from seat_changes that are in range [u, v)
        for (auto it = seat_changes.lower_bound(u); it != seat_changes.end() && it->first < v; ++it) {
            stations.push_back(it->first);
        }
        
        // Sort and remove duplicates
        sort(stations.begin(), stations.end());
        stations.erase(unique(stations.begin(), stations.end()), stations.end());
        
        // Check availability in each segment
        bool can_book = true;
        int current_seats = 0;
        
        // Calculate current occupancy at station u
        for (auto it = seat_changes.begin(); it != seat_changes.lower_bound(u); ++it) {
            current_seats += it->second;
        }
        
        // Check each segment
        for (int j = 0; j < stations.size() - 1; j++) {
            int seg_start = stations[j];
            int seg_end = stations[j+1];
            
            // If this segment is within our booking range and would exceed capacity
            if (seg_start >= u && seg_end <= v) {
                if (current_seats + n > k) {
                    can_book = false;
                    break;
                }
            }
            
            // Update current_seats for the next segment
            if (seat_changes.find(seg_start) != seat_changes.end()) {
                current_seats += seat_changes[seg_start];
            }
        }
        
        if (can_book) {
            // Update seat_changes with this booking
            seat_changes[u] += n;
            seat_changes[v] -= n;
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}