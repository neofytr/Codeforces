#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;    // stores the input string of parentheses
    stack<int> st; // stack to store the index of the last unmatched '(' or the base of the current valid substring
    st.push(-1);   // push -1 as the base index for valid substring calculation

    cin >> str;      // take the input string
    int count = 0;   // to count the number of longest valid substrings
    int maxLen = -1; // to track the length of the longest valid substring

    // iterate through each character in the string
    for (int index = 0; index < str.length(); ++index)
    {
        if (str[index] == '(') // if the character is '(', push the index onto the stack
        {
            st.push(index);
        }
        else // if the character is ')'
        {
            if (!st.empty()) // if the stack is not empty
            {
                st.pop();        // pop the top element (matching '(')
                if (!st.empty()) // if stack is still not empty
                {
                    int length = index - st.top(); // calculate the length of the current valid substring
                    if (length > maxLen)           // if the length is greater than the previous maximum length
                    {
                        count = 1;       // reset count to 1 as we found a new longest valid substring
                        maxLen = length; // update the maximum length
                    }
                    else if (length == maxLen) // if the length is equal to the current maximum length
                    {
                        count++; // increment the count for substrings with the same maximum length
                    }
                }
                else // if the stack is empty after popping
                {
                    st.push(index); // set the current base for the next valid substring
                }
            }
        }
    }

    if (count == 0) // if no valid substring found
    {
        cout << "0 1\n"; // print 0 for length and 1 for count
        return 0;
    }

    cout << maxLen << " " << count << endl; // print the maximum length and the count of such substrings
    return 0;
}
