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
    cout << arr.back() << endl;  // last element

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



    return EXIT_SUCCESS;
}