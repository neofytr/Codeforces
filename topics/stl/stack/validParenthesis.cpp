#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> bracket;
        unordered_map<char, char> matching = {
            {')', '('},
            {']', '['},
            {'}', '{'}};

        for (char ch : s)
        {
            if (ch == '(' || ch == '[' || ch == '{')
            {
                bracket.push(ch);
            }
            else
            {
                if (bracket.empty() || bracket.top() != matching[ch])
                {
                    return false;
                }
                bracket.pop();
            }
        }
        return bracket.empty();
    }
};
