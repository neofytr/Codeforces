#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

long long crunch_sum(const vector<int> &shelf) {
    long long pile = 0;
    for (int pebble : shelf) {
        pile += pebble;
    }
    return pile;
}

vector<int> twist_once(int sizeo, const vector<int> &rack) {
    vector<int> tally(sizeo + 2, 0);
    for (int pebble : rack) {
        tally[pebble]++;
    }

    int ghost = 0;
    while (ghost <= sizeo && tally[ghost] > 0) {
        ghost++;
    }

    vector<int> new_rack;
    new_rack.reserve(sizeo);
    for (int pebble : rack) {
        if (tally[pebble] == 1 && pebble < ghost) {
            new_rack.push_back(pebble);
        } else {
            new_rack.push_back(ghost);
        }
    }
    return new_rack;
}

void game_master() {
    int sizeo;
    long long cycles;
    cin >> sizeo >> cycles;
    vector<int> rack(sizeo);
    for (int i = 0; i < sizeo; ++i) {
        cin >> rack[i];
    }

    auto rack1 = twist_once(sizeo, rack);
    if (cycles == 1) {
        cout << crunch_sum(rack1) << endl;
        return;
    }

    auto rack2 = twist_once(sizeo, rack1);

    if (cycles % 2 == 0) {
        cout << crunch_sum(rack2) << endl;
    } else {
        auto rack3 = twist_once(sizeo, rack2);
        cout << crunch_sum(rack3) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int trials;
    cin >> trials;
    while (trials--) {
        game_master();
    }
    return 0;
}
