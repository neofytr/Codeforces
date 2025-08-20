module;
export module Vector;
import <cstddef>;
import <stdexcept>;

/*
 * Module Structure
 *
 *-----------------------
 * module;
 * #include <cstring>       <- Global Module Fragment
 * #define HELLO (10)
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

export class Vector {
  public:
    explicit Vector(size_t sz);
    double &operator[](size_t index) const;
    [[nodiscard]] size_t size() const;

    static constexpr size_t maxVectorSize = 100000;

  private:
    double *elements;
    size_t sz{};
};