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
    map<int, int> events;
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if we can accommodate this booking
        // We need to check if there are enough seats available from u to v-1
        
        // Get all event points in the range [u, v)
        vector<int> points;
        points.push_back(u);
        
        // Add all event points in the range [u, v)
        auto it_low = events.lower_bound(u);
        auto it_high = events.lower_bound(v);
        for (auto it = it_low; it != it_high; ++it) {
            points.push_back(it->first);
        }
        
        // Sort points
        sort(points.begin(), points.end());
        
        // Check each segment between consecutive points
        bool can_book = true;
        
        // Calculate occupancy just before u
        int current_occupancy = 0;
        for (auto it = events.begin(); it != events.lower_bound(u); ++it) {
            current_occupancy += it->second;
        }
        
        // Check occupancy in each segment [points[i], points[i+1])
        for (int j = 0; j < (int)points.size() - 1; j++) {
            int start = points[j];
            int end = points[j+1];
            
            // This segment is within our booking range
            if (start >= u && end <= v) {
                if (current_occupancy + n > k) {
                    can_book = false;
                    break;
                }
            }
            
            // Update occupancy for the next segment
            if (events.find(start) != events.end()) {
                current_occupancy += events[start];
            }
        }
        
        // Also check the last segment from last point to v if needed
        if (can_book && !points.empty() && points.back() < v) {
            // Check occupancy from last point to v
            if (current_occupancy + n > k) {
                can_book = false;
            }
        }
        
        if (can_book) {
            // Update events with this booking
            events[u] += n;
            events[v] -= n;
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}