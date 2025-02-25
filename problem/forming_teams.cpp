#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct
{
    int x, y;
} point_t;

float calc_distance(std::vector<point_t> &points, std::vector<int> &pairs)
{
    int size = pairs.size() / 2;
    float sum = 0;

    for (int i = 0; i < size; i++)
    {
        int idx1 = pairs[i * 2];
        int idx2 = pairs[i * 2 + 1];

        int x_diff = points[idx1].x - points[idx2].x;
        int y_diff = points[idx1].y - points[idx2].y;

        sum += sqrt(x_diff * x_diff + y_diff * y_diff);
    }

    return sum;
}

void solve(vector<point_t> &points)
{
    int size = points.size(); // size is guaranteed to be even
    vector<int> arr(size);

    // Initialize array with indices 0, 1, 2, ..., size-1
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    float min = __INT32_MAX__;
    vector<int> best;
    do
    {
        float curr = calc_distance(points, arr);
        if (curr < min)
        {
            min = curr;
            best = arr;
        }
    } while (next_permutation(arr.begin(), arr.end()));

    cout << "Minimum distance: " << min << "\n";
    cout << "Pairs:\n";
    for (int i = 0; i < size; i += 2)
    {
        cout << "(" << points[best[i]].x << ", " << points[best[i]].y << ")"
             << " - "
             << "(" << points[best[i + 1]].x << ", " << points[best[i + 1]].y << ")\n";
    }
}

int main()
{
    vector<point_t> points = {
        {1, 1}, {6, 8}, {8, 6}, {1, 3}};

    solve(points);

    return 0;
}