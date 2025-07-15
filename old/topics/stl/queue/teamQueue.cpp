#include <bits/stdc++.h>
using namespace std;

int main()
{
    int scenario = 1;
    while (true)
    {
        int t;
        cin >> t;
        if (t == 0)
            break;

        cout << "Scenario #" << scenario++ << '\n';

        unordered_map<int, int> member_to_team; // mapping of member to it's team number
        for (int team = 1; team <= t; ++team)
        {
            int n;
            cin >> n;
            while (n--)
            {
                int member;
                cin >> member;
                member_to_team[member] = team;
            }
        }

        queue<int> team_queue;                       // the actual queue storing current team numbers
        unordered_map<int, queue<int>> team_members; // mapping of team number to it's current members
        unordered_set<int> in_queue;                 // stores which team numbers are in the line currently

        string command;
        while (cin >> command && command != "END")
        {
            if (command == "ENQUEUE")
            {
                int x;
                cin >> x;
                int team = member_to_team[x];

                if (!in_queue.count(team))
                {
                    team_queue.push(team);
                    in_queue.insert(team);
                }
                team_members[team].push(x);
            }
            else if (command == "DEQUEUE")
            {
                int team = team_queue.front();
                cout << team_members[team].front() << '\n';
                team_members[team].pop();

                if (team_members[team].empty())
                {
                    team_queue.pop();
                    in_queue.erase(team);
                }
            }
        }

        cout << '\n';
    }

    return 0;
}
