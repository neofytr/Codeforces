module;
export module Vector;
import <cstddef>;
import <stdexcept>;
import Container;
using namespace std;

/*
 * Module Structure
 *
 *-----------------------
 * module;
 * #include <cstring>       <- Global Module Fragment
 * #define HELLO (10)
 * export module Vector
 * ----------------------
 *
 * #include <string>        <- Module preamble
 * #include <iostream>
 *
 * ---------------------
 *  Module purview
 *
 */

/*
 * Global Module Fragment
 * Can only contain preprocessor directives
 * Allows old style #include of headers in a module
 * #include statements can only show up in the global module fragment; if you'll put them
 * elsewhere, you'll get errors
 */

/*
 * Module preamble
 * Should only contain import statements; maybe importing proper module files, or just old non C-library headers (header units)
 */

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

/*
 * The abstract class Container only defines an interface and no implementation.
 * For the Container abstract type to be useful, we have to implement a container that implements the functions required
 * by its interface.
 * The ": public" can be read as "is derived from" or "is subtype of".
 * Class Vector is said to be derived from class Container, and class Container is said to be a base class of Vector.
 * An alternative terminology calls Vector and Container subclass and superclass, respectively.
 * The derived class is said to inherit members from its base class, so the use of base and derived classes is commonly
 * referred to as Inheritence.
 */

// the members operator and size are said to override the corresponding members in the base class Container.
// The use of override is optional, but being explicit allows the compiler to catch mistakes, such as misspellings of function names
// or slight differences between the type of virtual function and its intended overrider.
// The destructor overrides the base class destructor.

// If we had a member in the class of some other class type, its destructor would be implicitly called by ~Vector().
// The compiler will automatically insert destructor calls for all member objects after executing your destructor body.

export class Vector final : public Container {
  public:
    explicit Vector(size_t sz, double init = 0.0);
    Vector(const initializer_list<double> &);
    double &operator[](size_t index) override;
    const double &operator[](size_t index) const override; // for const access when container is used through a const reference
    void push_back(double d);
    [[nodiscard]] size_t size() const override;
    ~Vector() override;

    static constexpr size_t maxVectorSize = 100000;

  private:
    double *elements;
    size_t sz;
    size_t underlyingSize;
};