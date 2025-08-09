#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>
#include <vector>

struct Point {
    long long x, y;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;
    std::vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::map<std::pair<long long, long long>, int> slope_counts;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            long long dx = points[j].x - points[i].x;
            long long dy = points[j].y - points[i].y;

            if (dx == 0) {
                dy = 1;
            } else if (dy == 0) {
                dx = 1;
            } else {
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                }
                long long common_divisor = std::gcd(std::abs(dx), std::abs(dy));
                dx /= common_divisor;
                dy /= common_divisor;
            }
            slope_counts[{dy, dx}]++;
        }
    }

    long long gross_trapezoid_count = 0;
    for (auto const &pair : slope_counts) {
        long long count = pair.second;
        gross_trapezoid_count += count * (count - 1) / 2;
    }

    std::map<std::pair<long long, long long>, int> midpoint_counts;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            long long sum_x = points[i].x + points[j].x;
            long long sum_y = points[i].y + points[j].y;
            midpoint_counts[{sum_x, sum_y}]++;
        }
    }

    long long parallelogram_count = 0;
    for (auto const &pair : midpoint_counts) {
        long long count = pair.second;
        parallelogram_count += count * (count - 1) / 2;
    }

    long long final_answer = gross_trapezoid_count - parallelogram_count;
    std::cout << final_answer << std::endl;

    return 0;
}