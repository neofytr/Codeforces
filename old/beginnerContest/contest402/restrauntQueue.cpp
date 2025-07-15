#include <bits/stdc++.h>
using namespace std;

int main()
{
    int q;
    cin >> q;

    queue<int> list;
    int x;
    int type;
    while (q--)
    {
        cin >> type;
        if (type == 1)
        {
            cin >> x;
            list.push(x);
        }
        else
        {
            cout << list.front() << "\n";
            list.pop();
        }
    }

    return EXIT_SUCCESS;
}