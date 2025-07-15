#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;

    bool removed = false;
    string result;

    for (char c : s)
    {
        if (!removed && c == '0')
        {
            removed = true;
            continue; // skip this '0'
        }
        result += c;
    }

    // if no zero was found, remove the last character (must be '1')
    if (!removed)
    {
        result.pop_back();
    }

    cout << result << endl;
}
