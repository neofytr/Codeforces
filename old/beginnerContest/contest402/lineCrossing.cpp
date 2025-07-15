#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

// Returns true if two chords (a,b) and (c,d) intersect
bool do_intersect(int a, int b, int c, int d, int n)
{
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);

    // If the chords share an endpoint, they don't intersect
    if (a == c || a == d || b == c || b == d)
        return false;

    // For points on a circle, we need to check if the arcs overlap
    // Two chords intersect if their arcs "cross" each other

    // Two cases to consider:
    // 1. One arc is contained entirely within the other (no intersection)
    // 2. The arcs overlap partially (intersection)

    // We'll check if each arc contains exactly one endpoint of the other

    auto is_between = [n](int x, int start, int end)
    {
        if (start <= end)
            return start < x && x < end;
        else
            return start < x || x < end; // Wrap around
    };

    // Check if exactly one endpoint of chord (c,d) is within arc (a,b)
    bool c_in_ab = is_between(c, a, b);
    bool d_in_ab = is_between(d, a, b);

    // Check if exactly one endpoint of chord (a,b) is within arc (c,d)
    bool a_in_cd = is_between(a, c, d);
    bool b_in_cd = is_between(b, c, d);

    // Chords intersect if exactly one endpoint of each chord is inside the arc defined by the other
    return (c_in_ab ^ d_in_ab) && (a_in_cd ^ b_in_cd);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> chords(m);
    for (int i = 0; i < m; i++)
    {
        cin >> chords[i].first >> chords[i].second;
    }

    ll intersection_count = 0;

    // Check all pairs of chords for intersection
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            if (do_intersect(chords[i].first, chords[i].second,
                             chords[j].first, chords[j].second, n))
            {
                intersection_count++;
            }
        }
    }

    cout << intersection_count << endl;
    return 0;
}