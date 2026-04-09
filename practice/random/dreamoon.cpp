#include <bits/stdc++.h>
using namespace std;

int flow(int index, int currPos, int finalPos, string &Path) {
    int n = (int)Path.size();
    if (index >= n)
        if (currPos == finalPos)
            return 1;
        else
            return 0;
    if (Path[index] == '+')
        return flow(index + 1, currPos + 1, finalPos, Path);
    if (Path[index] == '-')
        return flow(index + 1, currPos - 1, finalPos, Path);
    return flow(index + 1, currPos + 1, finalPos, Path) + flow(index + 1, currPos - 1, finalPos, Path);
}

int32_t main() {
    string strOne;
    cin >> strOne;

    int pos = 0;
    for (char r : strOne)
        if (r == '+')
            pos++;
        else
            pos--;

    string strTwo;
    cin >> strTwo;

    int cnt = 0;
    for (char r : strTwo)
        if (r == '?')
            cnt++;

    double ans = flow(0, 0, pos, strTwo);
    cout << setprecision(18) << ans / (1 << cnt) << endl;
    return 0;
}