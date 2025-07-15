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
        // drink every potion
        cin >> potion_value;
        health += potion_value;
        num_of_potions_drank++;

        if (potion_value < 0) {
            negatives.push(-potion_value);
        }

        if (health < 0) {
            // don't drink the max negative potion drank until now
            num_of_potions_drank--;
            health += negatives.top();
            negatives.pop();
        }
    }


    cout << num_of_potions_drank << endl;
    return EXIT_SUCCESS;
}
