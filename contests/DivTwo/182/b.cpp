#include <bits/stdc++.h>
using namespace std;

void go() {
    int size;
    cin >> size;
    vector<int> arr(size);
    vector<bool> exists(size + 1, false);
    vector<int> blanks;

    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
        if (arr[i] != 0)
            exists[arr[i]] = true;
        else
            blanks.push_back(i);
    }

    if (blanks.empty()) {
        int left = -1, right = -1;
        for (int i = 0; i < size; ++i) {
            if (arr[i] != i + 1) {
                if (left == -1)
                    left = i;
                right = i;
            }
        }
        if (left == -1)
            cout << 0 << endl;
        else
            cout << right - left + 1 << endl;
        return;
    }

    vector<int> missing;
    for (int i = 1; i <= size; ++i)
        if (!exists[i])
            missing.push_back(i);

    int left_fix = size, right_fix = -1;
    for (int i = 0; i < size; ++i)
        if (arr[i] != 0 && arr[i] != i + 1) {
            left_fix = min(left_fix, i);
            right_fix = max(right_fix, i);
        }

    int final_left, final_right;
    bool must_match = false;
    if (blanks.size() == 1 && missing[0] == blanks[0] + 1)
        must_match = true;

    if (must_match) {
        final_left = left_fix;
        final_right = right_fix;
    } else {
        int first_blank = blanks.front();
        int last_blank = blanks.back();
        final_left = min(left_fix, first_blank);
        final_right = max(right_fix, last_blank);
    }

    if (final_left > final_right)
        cout << 0 << endl;
    else
        cout << final_right - final_left + 1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int times;
    cin >> times;
    while (times--) {
        go();
    }
    return 0;
}
