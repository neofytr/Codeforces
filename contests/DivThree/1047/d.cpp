#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

void crack_it() {
    int sizeo;
    cin >> sizeo;

    vector<vector<int>> bucket(sizeo + 1);
    for (int indexo = 0; indexo < sizeo; ++indexo) {
        int magic_num;
        cin >> magic_num;
        bucket[magic_num].push_back(indexo);
    }

    for (int kappa = 1; kappa <= sizeo; ++kappa) {
        if (!bucket[kappa].empty()) {
            if (bucket[kappa].size() % kappa != 0) {
                cout << -1 << endl;
                return;
            }
        }
    }

    vector<int> puzzle(sizeo);
    int sticker = 0;

    for (int kappa = 1; kappa <= sizeo; ++kappa) {
        if (!bucket[kappa].empty()) {
            for (size_t idx = 0; idx < bucket[kappa].size(); ++idx) {
                if (idx % kappa == 0) {
                    sticker++;
                }
                puzzle[bucket[kappa][idx]] = sticker;
            }
        }
    }

    for (int indexo = 0; indexo < sizeo; ++indexo) {
        cout << puzzle[indexo] << (indexo == sizeo - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int rounds;
    cin >> rounds;
    while (rounds--) {
        crack_it();
    }
    return 0;
}
