#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cin >> str;

    string answer;
    int counter = 0;
    for (int index = 0; index < str.length(); index++)
    {
        if (isupper(str[index]))
        {
            answer.insert(counter++ + answer.begin(), str[index]);
        }
    }

    cout << answer << endl;
}