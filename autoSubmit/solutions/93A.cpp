#include <iostream>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();
    long long n, m, a, b;
    std::cin >> n >> m >> a >> b;

    // Calculate 0-indexed row and column for folder 'a'
    long long ra = (a - 1) / m;
    long long ca = (a - 1) % m;

    // Calculate 0-indexed row and column for folder 'b'
    long long rb = (b - 1) / m;
    long long cb = (b - 1) % m;

    // Case 1: The desired folders (from 'a' to 'b') are all within a single row.
    // This forms a continuous horizontal segment that can be selected with one rectangle.
    if (ra == rb) {
        std::cout << 1 << std::endl;
    }
    // Case 2: The desired folders form a perfect rectangle spanning multiple rows.
    // This happens if folder 'a' is the first icon in its row (column 0),
    // and folder 'b' is the last icon in its row (column m-1).
    else if (ca == 0 && cb == m - 1) {
        std::cout << 1 << std::endl;
    }
    // Case 3: The desired folders require 2 selections. This covers several scenarios:
    // a) Folder 'a' is at the beginning of its row (ca == 0).
    //    We can select a rectangle from (ra, 0) to (rb-1, m-1) (all full rows up to 'rb-1')
    //    and a second rectangle for the partial row 'rb' from (rb, 0) to (rb, cb).
    // b) Folder 'b' is at the end of its row (cb == m-1).
    //    We can select a rectangle for the partial row 'ra' from (ra, ca) to (ra, m-1)
    //    and a second rectangle from (ra+1, 0) to (rb, m-1) (all full rows from 'ra+1' to 'rb').
    // c) Folder 'b' is the very last folder 'n' in the entire grid.
    //    In this situation, even if 'b' is not at the end of its visual row (cb < m-1),
    //    we can consider the actual end of the available icons for the last row to be 'cb'.
    //    So, we can select a rectangle for the partial first row (if ca > 0) and another for
    //    all subsequent rows up to (rb, cb), effectively treating 'cb' as the end of the content.
    //    Example: n=11, m=4, a=3, b=11.
    //    ra=0, ca=2. rb=2, cb=2.
    //    Here ca != 0 and cb != m-1 (2 != 3). However, b == n.
    //    We can select (0,2) to (0,3) (folders 3,4) in one rectangle.
    //    And (1,0) to (2,2) (folders 5-11) in a second rectangle. Total 2.
    else if (ca == 0 || cb == m - 1 || b == n) {
        std::cout << 2 << std::endl;
    }
    // Case 4: None of the above conditions are met. This means:
    // - The folders span multiple rows (ra < rb).
    // - They do not form a perfect multi-row rectangle.
    // - Folder 'a' is not at the beginning of its row (ca > 0).
    // - Folder 'b' is not at the end of its row (cb < m-1).
    // - Folder 'b' is not the very last folder 'n' (b < n).
    // In this complex scenario, we must use three selections:
    // 1. A rectangle for the partial starting row: from (ra, ca) to (ra, m-1).
    // 2. A rectangle for all complete middle rows: from (ra+1, 0) to (rb-1, m-1).
    // 3. A rectangle for the partial ending row: from (rb, 0) to (rb, cb).
    else {
        std::cout << 3 << std::endl;
    }

    return 0;
}