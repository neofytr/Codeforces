#include <bits/stdc++.h>
using namespace std;

int main()
{
    string token;
    char delimeter = ' ';
    while (getline(cin, token, delimeter))
    {
        if (token[token.size() - 1] == '.')
        {
            token.pop_back();
        }

        cout << token << "\n";
    }

    return EXIT_SUCCESS;
}