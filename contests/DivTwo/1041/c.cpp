#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

struct Interval {
    int start;
    int end;
};

// Custom comparator for sorting intervals
bool compareIntervals(const Interval& a, const Interval& b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

void solve() {
    int n;
    long long k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    std::vector<int> b(n);
    std::vector<Interval> intervals(n);
    long long initial_sum = 0;
    std::vector<long long> all_numbers;
    all_numbers.reserve(2 * n);

    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < n; ++i) std::cin >> b[i];

    for (int i = 0; i < n; ++i) {
        initial_sum += std::abs(a[i] - b[i]);
        intervals[i] = {std::min(a[i], b[i]), std::max(a[i], b[i])};
        all_numbers.push_back(a[i]);
        all_numbers.push_back(b[i]);
    }

    // Case 1: k >= n-1, Ali can connect everything
    if (k >= n - 1) {
        std::sort(all_numbers.begin(), all_numbers.end());
        long long max_possible_sum = 0;
        for (int i = 0; i < n; ++i) {
            max_possible_sum += (all_numbers[n + i] - all_numbers[i]);
        }
        std::cout << max_possible_sum << std::endl;
        return;
    }

    // Case 2: k < n-1
    std::sort(intervals.begin(), intervals.end(), compareIntervals);

    bool has_overlap = false;
    long long max_end = intervals[0].end;
    for (int i = 1; i < n; ++i) {
        if (intervals[i].start < max_end) {
            has_overlap = true;
            break;
        }
        max_end = std::max(max_end, (long long)intervals[i].end);
    }

    if (has_overlap) {
        std::cout << initial_sum << std::endl;
        return;
    }

    // Case 2b: All intervals are disjoint
    std::vector<long long> gaps;
    for (int i = 0; i < n - 1; ++i) {
        gaps.push_back(intervals[i + 1].start - intervals[i].end);
    }
    
    std::sort(gaps.begin(), gaps.end());

    long long increase = 0;
    for (int i = 0; i < k; ++i) {
        increase += gaps[i];
    }

    std::cout << initial_sum + 2 * increase << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}