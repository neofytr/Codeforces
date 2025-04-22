#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_map<long long, long long> min_arrival_date_to_room;
    priority_queue<long long, vector<long long>, greater<> > min_arrival_date;
    min_arrival_date.push(LLONG_MAX);
    long long curr_room_number = 0;
    vector<long long> room_number(n);

    long long arrival, departure;
    for (int index = 0; index < n; ++index) {
        cin >> arrival >> departure;
        if (arrival >= min_arrival_date.top()) {
            room_number[index] = min_arrival_date_to_room[min_arrival_date.top()];
            min_arrival_date.pop();
            min_arrival_date.push(departure + 1);
        } else {
            curr_room_number++;
            room_number[index] = curr_room_number;
            min_arrival_date_to_room[departure + 1] = curr_room_number;
            min_arrival_date.push(departure + 1);
        }
    }

    cout << curr_room_number << endl;
    for (int index = 0; index < room_number.size(); index++) {
        cout << room_number[index] << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}
