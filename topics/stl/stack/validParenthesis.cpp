#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> brackets;
        unordered_map<char, char> map = {
            {'}', '{'},
            {')', '('},
            {']', '['},
        };

        for (char character : s)
        {
            if (character == '{' || character == '[' || character == '(')
            {
                brackets.push(character);
            }
            else
            {
                // must be closing
                if (brackets.empty() || map[character] != brackets.top())
                {
                    return false;
                }

                brackets.pop();
            }
        }

        return !brackets.size();
    }
};
