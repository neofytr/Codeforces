#include <bits/stdc++.h>
using namespace std;

int main()
{
    string token;
    vector<string> tokens;
    char delimeter = ' ';
    while (getline(cin, token, delimeter))
    {
        if (token[token.size() - 1] == '.')
        {
            token.pop_back();
        }

        tokens.push_back(token);
    }

    return EXIT_SUCCESS;
}