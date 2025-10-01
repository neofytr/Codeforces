#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (1000000000 + 7)

class Mat {
private:
    vector<vector<int>> arr;
    int n;
public:
    Mat(const int sz, const int val) {
        n = sz;
        arr.resize(n);
        for (int r = 0; r < n; r++)
            arr[r].resize(n, val);
    }

    Mat operator*(const Mat &other) const {
        if (n != other.n)
            throw runtime_error("Cannot Multiply Square Matrices of Different Sizes!");
        Mat res(n, 0);
        for (int row = 0; row < n; row++) 
            for (int col = 0; col < n; col++) 
                int c = 0;
                for (int k = 0; k < n; k++) {
                    c = (c + (arr[row][k] % MOD) * (other[k][col] % MOD)) % MOD;
                
                res[row][col] = c;
            }
        return res;
    }

    int size() const {
        return n;
    }

    vector<int>& operator[](const int idx) {
        return arr[idx];
    }
};

Mat matpw(Mat base, int exp) {
    int n = base.size();
    Mat res(n, 0);
    for (int i = 0; i < n; i++) res[i][i] = 1; // identity
    while (exp) {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

// assumption -> base is passed to the function modulo MOD
int pw(int base, int exp) {
    int res = 1;
    while (exp) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;

        // 1 <= a, b <= 1e9
        int r1 = (a - b) % MOD;
        if (r1 < 0) r1 += MOD; 
        cout << r1 << " ";

        int r2 = a + b;
        if (r2 >= MOD) 
            r2 -= MOD;
        cout << r2 << "\n";
    }
}
