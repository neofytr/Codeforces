#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n;
    std::cin >> n;

    std::vector<std::string> names = {"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};

    long long cans_per_person_block = 1;

    while (n > 5 * cans_per_person_block) {
        n -= 5 * cans_per_person_block;
        cans_per_person_block *= 2;
    }
    
    long long person_index = (n - 1) / cans_per_person_block;

    std::cout << names[person_index] << std::endl;

    return 0;
}