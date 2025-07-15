#include <bits/stdc++.h>
using namespace std;

inline bool check_seven_dots(const string &line)
{
    return line.size() >= 7 && line.substr(0, 7) == ".......";
}

int main()
{
    string line, temp;
    if (getline(cin, temp) && !check_seven_dots(temp))
    {
        line = temp;
        while (getline(cin, temp) && !check_seven_dots(temp))
        {
            line += " " + temp;
        }
    }

    cout << "Final String: " << line << endl;
    return EXIT_SUCCESS;
}