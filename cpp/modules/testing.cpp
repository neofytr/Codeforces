import Vector;
import <iostream>;
using namespace std;

int main(int argc, char **argv) {
    int n;
    cin >> n;
    const Vector vec(n);
    for (int i = 0; i < n; i++)
        cin >> vec[i];
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec[i];
    cout << sum << endl;
    return EXIT_SUCCESS;
}