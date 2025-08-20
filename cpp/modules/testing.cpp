import Vector;
import Container;
import List;
import <iostream>;
using namespace std;
/*
 * For a function like calc to use a Container in complete ignorance of its implementation details,
 * some other function will have to make an object on which it can operate. This is what main does.
 *
 * Since calc doesn't know about Vector but only knows the Container interface, it will work
 * just as well for a different implementation of a Container -> List
 *
 * The point is that calc has no idea if its argument is a Vector or List, or some other kind of
 * container. Consequently, calc needn't be recompiled if the implementation of List/Vector changes
 * or a brand-new class derived from Container is used.
 *
 */
double calc(Container &c) {
    double sum = 0;
    for (int i = 0; i < static_cast<int>(c.size()); i++)
        sum += c[i];

    /*
     * What can we do if we want to use a member function that is only provided by a particular derived class?
     * We can ask "is this Container a kind of List" using the dynamic_cast operator:
     */

    /*
     * If at run-time, the object pointed to by the argument of dynamic_cast (here, &c) is not of the
     * expected type(here, List *), or a class derived from the expected type (so that it at-least has the
     * interfaces we want to use), dynamic_cast returns nullptr
     */

    /*
     * We use dynamic cast to a pointer type when a pointer to an object of a different derived class
     * is a valid argument. We can test whether the result is nullptr. This test can often conveniently
     * be placed in the initialization of a variable in a condition.
     */
    if (const auto lst = dynamic_cast<List *>(&c)) {
        lst->push(696969);
        sum += (*lst)[c.size() - 1];
    }

    /*
     * When a different type is unacceptable, we can simply dynamic_cast to a reference type.
     * If the object is not of the expected type, dynamic_cast throws a bad_cast exception:
     */
    try {
        auto &lst = dynamic_cast<List &>(c);
    } catch (const std::bad_cast &) {
        // c is not a list
    }
    return sum;
}

int main(int argc, char **argv) {
    int n;
    cin >> n;
    Vector vec(n);
    List lst;
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    double val;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> val;
        lst.push(val);
    }

    cout << calc(vec) << " " << calc(lst) << endl;
    return EXIT_SUCCESS;
}