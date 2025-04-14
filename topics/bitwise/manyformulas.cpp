// https://vjudge.net/problem/AtCoder-arc061_a

#include <bits/stdc++.h>
using namespace std;

long long stringTolong(const string &str)
{
    try
    {
        return stoll(str);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Invalid argument: " << e.what() << endl;
        return 0;
    }
    catch (const out_of_range &e)
    {
        cerr << "Out of range: " << e.what() << endl;
        return 0;
    }
}

long long computeExpressionValue(const string &expression)
{
    long long result = 0;
    stringstream ss(expression);
    string number;

    while (getline(ss, number, '+'))
    {
        result += stringTolong(number);
    }

    return result;
}

int main()
{
    string str;
    cin >> str;

    string copied = str;

    long long length = str.length();

    if (length == 1)
    {
        cout << stringTolong(str) << endl;
        return EXIT_SUCCESS;
    }

    long long total = 0;

    for (long long plus = 0; plus < (1 << (length - 1)); plus++)
    {
        long long inserted = 0;
        for (long long bit = 0; bit < length - 1; bit++)
        {
            if (plus & (1 << bit))
            {
                copied.insert(bit + inserted + 1, "+");
                inserted++;
            }
        }

        total += computeExpressionValue(copied);
        copied = str;
    }

    cout << total << endl;
}