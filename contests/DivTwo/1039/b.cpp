#include <deque>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_bad_move(const deque<int> &history, int next_val) {
    if (history.size() < 4) {
        return false;
    }

    vector<int> test_seq;
    for (int val : history) {
        test_seq.push_back(val);
    }
    test_seq.push_back(next_val);

    bool increasing = true;
    for (int i = 0; i < 4; ++i) {
        if (test_seq[i] >= test_seq[i + 1]) {
            increasing = false;
            break;
        }
    }
    if (increasing)
        return true;

    bool decreasing = true;
    for (int i = 0; i < 4; ++i) {
        if (test_seq[i] <= test_seq[i + 1]) {
            decreasing = false;
            break;
        }
    }
    if (decreasing)
        return true;

    return false;
}

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    int l = 0, r = n - 1;
    string result = "";
    deque<int> history;

    for (int turn = 0; turn < n; ++turn) {
        bool can_l = !is_bad_move(history, p[l]);
        bool can_r = !is_bad_move(history, p[r]);

        if (can_l && can_r) {
            int options_after_l = 0;
            if ((r - (l + 1) + 1) >= 1) {
                deque<int> temp_hist_l = history;
                temp_hist_l.push_back(p[l]);
                if (temp_hist_l.size() > 4)
                    temp_hist_l.pop_front();

                if (!is_bad_move(temp_hist_l, p[l + 1]))
                    options_after_l++;
                if ((r - (l + 1) + 1) >= 2 && !is_bad_move(temp_hist_l, p[r]))
                    options_after_l++;
            }

            int options_after_r = 0;
            if (((r - 1) - l + 1) >= 1) {
                deque<int> temp_hist_r = history;
                temp_hist_r.push_back(p[r]);
                if (temp_hist_r.size() > 4)
                    temp_hist_r.pop_front();

                if (!is_bad_move(temp_hist_r, p[l]))
                    options_after_r++;
                if (((r - 1) - l + 1) >= 2 && !is_bad_move(temp_hist_r, p[r - 1]))
                    options_after_r++;
            }

            if (options_after_l >= options_after_r) {
                result += 'L';
                history.push_back(p[l]);
                l++;
            } else {
                result += 'R';
                history.push_back(p[r]);
                r--;
            }
        } else if (can_l) {
            result += 'L';
            history.push_back(p[l]);
            l++;
        } else {
            result += 'R';
            history.push_back(p[r]);
            r--;
        }

        if (history.size() > 4) {
            history.pop_front();
        }
    }

    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}