#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    long long n;
    cin >> n;

    vector<pair<long long, long long> > customers(n); // arrival, departure
    for (auto &customer: customers) {
        cin >> customer.first >> customer.second;
    }

    sort(customers.begin(), customers.end(),
         [](const pair<long long, long long> &a, const pair<long long, long long> &b) {
             return a.first < b.first;
         });

    // min-heap to track the earliest ending room
    priority_queue<long long, vector<long long>, greater<long long> > room_endings;

    for (int i = 0; i < n; i++) {
        auto [arrival, departure] = customers[i];

        if (!room_endings.empty() && room_endings.top() < arrival) {
            //rReuse room
            room_endings.pop();
        }

        // assign room to current customer
        room_endings.push(departure);
    }

    cout << room_endings.size() << endl; // number of rooms needed

    return 0;
}
