#include <bits/stdc++.h>
using namespace std;

int main()
{
    int scenario = 1;
    while (true)
    {
        int t;
        cin >> t;
        if (!t)
            break;

        cout << "Scenario #" << scenario++ << '\n';

        unordered_map<int, int> member_to_team; // mapping of member to it's team number
        for (int index = 1; index <= t; index++)
        {
            int num;
            cin >> num;

            for (int counter = 0; counter < num; counter++)
            {
                int member;
                cin >> member;
                member_to_team[member] = index;
            }
        }

        queue<int> team_queue;                       // the actual queue storing current team numbers
        unordered_map<int, queue<int>> team_members; // mapping of team number to it's current members
        unordered_set<int> in_queue;                 // stores which team numbers are in the line currently

        string command;
        while (cin >> command && command != "STOP")
        {
            if (command == "ENQUEUE")
            {
                int person;
                cin >> person;
                int team = member_to_team[person];
                if (!team) // not in any team
                {
                    team_queue.push(person); // insert at the end
                    // since this isn't a team we don't store it in in_queue
                }
                else
                {
                    // in a team
                    if (in_queue.count(team)) // check if the team in queue
                    {
                        // team is in queue
                        team_members[team].push(person);
                    }
                    else
                    {
                        // team is not in queue
                        in_queue.insert(team); // insert team into queue
                        team_queue.push(team); // push this team into the back

                        team_members[team].push(person);
                    }
                }
            }
            else if (command == "DEQUEUE")
            {
                int team = team_queue.front();
                if (in_queue.count(team)) // check if this is a team
                {
                    // this is a team
                    cout << team_members[team].front() << endl;
                    team_members[team].pop();

                    if (team_members[team].empty())
                    {
                        // if the team becomes empty
                        in_queue.erase(team);
                        team_queue.pop();
                    }
                }
                else
                {
                    // this is not a team
                    cout << team_queue.front() << endl;
                    team_queue.pop();
                }
            }
        }

        cout << '\n';
    }

    return 0;
}
