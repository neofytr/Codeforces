export module Vector;
#include <cstddef>
#include <stdexcept>
using namespace std;

/*
 * This defines a module called Vector, which exports the class Vector, all it's member
 * functions, and the non-member function defining operator ==
 *
 * The way we use this module is to import it where we need it
 *
 * The differences between headers and modules are not just syntactic ->
 * 1. A module is compiled once only (rather than in each translation unit in which it's used)
 * 2. Two modules can be imported in either order without changing their meaning
 * 3. If you import or #include something into a module, users of your module do not implicitly
 * gain access to (and are not bothered by) that: import is not transitive
 */

export class Vector {
  public:
    explicit Vector(size_t sz);
    double &operator[](std::size_t index) const;
    [[nodiscard]] size_t size() const;

    static constexpr size_t maxVectorSize = 1e5;

  private:
    double *elements;
    size_t sz;
};

Vector::Vector(const size_t sz) {
    if (sz >= Vector::maxVectorSize)
        throw length_error("The given size exceeds the maximum vector size!");
    elements = new double[sz];
    this->sz = sz;
}

double &Vector::operator[](size_t index) const {
    return elements[index];
}

size_t Vector::size() const {
    return sz;
}

export bool operator==(const Vector &vecOne, const Vector &vecTwo) {
    if (vecOne.size() != vecTwo.size())
        return false;

    for (int i = 0; i < vecOne.size(); i++)
        if (vecOne[i] != vecTwo[i])
            return false;
    return true;
}
