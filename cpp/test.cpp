#include <iostream>
using namespace std;
class Vector {
  public:
    // constructors defined for various situations
    Vector() {
        elt = nullptr;
        sz = 0;
        return;
    }
    Vector(int s) {
        elt = new double[s];
        sz = s;
        return;
    } // constructor
    double &operator[](int i) {
        return elt[i];
    } // defining what the operator [] means in context of Vectors
      // we return a reference so that the caller can also edit the value
    int size() { return sz; } // get the size of the vector

  private:
    double *elt; // pointer to the elements
    int sz;      // the number of elements
};

/*

both classes and structs are identical in terms of their features
except for the following two things ->

1. in a struct, members are public by default; the opposite is true for classes
2. struct uses public inheritance by default; class uses private inheritance by default

*/

int main() {
    int n;
    cin >> n;
    Vector vec(n);
    for (int i = 0; i < vec.size(); i++) {
        cin >> vec[i];
    }

    double sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    cout << sum;
    return EXIT_SUCCESS;
}