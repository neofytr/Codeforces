#include <bits/stdc++.h>

bool is_comfortable(int G_fingers, int B_fingers) {
    if (B_fingers < G_fingers - 1) {
        return false;
    }
    if (B_fingers > 2 * (G_fingers + 1)) {
        return false;
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int al, ar;
    int bl, br;

    std::cin >> al >> ar;
    std::cin >> bl >> br;

    bool possible = false;

    // Scenario 1: Boy is on the left of the girl.
    // Boy uses his right hand (br) to hold girl's left hand (al).
    if (is_comfortable(al, br)) {
        possible = true;
    }

    // Scenario 2: Boy is on the right of the girl.
    // Boy uses his left hand (bl) to hold girl's right hand (ar).
    if (is_comfortable(ar, bl)) {
        possible = true;
    }

    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}