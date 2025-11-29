#include <bits/stdc++.h>
using namespace std;

void solve_the_mess() {
    int big_n;
    cin >> big_n;
    string s_dude, t_dude;
    cin >> s_dude >> t_dude;

    if (s_dude == t_dude) {
        cout << 0 << "\n";
        return;
    }

    vector<pair<int, int>> da_moves;
    
    auto flip_it_good = [&](int l_idx, int r_idx) {
        da_moves.push_back({l_idx + 1, r_idx + 1});
        for (int z = l_idx; z <= r_idx; z++) {
            s_dude[z] = (s_dude[z] == '0' ? '1' : '0');
        }
    };

    int limit_idx = big_n - 4;
    for (int i = 0; i < limit_idx; i++) {
        if (s_dude[i] == t_dude[i]) continue;
        
        if (s_dude[i] == s_dude[i+1]) {
            flip_it_good(i, i+1);
        } else if (s_dude[i] == s_dude[i+2]) {
            flip_it_good(i, i+2);
        } else {
            flip_it_good(i+1, i+2);
            flip_it_good(i, i+1);
        }
    }

    string target_tail = t_dude.substr(limit_idx);
    string curr_tail = s_dude.substr(limit_idx);
    
    if (curr_tail == target_tail) {
        cout << da_moves.size() << "\n";
        for(auto pp : da_moves) cout << pp.first << " " << pp.second << "\n";
        return;
    }

    map<string, pair<string, pair<int, int>>> momma_map;
    map<string, int> dist_tracker;
    queue<string> q_line;

    q_line.push(curr_tail);
    dist_tracker[curr_tail] = 0;
    momma_map[curr_tail] = {"", {-1, -1}};

    bool bingo = false;

    while(!q_line.empty()) {
        string u_state = q_line.front();
        q_line.pop();

        if (u_state == target_tail) {
            bingo = true;
            break;
        }

        for (int a = 0; a < 4; a++) {
            for (int b = a + 1; b < 4; b++) {
                bool is_pal_yo = true;
                for (int k = 0; k <= (b - a) / 2; k++) {
                    if (u_state[a + k] != u_state[b - k]) {
                        is_pal_yo = false;
                        break;
                    }
                }

                if (is_pal_yo) {
                    string v_next = u_state;
                    for (int k = a; k <= b; k++) {
                        v_next[k] = (v_next[k] == '0' ? '1' : '0');
                    }
                    if (dist_tracker.find(v_next) == dist_tracker.end()) {
                        dist_tracker[v_next] = dist_tracker[u_state] + 1;
                        momma_map[v_next] = {u_state, {a, b}};
                        q_line.push(v_next);
                    }
                }
            }
        }
    }

    if (!bingo) {
        cout << "-1\n";
    } else {
        vector<pair<int, int>> tail_ops;
        string walker = target_tail;
        while(walker != curr_tail) {
            auto info = momma_map[walker];
            tail_ops.push_back(info.second);
            walker = info.first;
        }
        reverse(tail_ops.begin(), tail_ops.end());
        
        cout << da_moves.size() + tail_ops.size() << "\n";
        for(auto pp : da_moves) cout << pp.first << " " << pp.second << "\n";
        for(auto pp : tail_ops) cout << (limit_idx + pp.first + 1) << " " << (limit_idx + pp.second + 1) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t_cases;
    cin >> t_cases;
    while(t_cases--) {
        solve_the_mess();
    }
    return 0;
}