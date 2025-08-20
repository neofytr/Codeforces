module Vector;
import <cstddef>;
using namespace std;

inline Vector::Vector(const size_t sz, double init) {
    if (sz >= Vector::maxVectorSize)
        throw length_error("The given size exceeds the maximum vector size!");
    elements = new double[sz];
    for (int i = 0; i < sz; i++)
        elements[i] = init;
    this->sz = sz;
}

inline double &Vector::operator[](size_t index) const {
    return elements[index];
}

inline size_t Vector::size() const {
    return sz;
}

inline bool operator==(const Vector &vecOne, const Vector &vecTwo) {
    if (vecOne.size() != vecTwo.size())
        return false;

    for (size_t i = 0; i < vecOne.size(); i++)
        if (vecOne[i] != vecTwo[i])
            return false;

    return true;
}

Vector::~Vector() {
    delete[] elements; // release resources
}
