#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (a == 1) {
            count1++;
        } else if (a == 2) {
            count2++;
        } else { // a == 3
            count3++;
        }
    }

    // To make all numbers equal to 1, we need to replace all numbers that are not 1.
    // The count of numbers not equal to 1 is n - count1.
    int replacements_to_1 = n - count1;
    
    // To make all numbers equal to 2, we need to replace all numbers that are not 2.
    // The count of numbers not equal to 2 is n - count2.
    int replacements_to_2 = n - count2;

    // To make all numbers equal to 3, we need to replace all numbers that are not 3.
    // The count of numbers not equal to 3 is n - count3.
    int replacements_to_3 = n - count3;

    // The minimum of these three options is the answer.
    int min_replacements = std::min({replacements_to_1, replacements_to_2, replacements_to_3});

    std::cout << min_replacements << std::endl;

    return 0;
}