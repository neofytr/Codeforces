#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> childrenMin(n);
    queue<pair<int, int> > line; // the pair stores child number and candies he wants more (at least)

    int min;
    for (int index = 0; index < n; index++) {
        cin >> min;
        childrenMin[index] = min;
        line.push(pair(index, min));
    }

    int last;
    while (!line.empty()) {
        pair<int, int> front = line.front();
        front.second -= m;
        if (front.second <= 0) {
            // child satisfied
            last = front.first + 1;
            line.pop();
        } else {
            // child not satisfied, push him to the back
            line.pop();
            line.push(front);
        }
    }

    cout << last << endl;
    return EXIT_SUCCESS;
}
