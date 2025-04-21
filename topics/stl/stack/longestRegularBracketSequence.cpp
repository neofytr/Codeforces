#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cin >> str; // take the input string of parentheses

    stack<int> st;
    st.push(-1); // push -1 as the base index to help compute lengths of valid substrings

    int maxLen = 0; // stores the maximum length of valid parentheses substring
    int count = 0;  // stores how many times the maxLen occurs

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            st.push(i); // if current character is '(', push its index
        }
        else
        {
            if (!st.empty())
                st.pop(); // pop the top because this ')' may close a previous '('

            if (!st.empty())
            {
                // compute the length of valid substring from current index to top of the stack
                int len = i - st.top();

                if (len > maxLen)
                {
                    maxLen = len; // found a new longer valid substring
                    count = 1;    // reset count to 1
                }
                else if (len == maxLen)
                {
                    count++; // found another valid substring of same max length
                }
            }
            else
            {
                st.push(i); // stack is empty, push current index as new base
            }
        }
    }

    if (!count)
        cout << "0 1\n"; // no valid substring found, default to "0 1"
    else
        cout << maxLen << " " << count << endl; // output the max length and its frequency

    return 0;
}
