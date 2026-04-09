#include <bits/stdc++.h>

// For fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

struct Point {
    int x, y;
};

// Function to calculate squared Euclidean distance between two points
long long distSq(Point p1, Point p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

// Function to check if three points are collinear
// This is equivalent to checking if the area of the triangle formed by them is zero.
// Area = 0.5 * |x1(y2-y3) + x2(y3-y1) + x3(y1-y2)|
bool is_collinear(Point p1, Point p2, Point p3) {
    return (long long)p1.x * (p2.y - p3.y) +
           (long long)p2.x * (p3.y - p1.y) +
           (long long)p3.x * (p1.y - p2.y) == 0;
}

// Function to check if a triangle formed by three points is right-angled and non-degenerate
bool is_right_angled_non_degenerate(Point p1, Point p2, Point p3) {
    // A right-angled triangle must be non-degenerate.
    // If points are collinear, it's degenerate and thus not a right-angled triangle.
    if (is_collinear(p1, p2, p3)) {
        return false;
    }

    long long d12 = distSq(p1, p2);
    long long d13 = distSq(p1, p3);
    long long d23 = distSq(p2, p3);

    // Check Pythagorean theorem for all three possible hypotenuses
    // The sum of squares of two sides must equal the square of the third side.
    if (d12 + d13 == d23 ||
        d12 + d23 == d13 ||
        d13 + d23 == d12) {
        return true;
    }
    return false;
}

int main() {
    fast_io();

    std::vector<Point> p(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> p[i].x >> p[i].y;
    }

    // 1. Check if the original triangle is RIGHT
    // The problem guarantees the initial triangle is non-degenerate.
    if (is_right_angled_non_degenerate(p[0], p[1], p[2])) {
        std::cout << "RIGHT\n";
        return 0;
    }

    // 2. Check if it can become ALMOST right-angled by moving one point
    // Iterate through each of the three original points (p[0], p[1], p[2]).
    // For each point, consider its 4 possible moves (x+1, x-1, y+1, y-1).
    // There are 3 points * 4 moves = 12 possible new triangles to check.
    
    int dx[] = {0, 0, 1, -1}; // Changes in x-coordinate for moves
    int dy[] = {1, -1, 0, 0}; // Changes in y-coordinate for moves

    for (int i = 0; i < 3; ++i) { // Iterate through each point to potentially move (p[0], p[1], p[2])
        Point original_point = p[i]; // Store original point to restore it later

        for (int k = 0; k < 4; ++k) { // Iterate through 4 possible moves for the current point
            Point moved_point = {original_point.x + dx[k], original_point.y + dy[k]};
            
            // Create a temporary vector of points with the current point moved
            std::vector<Point> temp_p = p;
            temp_p[i] = moved_point;

            // Check if the new triangle is right-angled and non-degenerate
            if (is_right_angled_non_degenerate(temp_p[0], temp_p[1], temp_p[2])) {
                std::cout << "ALMOST\n";
                return 0; // Found an "ALMOST" case, no need to check further
            }
        }
    }

    // 3. If neither of the above conditions is met, then it's NEITHER
    std::cout << "NEITHER\n";

    return 0;
}