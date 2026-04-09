#include <bits/stdc++.h>

void solve() {
    std::string s1, s2;
    std::cin >> s1 >> s2;

    std::vector<std::vector<int>> positions(26);
    std::vector<bool> s1_has_char(26, false);

    for (int i = 0; i < s1.length(); ++i) {
        positions[s1[i] - 'a'].push_back(i);
        s1_has_char[s1[i] - 'a'] = true;
    }

    int ans = 1;
    int s1_last_match_idx = -1;

    for (int i = 0; i < s2.length(); ++i) {
        char char_to_find = s2[i];
        int char_code = char_to_find - 'a';

        if (!s1_has_char[char_code]) {
            std::cout << -1 << std::endl;
            return;
        }

        const auto& char_pos_list = positions[char_code];
        
        auto it = std::upper_bound(char_pos_list.begin(), char_pos_list.end(), s1_last_match_idx);

        if (it == char_pos_list.end()) {
            ans++;
            s1_last_match_idx = -1;
            
            it = std::upper_bound(char_pos_list.begin(), char_pos_list.end(), s1_last_match_idx);
            
            s1_last_match_idx = *it;
        } else {
            s1_last_match_idx = *it;
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}