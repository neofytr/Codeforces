// https://vjudge.net/problem/AtCoder-arc061_a

#include <bits/stdc++.h>
using namespace std;

int stringToInt(const string &str)
{
    try
    {
        return stoi(str);
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

int main()
{
    string str;
    cin >> str;

    int length = str.length();
    int total = 0, sum = 0;

    for (size_t plus = 0; plus < (1 << length); plus++)
    {
        int curr_num = 0;
        for (int bit = 0; bit < length; bit++)
        {
        }
    }
}