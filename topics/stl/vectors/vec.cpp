#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {1, 2, 3, 4};
    arr.push_back(9); // array capacity should now become 8
    cout << arr.capacity() << endl;

    arr.shrink_to_fit(); // fit capacity to size of the array (5)
    cout << arr.capacity() << endl;

    cout << arr.front() << endl; // first element
    cout << arr.back() << endl; // last element

    cout << arr.at(3) << endl;
    arr.at(0) = 4;

    cout << arr.empty() << endl; // returns true if the vector is empty

    // iterating over arrays
    for (auto itr = arr.begin(); itr != arr.end(); ++itr)
    {
        cout << *itr << endl;
    }

    for (const auto val : arr)
    {
        cout << val << endl;
    }

    cout << "max size that can be allocated : " << arr.max_size();

    list<int> intList = {100, 200, 300};
    arr.insert(arr.begin(), intList.begin(), intList.end()); // insert elements
    // at arr.begin() from intList.begin() to intList.end() - 1

    arr.erase(arr.begin(), arr.begin() + 3);
    // remove elements from arr.begin() to arr.begin() + 3 - 1;

    // efficiently exchange the contents of two vectors (or other containers) without copying elements
    // O(1)
    vector<int> arrTwo = {1, 2, 3, 4};
    arrTwo.swap(arr);

    return EXIT_SUCCESS;
}
