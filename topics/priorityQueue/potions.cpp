#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long health = 0;
    long long potion_value;
    long long num_of_potions_drank = 0;

    priority_queue<long long> negatives;

    for (int index = 0; index < n; index++) {
        cin >> potion_value;
        if (potion_value >= 0) {
            health += potion_value;
            num_of_potions_drank++;
        } else {
            negatives.push(potion_value);
        }
    }

    while (!negatives.empty()) {
        const long long top = negatives.top();
        if (health + top >= 0) {
            health += top;
            num_of_potions_drank++;
        } else {
            break;
        }
    }

    cout << num_of_potions_drank << endl;
    return EXIT_SUCCESS;
}
