#include <algorithm>
#include <iostream>
using namespace std;

void crack_it() {
    long long thingy_a;
    long long thingy_b;
    cin >> thingy_a >> thingy_b;

    bool doable;
    if (thingy_a % 2 == thingy_b % 2) {
        doable = true;
    } else {
        if (thingy_a % 2 != 0 && thingy_b % 4 == 0) {
            doable = true;
        } else {
            doable = false;
        }
    }

    if (!doable) {
        cout << -1 << "\n";
        return;
    }

    long long biggest_sum;
    if (thingy_a % 2 != 0 && thingy_b % 2 != 0) {
        biggest_sum = max(thingy_a + thingy_b, thingy_a * thingy_b + 1);
    } else if (thingy_a % 2 == 0 && thingy_b % 2 == 0) {
        biggest_sum = max(thingy_a + thingy_b, thingy_a * (thingy_b / 2) + 2);
    } else {
        biggest_sum = max(thingy_a * 2 + thingy_b / 2, thingy_a * (thingy_b / 2) + 2);
    }

    cout << biggest_sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int how_many_rounds;
    cin >> how_many_rounds;
    while (how_many_rounds--) {
        crack_it();
    }

    return 0;
}
