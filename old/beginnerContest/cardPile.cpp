#include <bits/stdc++.h>
using namespace std;

int main()
{
    int q;
    cin >> q;

    stack<int> cards;
    for (int index = 0; index < 100; index++)
    {
        cards.push(0);
    }

    int c, x;
    while (q--)
    {
        cin >> c;
        if (c == 1)
        {
            cin >> x;
            cards.push(x);
        }
        else
        {
            cout << cards.top() << endl;
            cards.pop();
        }
    }

    return EXIT_SUCCESS;
}