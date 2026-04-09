#include <bits/stdc++.h>
using namespace std;

bool func(const vector<int> &arr, const int mid, const int m) {
    const int n = static_cast<int>(arr.size());
    // we are to find that whether we can assign the books to the students in a manner such that
    // no student receives more than 'mid' number of pages

    int student_count = 1;
    int current_pages = 0;

    // the allocation is contiguous
    for (const int pages: arr) {
        if (pages > mid) {
            return false;
        }

        if (current_pages + pages > mid) {
            current_pages = pages;
            student_count++;
        }

        if (student_count > m) {
            return false;
        }
    }

    return true;
}

int main() {
    // given an array of n integers
    // where arr[i] represents the number of pages in the
    // ith book, and an integer m representing the number of students,
    // allocate all the books to the students so that each student gets at least once book,
    // each book is allocated to only one student, and the allocation is contiguous (in the array)

    // allocate all the books to all the m students in such a way that the maximum number of pages assigned to
    // a student is minimized

    // if the allocation of books is not possible, return -1

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    if (m > n) {
        // if the number of students is greater than the number of books
        // then obviously we can't allocate the books
        cout << -1 << endl;
        return EXIT_SUCCESS;
    }

    // now, m >= n, so we can at least assign books to each student

    // if there is an allocation where the max number of pages assigned is at most x, there is an allocation
    // where the max number of pages assigned is at most x + 1

    // if there is no allocation where the max number of pages assigned is at most x, then there is no
    // allocation where the max number of pages assigned is at most x - 1;

    // define
    // f[x] = 1 if there is an allocation where the max number of pages assigned is at most x
    //      = 0 if there is no allocation where the max number of pages assigned is at most x

    // f[0] = 0
    // f[max(arr) * n] = 1

    // f is monotonically increasing
    // so there is an alpha for which
    // f[x] = 0 for all x < alpha
    // f[x] = 1 for all x >= alpha

    // so there is no allocation where the max number of pages is at most beta where beta < alpha
    // and there is an allocation where the max number of pages is at most alpha
    // so alpha is the min we are looking for

    // we maintain the invariant that
    // f[left] = 0
    // f[right] = 1

    int left = 0;
    int right = *max_element(arr.begin(), arr.end()) * n;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (func(arr, mid, m)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << left << endl;
    return EXIT_SUCCESS;
}
