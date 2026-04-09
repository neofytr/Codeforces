#include <bits/stdc++.h>
using namespace std;

#define MAX 1000000000

int main()
{
    size_t n;
    cin >> n;

    bitset<MAX + 1> visited; // initialized to all zeroes;
    size_t num;

    for (size_t index = 0; index < n; index++)
    {
        cin >> num;
        visited[num] = true;
    }

    cout << visited.count() << endl;
}