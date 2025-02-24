#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int t, n;
    cin >> t;

    for (int counter = 0; counter < t; counter++)
    {
        cin >> n;
        vector<char> str(n + 1);
        cin >> str.data();

        unordered_map<char, int> freq;
        for (char c : str)
        {
            freq[c]++;
        }

        char max_char = str[0], min_char = str[0];
        int max_freq = freq[str[0]], min_freq = freq[str[0]];

        for (auto &[ch, count] : freq)
        {
            if (count > max_freq)
            {
                max_freq = count;
                max_char = ch;
            }
            if (count < min_freq)
            {
                min_freq = count;
                min_char = ch;
            }
        }

        for (char &c : str)
        {
            if (c == min_char)
            {
                c = max_char;
                break;
            }
        }

        cout << str.data() << endl;
    }
}
