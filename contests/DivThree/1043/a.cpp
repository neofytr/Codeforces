#include <iostream>
#include <string>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::string a;
    std::cin >> a;
    int m;
    std::cin >> m;
    std::string b;
    std::cin >> b;
    std::string c;
    std::cin >> c;

    std::string result = a;

    for (int i = 0; i < m; ++i) {
        if (c[i] == 'V') {
            result = b[i] + result;
        } else {
            result += b[i];
        }
    }

    std::cout << result << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}