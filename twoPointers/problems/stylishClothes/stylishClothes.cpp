#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: stylishClothes
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/D
// Difficulty: hard
// Tags:
// Strategy:

vector<int> caps, shirts, pants, shoes;
int capsSize, shirtsSize, pantsSize, shoesSize;

bool canFind(int x) {
    // can we find a set with style at-least x

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int maxi = LLONG_MIN;
    int mini = LLONG_MAX;
    cin >> n;
    capsSize = n;
    caps.resize(capsSize);
    for (int &val : caps) {
        cin >> val;
        maxi = max(maxi, val);
    }
    cin >> n;
    shirtsSize = n;
    shirts.resize(shirtsSize);
    for (int &val : shirts) {
        cin >> val;
        maxi = max(maxi, val);
    }
    cin >> n;
    pantsSize = n;
    pants.resize(pantsSize);
    for (int &val : pants) {
        cin >> val;
        maxi = max(maxi, val);
    }
    cin >> n;
    shoesSize = n;
    shoes.resize(shoesSize);
    for (int &val : shoes) {
        cin >> val;
        maxi = max(maxi, val);
    }
    // a set of clothes is a cap, shirt, pant and a shoe
    // each set is characterized by its style, the maximum difference between any two elements in the set
    // we are to find the set with the minimum style

    // if we can find a set with style at-least k, we can find a set with style at-least k + 1
    int right = maxi - mini; // can find
    int left = -1;           // can't find

    while (right != left + 1) {
        if (const int mid = left + (right - left) / 2; canFind(mid))
            right = mid;
        else
            left = mid;
    }
    return 0;
}