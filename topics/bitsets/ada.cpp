#include <bits/stdc++.h>
using namespace std;

#define MAX (2 * 10000)

int main() {
    int q;
    cin >> q;

    vector<bitset<MAX + 1> > arr(MAX + 1);
    char symbol;
    int x, y;
    while (q--) {
        cin >> symbol >> x >> y;
        switch (symbol) {
            case '+': {
                arr[x].set(y);
                break;
            }
            case '-': {
                arr[x].reset(y);
                break;
            }
            case 'v': {
                cout << (arr[x] | arr[y]).count() << endl;
                break;
            }
            case '^': {
                cout << (arr[x] & arr[y]).count() << endl;
                break;
            }
            case '!': {
                cout << (arr[x] ^ arr[y]).count() << endl;
                break;
            }
            case 92: {
                // 92 is the ascii for '\'
                cout << (arr[x] & (~arr[y])).count() << endl;
                break;
            }
            default: {
                cout << "not possible\n";
            }
        }
    }
}
