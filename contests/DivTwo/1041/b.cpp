#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, x;
        cin >> n >> x;
        x--; // Convert to 0-indexed
        
        string s;
        cin >> s;
        
        // Key insight: Let's think about what Hamid can achieve and what Mani can do to stop him
        
        // First, let's see if Hamid can escape immediately (day 1)
        bool canEscapeLeft = true, canEscapeRight = true;
        
        // Check if there are walls to the left
        for (int i = 0; i < x; i++) {
            if (s[i] == '#') {
                canEscapeLeft = false;
                break;
            }
        }
        
        // Check if there are walls to the right
        for (int i = x + 1; i < n; i++) {
            if (s[i] == '#') {
                canEscapeRight = false;
                break;
            }
        }
        
        // If Hamid can escape immediately
        if (canEscapeLeft || canEscapeRight) {
            cout << 1 << "\n";
            continue;
        }
        
        // Both directions have walls, so Hamid must destroy some walls
        
        // The key insight: Let's count distances
        // Distance to escape left = number of walls to the left  
        // Distance to escape right = number of walls to the right
        
        int wallsLeft = 0, wallsRight = 0;
        
        for (int i = 0; i < x; i++) {
            if (s[i] == '#') wallsLeft++;
        }
        
        for (int i = x + 1; i < n; i++) {
            if (s[i] == '#') wallsRight++;
        }
        
        // Now here's the crucial part I was missing:
        // Mani wants to maximize the game duration
        // Hamid wants to minimize it
        
        // If wallsLeft < wallsRight, Hamid prefers left
        // Mani will try to build walls on the left to make it less attractive
        // But Mani can only build walls where there are empty spaces
        
        // Let's count empty spaces on each side
        int emptyLeft = 0, emptyRight = 0;
        
        for (int i = 0; i < x; i++) {
            if (s[i] == '.') emptyLeft++;
        }
        
        for (int i = x + 1; i < n; i++) {
            if (s[i] == '.') emptyRight++;
        }
        
        // The total "cost" to escape left can be increased by Mani to: wallsLeft + emptyLeft
        // The total "cost" to escape right can be increased by Mani to: wallsRight + emptyRight
        
        // Mani will build walls optimally to maximize the minimum escape time
        // So the answer is: min(wallsLeft + emptyLeft, wallsRight + emptyRight) + 1
        
        // Wait, that's not right either. Let me think again...
        
        // Actually, I think the answer is much simpler:
        // Hamid needs to destroy min(wallsLeft, wallsRight) walls to escape
        // Plus 1 day for the final escape
        // Mani cannot prevent this - he can only delay by building walls,
        // but Hamid will always choose the optimal path
        
        cout << min(wallsLeft, wallsRight) + 1 << "\n";
    }
    
    return 0;
}