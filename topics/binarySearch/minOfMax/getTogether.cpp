#include <bits/stdc++.h>
using namespace std;

// declare number of people
int n;

bool canGather(vector<long long> &pos, vector<long long> &speed, double time) {
    double max_left = -1e20;
    double min_right = 1e20;

    for (int i = 0; i < n; i++) {
        double left = pos[i] - time * speed[i];
        double right = pos[i] + time * speed[i];
        max_left = max(max_left, left);
        min_right = min(min_right, right);
    }

    return min_right >= max_left;
}


int main() {
    cin >> n;

    // declare vectors to store initial positions and speeds
    vector<long long> pos(n);
    vector<long long> speed(n);

    for (int i = 0; i < n; ++i) {
        cin >> pos[i] >> speed[i];
    }

    // there are n people on a real number line
    // person index is initially at position pos[index] and moves at maximum velocity speed[index]
    // we are asked to find the minimum time t >= 0
    // such that there exists a real number point x
    // where all people can gather in time at most t

    // define f(x) = max over all i of (abs(pos[i] - x) / speed[i])
    // f(x) represents the minimum time needed for everyone to gather at point x

    // our goal is to find min over all x in real numbers of f(x)

    // fix a candidate time t >= 0
    // for each person i, within time t, they can reach any point between:
    // [pos[i] - speed[i] * t, pos[i] + speed[i] * t]
    // these are closed intervals

    // all people can gather within time t if and only if
    // the intersection of all these intervals is non-empty

    // if the intersection is empty, then there is no point x
    // that everyone can reach within time t

    // monotonicity:
    // - if time t is sufficient (i.e., intervals intersect), then any larger time t' > t is also sufficient
    // - if time t is not sufficient, then any smaller time t' < t is also not sufficient

    // therefore, the set of feasible times is of the form [t_min, +infinity)
    // thus, we can binary search to find the minimum feasible time t_min

    // we maintain the invariant
    // they cannot gather at any point in time left
    // they can gather at some point in time right

    double left = 0; // they cannot gather at any point in zero time until and unless all their init pos are same
    // which I assume isn't the case
    double right = 1e24; // I assume they all can gather at some point in this ridiculously long time

    for (int index = 0; index < 100; index++) {
        double mid = left + (right - left) / 2;

        if (canGather(pos, speed, mid)) {
            // if they can gather in mid
            right = mid;
        } else {
            // if they cannot gather in mid
            left = mid;
        }
    }

    cout << fixed << setprecision(15) << right << endl;
    return EXIT_SUCCESS;
}
