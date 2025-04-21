#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    stack<int> st; // stores the base of the current substring

    cin >> str;
    int count = 0;
    int maxLen = 0; // Changed to 0 instead of -1
    for (int index = 0; index < str.length(); ++index)
    {
        if (str[index] == '(')
        {
            st.push(index);
        }
        else
        {
            if (!st.empty())
            {
                st.pop(); // Pop the opening parenthesis

                int len = 0;
                if (!st.empty())
                {
                    len = index - st.top(); 
                }
                else
                {
                    len = index + 1; // This case handles the scenario when the stack is empty after popping
                }

                if (len > maxLen)
                {
                    count = 1;
                    maxLen = len;
                }
                else if (len == maxLen)
                {
                    count++;
                }
            }
        }
    }

    if (maxLen == 0)
    {
        cout << "0 1\n"; // If no valid substring is found
        return 0;
    }

    cout << maxLen << " " << count << endl;
    return 0;
}
