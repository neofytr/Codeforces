#include <bits/stdc++.h>

// Function to map a point (x, y) on the square's perimeter to a single
// coordinate representing its distance from (0,0) along the perimeter
// in a counter-clockwise direction.
long long map_point_to_perimeter_coord(int x, int y, int n) {
    long long d;
    if (y == 0) { // Point is on the bottom side (x, 0)
        d = x;
    } else if (x == n) { // Point is on the right side (n, y)
        d = (long long)n + y;
    } else if (y == n) { // Point is on the top side (x, n)
        // Distance from (0,0) to (n,0) to (n,n) to (x,n)
        d = (long long)n + n + (n - x);
    } else { // Point is on the left side (0, y)
        // Distance from (0,0) to (n,0) to (n,n) to (0,n) to (0,y)
        d = (long long)n + n + n + (n - y);
    }
    return d;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, x1, y1, x2, y2;
    std::cin >> n >> x1 >> y1 >> x2 >> y2;

    long long d1 = map_point_to_perimeter_coord(x1, y1, n);
    long long d2 = map_point_to_perimeter_coord(x2, y2, n);

    long long perimeter = 4LL * n;

    long long diff = std::abs(d1 - d2);

    // The shortest path is either the direct difference or going the other way around the square
    long long shortest_distance = std::min(diff, perimeter - diff);

    std::cout << shortest_distance << std::endl;

    return 0;
}