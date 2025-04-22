#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Customer {
    long long arrival, departure, index;
};

int main() {
    long long n;
    cin >> n;

    vector<Customer> customers(n);
    for (long long i = 0; i < n; ++i) {
        cin >> customers[i].arrival >> customers[i].departure;
        customers[i].index = i;
    }

    // sort by arrival time
    sort(customers.begin(), customers.end(), [](const Customer &a, const Customer &b) {
        return a.arrival < b.arrival;
    });

    // min-heap to track (departure day, room number)
    priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long, long long>> > pq;
    vector<long long> result(n);
    long long roomCount = 0;

    for (const auto &cust: customers) {
        // free up room if earliest departure is before current arrival
        if (!pq.empty() && pq.top().first < cust.arrival) {
            auto [dep, room] = pq.top();
            pq.pop();
            result[cust.index] = room;
            pq.emplace(cust.departure, room);
        } else {
            // need new room
            ++roomCount;
            result[cust.index] = roomCount;
            pq.emplace(cust.departure, roomCount);
        }
    }

    cout << roomCount << '\n';
    for (const long long room: result)
        cout << room << ' ';
    cout << '\n';

    return 0;
}
