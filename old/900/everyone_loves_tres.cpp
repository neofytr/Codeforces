#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isDivisibleBy66(const string &num)
{
    int n = num.length();

    if ((num[n - 1] - '0') % 2 != 0)
    {
        return false;
    }

    int digitSum = 0;
    for (char digit : num)
    {
        digitSum += (digit - '0');
    }
    if (digitSum % 3 != 0)
    {
        return false;
    }

    int altSum = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            altSum += (num[i] - '0');
        }
        else
        {
            altSum -= (num[i] - '0');
        }
    }
    return altSum % 11 == 0;
}

string nextNumber(string num)
{
    int n = num.length();
    int i = n - 1;

    while (i >= 0)
    {
        if (num[i] == '3')
        {
            num[i] = '6';
            break;
        }
        else
        {
            num[i] = '3';
            i--;
        }
    }

    if (i < 0)
    {
        return "";
    }

    return num;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        string num = string(n, '3');

        num[n - 1] = '6';

        bool found = false;

        while (!num.empty())
        {
            if (isDivisibleBy66(num))
            {
                cout << num << endl;
                found = true;
                break;
            }
            num = nextNumber(num);
        }

        if (!found)
        {
            cout << -1 << endl;
        }
    }

    return 0;
}