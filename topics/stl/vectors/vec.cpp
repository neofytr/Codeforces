#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> arr = {1, 2, 3, 4};
    arr.push_back(9); // array capacity should now become 8
    cout << arr.capacity() << endl;

    arr.shrink_to_fit(); // fit capacity to size of the array (5)
    cout << arr.capacity() << endl;

    return EXIT_SUCCESS;
}