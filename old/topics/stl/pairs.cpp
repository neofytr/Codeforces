#include <bits/stdc++.h>
using namespace std;

int main()
{
    int valOne;
    string valTwo;
    cin >> valOne >> valTwo;

    pair<int, string> pairOne = {valOne, valTwo};

    cout << pairOne.first << endl;
    cout << pairOne.second << endl;

    pairOne = make_pair(89, "hello");

    int first;
    string second;
    tie(first, second) = pairOne; // unpacks the pair

    cout << first << endl;
    cout << second << endl;

    return EXIT_SUCCESS;
}