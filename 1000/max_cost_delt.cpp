#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, a, b;
    string str;

    cin >> n >> a >> b >> str;
    int len = str.length();

    if (!a)
    {
        cout << b << endl;
        return;
    }

    if (a > 0)
    {
        // a * l + b is an increasing function
        if (b >= 0)
        {
            // remove everthing one by one
            // this will give the max points

            cout << a * len + b * len << endl;
            return;
        }
        else
        {
            // b is negative
            // minimize the number of deletions themselves in this case

            int zerocount = 0;
            int onecount = 0;
            for (int index = 0; index < len; index++)
            {
                if (str[index] == '0')
                {
                    zerocount++;
                }
                else
                {
                    onecount++;
                }
            }

            if (onecount > zerocount)
            {
                bool found = false;
                int currlen = 0;
                vector<int> zeroes;

                for (int index = 0; index < len; index++)
                {
                    if (str[index] == '0')
                    {
                        if (!found)
                        {
                            found = true;
                            currlen = 1;
                        }
                        else
                        {
                            currlen++;
                        }
                    }
                    else if (found) // str[index] == '1'
                    {
                        zeroes.push_back(currlen);
                        found = false;
                        currlen = 0;
                    }
                }

                if (found)
                {
                    zeroes.push_back(currlen);
                }

                int pts = 0;
                pts += (onecount * a + b);

                for (int index = 0; index < zeroes.size(); index++)
                {
                    pts += (zeroes[index] * a + b);
                }

                cout << pts << endl;
                return;
            }
            else if (zerocount > onecount)
            {
                bool found = false;
                int currlen = 0;
                vector<int> ones;

                for (int index = 0; index < len; index++)
                {
                    if (str[index] == '1')
                    {
                        if (!found)
                        {
                            found = true;
                            currlen = 1;
                        }
                        else
                        {
                            currlen++;
                        }
                    }
                    else if (found) // str[index] == '0'
                    {
                        ones.push_back(currlen);
                        found = false;
                        currlen = 0;
                    }
                }

                if (found)
                {
                    ones.push_back(currlen);
                }

                int pts = 0;
                pts += (zerocount * a + b);

                for (int index = 0; index < ones.size(); index++)
                {
                    pts += (ones[index] * a + b);
                }

                cout << pts << endl;
                return;
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}