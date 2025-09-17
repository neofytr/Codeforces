#include <iostream>
#include <vector>

using namespace std;

#define int long long
constexpr int MOD = 1'000'000'007;

class Mat {
  private:
    vector<vector<int>> m;
    int n;

  public:
    explicit Mat(istream &in) {
        in >> n;
        m.assign(n, vector<int>(n));
        for (int row = 0; row < n; ++row)
            for (int col = 0; col < n; ++col)
                in >> m[row][col];
    }

    explicit Mat(const int size) : m(size, vector<int>(size, 0)), n(size) {}

    vector<int> &operator[](const int row) { return m[row]; }
    const vector<int> &operator[](const int row) const { return m[row]; }

    Mat operator*(const Mat &other) const {
        Mat result(n);
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                int sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum = (sum + m[row][k] * other[k][col]) % MOD;
                }
                result[row][col] = sum;
            }
        }
        return result; // the compiler will usually apply RVO and no unnecessary copies will occur
    }

    Mat(const int n, const int diag) {
        m.resize(n);
        for (int row = 0; row < n; row++)
            m[row].resize(n, 0), m[row][row] = diag;
    }

    int size() const { return n; }

    void print() const {
        for (const auto &row : m) {
            for (const auto &val : row)
                cout << val << ' ';
            cout << '\n';
        }
    }
};

Mat matExp(Mat base, int power) {
    Mat result(base.size(), 1);
    while (power) {
        if (power & 1)
            result = result * base;
        base = base * base;
        power >>= 1;
    }
    return result;
}

int32_t main() {
    int m;
    int n;
    cin >> m >> n;
    Mat mat(cin);
    const Mat result = matExp(move(mat), n);
    result.print();
    return 0;
}
