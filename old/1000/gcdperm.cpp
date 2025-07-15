#include <iostream>
#include <vector>
using namespace std;

void generatePermutation(int n)
{
    vector<int> a;
    a.push_back(1);

    for (int x = 2; x <= n; x *= 2)
    {
        a.push_back(x);
    }

    for (int i = 3; i <= n; i += 2)
    {
        if (find(a.begin(), a.end(), i) == a.end())
        {
            for (int x = i; x <= n; x *= 2)
            {
                if (find(a.begin(), a.end(), x) == a.end())
                {
                    a.push_back(x);
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        generatePermutation(n);
    }
    return 0;
}