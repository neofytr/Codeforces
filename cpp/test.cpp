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

/*

Traditional Enums (enum)

enum Color {
red,
green,
blue
};

Underlying type -> usually int (but implementation-defined, can be smaller)
Scope -> enumerator names are injected into the score surrounding the declaration
Enumerators can be implicitly converted to int and compared with integers

Issues ->
1. No type safety (different enums can be compared)
2. Name pollution (all enum names are in the enclosing scope)

*/

/*

Scoped Enums (enum class)

enum class Color {
    Red,
    Green,
    Blue,
}

1. Underlying type
Default is int, but can explicitly specify:
enum class Color : unsigned char {red, green, blue}

2. Scope
Enumerator names are scoped inside the enum
Color c = Color::Red // must qualify with scope

3. Implicit Conversions
No implicit conversion to int. Must cast explicitly
int x = (int) Color::Red

The class after the enum specifies that an enumeration is strongly typed and that it's enumerators
are scoped.
Initializing an enum with a value from it's underlying type (by default, thats int) is allowed ->
Color x = Color{1};
Color y {1};

By default, enum class has assignment, initialization, and comparisons defined, and only those.
However, an enumeration is a user-defined type, so we can define operators for it ->

*/

enum class trafficLight : unsigned char { red, yellow, green };
trafficLight &operator++(trafficLight &t) {
    using enum trafficLight; // make the score trafficLight
    switch (t) {
    case green:
        return t = red;
    case yellow:
        return t = green;
    case red:
        return t = yellow;
    }
}

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