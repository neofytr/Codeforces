#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    string str;
    cin >> str;

    int n = static_cast<int>(str.length());

    vector<tuple<int, int, char>> res;

    int i = 0, j = 0;
    while (i < n) {
        j = i;

        while (j < n - 1 && str[j + 1] == str[j])
            j++;

        char choice1 = (str[i] == 'z' ? 'y' : 'z');
        char choice2 = (str[i] == 'a' ? 'b' : 'a');
        char choice3 = (str[i] == 'm' ? 'n' : 'm');
        char choice4 = (str[i] == 'o' ? 'p' : 'o');
        char replace;

        if (i == j) {
            res.push_back({i, j, str[i]});
            i++;
            continue;
        }

        if (!i && j == n - 1)
            replace = choice1;
        else if (!i && j < n - 1)
            replace = (str[j + 1] == choice1 ? choice2 : choice1);
        else if (i && j == n - 1)
            replace = (str[i - 1] == choice1 ? choice2 : choice1);
        else if (i && j < n - 1) {
            if (str[i - 1] == str[j + 1])
                replace = (str[i - 1] == choice1 ? choice2 : choice1);
            else {
                if ((str[i - 1] == choice1 && str[j + 1] == choice2) || (str[i - 1] == choice2 && str[j + 1] == choice1)) {
                    replace = (str[i] == 'c' ? 'd' : 'c');
                } else if (str[i - 1] == choice2 || str[i - 1] == choice2) {
                    replace = (str[j + 1] == choice3 ? choice4 : choice3);
                } else if (str[j + 1] == choice1 || str[j + 1] == choice2) {
                    replace = (str[i - 1] == choice3 ? choice4 : choice3);
                } else
                    replace = choice1;
            }
        }
        res.push_back({i, j, replace});
        i = j + 1;
    }

    for (auto &[i, j, r] : res) {
        if (i == j)
            cout << r;
        else {
            char same = str[i];
            int k = i;
            while (k <= j) {
                cout << same;
                k++;
                if (k <= j)
                    cout << r, k++;
            }
        }
    }
    cout << endl;
    return 0;
}