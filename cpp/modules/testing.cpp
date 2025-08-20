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
    for (int i = 0; i < c.size(); i++)
        sum += c[i];
    return sum;
}

int main(int argc, char **argv) {
    int n;
    cin >> n;
    Vector vec(n);
    List lst;
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    for (int i = 0; i < n; i++)
        cin >> lst[i];

    cout << calc(vec) << " " << calc(lst) << endl;
    return EXIT_SUCCESS;
}