#include <bits/stdc++.h>
using namespace std;

int main()
{
    tuple<int, string, char> tupleOne = {69, "raj", 'A'};
    tuple<int, int> tupleTwo(20, 10);

    cout << get<0>(tupleOne) << endl;
    cout << get<1>(tupleOne) << endl;

    get<0>(tupleOne) = 100;
    cout << get<0>(tupleOne) << endl;

    tuple<int, char, bool, float> thing;
    thing = make_tuple(10, 'R', false, 98.9);

    tuple<int, string> humanOne = make_tuple(20, "raj");
    tuple<int, string> humanTwo = make_tuple(17, "rishika");

    humanOne.swap(humanTwo); // swaps the values in humanOne and humanTwo
    // the tuples should have the same types and number of elements
}