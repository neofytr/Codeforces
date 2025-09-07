#include <iostream>
using namespace std;

long long magic_result;

void backtrack(int steps_left, long long current_val) {
    if (magic_result != -1)
        return;
    if (steps_left == 0) {
        magic_result = current_val;
        return;
    }
    if (current_val % 6 == 4) {
        backtrack(steps_left - 1, (current_val - 1) / 3);
    }
    if (magic_result != -1)
        return;
    backtrack(steps_left - 1, current_val * 2);
}

void run_a_case() {
    int jumps;
    long long target;
    cin >> jumps >> target;
    magic_result = -1;
    backtrack(jumps, target);
    cout << magic_result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int rounds;
    cin >> rounds;
    while (rounds--) {
        run_a_case();
    }
    return 0;
}
