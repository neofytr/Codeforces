module Vector;
import <cstddef>;
using namespace std;

inline Vector::Vector(const size_t sz, const double init) {
    if (sz >= Vector::maxVectorSize)
        throw length_error("The given size exceeds the maximum vector size!");
    elements = new double[sz];
    for (size_t i = 0; i < sz; i++)
        elements[i] = init;
    this->sz = sz;
    underlyingSize = sz;
}

const double &Vector::operator[](const size_t index) const {
    return elements[index];
}

inline double &Vector::operator[](const size_t index) override {
    return elements[index];
}

inline size_t Vector::size() const {
    return sz;
}

inline Vector::Vector(const initializer_list<double> &lst) {
    const size_t lstSize = lst.size();
    sz = lstSize;
    elements = new double[sz];
    underlyingSize = sz;

    size_t index = 0;
    for (const double val : lst) {
        elements[index++] = val;
    }
}

void Vector::push_back(const double d) {
    if (underlyingSize == sz) {
        // reallocate
        if (sz > Vector::maxVectorSize / 2) {
            // would overflow
            throw length_error("Maximum size of vector exceeded!");
        }
        underlyingSize = sz << 2;
        auto *newElements = new double[underlyingSize];
        for (size_t index = 0; index < sz; index++)
            newElements[index] = elements[index];
        delete[] elements;
        elements = newElements;
    }
    elements[sz++] = d;
}

inline bool operator==(Vector &vecOne, Vector &vecTwo) {
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
