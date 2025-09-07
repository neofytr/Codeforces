#include <bits/stdc++.h>
using namespace std;

void figure_it_out() {
    int how_many_numbers;
    cin >> how_many_numbers;

    vector<int> the_one_they_gave_us(how_many_numbers);
    for (int idx = 0; idx < how_many_numbers; ++idx) {
        cin >> the_one_they_gave_us[idx];
    }

    int the_constant_sum = how_many_numbers + 1;

    vector<int> the_one_we_make(how_many_numbers);
    for (int idx = 0; idx < how_many_numbers; ++idx) {
        the_one_we_make[idx] = the_constant_sum - the_one_they_gave_us[idx];
    }

    for (int idx = 0; idx < how_many_numbers; ++idx) {
        cout << the_one_we_make[idx];
        if (idx < how_many_numbers - 1) {
            cout << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int number_of_puzzles;
    cin >> number_of_puzzles;

    while (number_of_puzzles--) {
        figure_it_out();
    }

    return 0;
}