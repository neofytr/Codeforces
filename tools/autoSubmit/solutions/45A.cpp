#include <bits/stdc++.h>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    std::vector<std::string> months = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    std::string current_month_str;
    std::cin >> current_month_str;

    int k;
    std::cin >> k;

    int current_month_idx = -1;
    for (int i = 0; i < months.size(); ++i) {
        if (months[i] == current_month_str) {
            current_month_idx = i;
            break;
        }
    }

    // Calculate the new month index using modular arithmetic.
    // (current_month_idx + k) gives the total offset from January if we were to count linearly.
    // % 12 wraps this count around the 12 months of the year.
    int new_month_idx = (current_month_idx + k) % 12;

    std::cout << months[new_month_idx] << std::endl;

    return 0;
}