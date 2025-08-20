module;
export module Container;
import <cstddef>;

/*
 * An abstract type is a type that completely insulates a user from implementation details
 * To do that, we decouple the interface from the representation and give up genuine local variables
 * Since we don't know anything about the representation of an abstract type (not even it's size), we
 * must allocate objects on the free store and access them through references or pointers
 */

/*This class is a pure interface to specific containers defined later*/
// the word virtual means "may be redefined later in a class derived from this one"
// a function declared virtual is called a virtual function
// a class derived from Container provided an implementation for the container interface

// the = 0 syntax says that the function is pure virtual; that is, some class derived from Container
// must define the function; thus, it is not possible to define an object that is just a Container

// a Container can only serve as the interface to a class that implements it's operator and size functions
// a class with pure virtual functions is called an abstract class
// a class that provides the interface to a variety of other classes is called a polymorphic type
// as is common for abstract classes, Container does not have a constructor
// Container does have a destructor that is virtual, so that classes derived from Container can provide implementations

// again, that is common for abstract classes because they tend to be manipulated through references or pointers, and
// someone destroying a Container through a pointer has no idea what resources are owned by its implementation
export class Container {
  public:
    virtual double &operator[](size_t index) = 0;
    virtual const double &operator[](size_t index) const = 0; // for const access when container is used through a const reference
    [[nodiscard]] virtual size_t size() const = 0;
    virtual ~Container() = default;
};

/*
 * When you destroy an object of a derived type, the most derived destructor runs first.
 * Then, the base class destructor is called automatically (this is why a definition of it is required).
 * If there's a chain of inheritance, it continues up the hierarchy.
 *
 * Destructors are called in the reverse order of construction.
 * Construction goes from base to derived, while destruction goes from derived to base.
 */
