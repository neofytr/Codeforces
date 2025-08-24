#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void laksjdhfg() {
    int nqwert;
    std::cin >> nqwert;
    std::vector<int> asdfghjkl(nqwert);
    for (int zxcvbnm = 0; zxcvbnm < nqwert; ++zxcvbnm) {
        std::cin >> asdfghjkl[zxcvbnm];
    }

    std::sort(asdfghjkl.begin(), asdfghjkl.end());

    bool poiuyt = false;
    for (int mnbvc = 0; mnbvc < nqwert - 1; ++mnbvc) {
        if (asdfghjkl[mnbvc] == asdfghjkl[mnbvc + 1]) {
            poiuyt = true;
            break;
        }
    }

    if (poiuyt) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int qwertyuiop;
    std::cin >> qwertyuiop;
    while (qwertyuiop--) {
        laksjdhfg();
    }

    return 0;
}