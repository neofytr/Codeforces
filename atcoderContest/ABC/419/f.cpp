#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

const int MOD = 998244353;

const int MAX_L = 100;
const int MAX_N = 8;
const int MAX_TOTAL_LEN = 80;
const int MAX_NODES = MAX_TOTAL_LEN + 2;
const int ALPHABET_SIZE = 26;

struct Node {
    int next[ALPHABET_SIZE];
    int fail_link;
    int output_mask;

    Node() {
        fill(next, next + ALPHABET_SIZE, 0);
        fail_link = 0;
        output_mask = 0;
    }
};

vector<Node> trie;
int num_nodes;

long long dp[MAX_L + 1][MAX_NODES][1 << MAX_N];

int go_memo[MAX_NODES][ALPHABET_SIZE];

void init_trie() {
    trie.assign(MAX_NODES, Node());
    num_nodes = 1;
}

void add_string(const string &s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == 0) {
            trie[v].next[c] = num_nodes++;
        }
        v = trie[v].next[c];
    }
    trie[v].output_mask |= (1 << id);
}

void build_aho_corasick() {
    queue<int> q;

    for (int c = 0; c < ALPHABET_SIZE; ++c) {
        if (trie[0].next[c] != 0) {
            q.push(trie[0].next[c]);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            int v = trie[u].next[c];
            if (v == 0)
                continue;

            int f = trie[u].fail_link;
            while (f != 0 && trie[f].next[c] == 0) {
                f = trie[f].fail_link;
            }

            if (trie[f].next[c] != 0) {
                trie[v].fail_link = trie[f].next[c];
            } else {
                trie[v].fail_link = 0;
            }

            trie[v].output_mask |= trie[trie[v].fail_link].output_mask;
            q.push(v);
        }
    }
}

int get_next_state(int state, int c) {
    if (go_memo[state][c] != -1) {
        return go_memo[state][c];
    }

    int current_state = state;
    while (current_state != 0 && trie[current_state].next[c] == 0) {
        current_state = trie[current_state].fail_link;
    }
    if (trie[current_state].next[c] != 0) {
        current_state = trie[current_state].next[c];
    }

    return go_memo[state][c] = current_state;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, L;
    cin >> N >> L;

    init_trie();
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        add_string(s, i);
    }

    build_aho_corasick();

    for (int i = 0; i < num_nodes; ++i) {
        fill(go_memo[i], go_memo[i] + ALPHABET_SIZE, -1);
    }

    dp[0][0][0] = 1;

    for (int i = 0; i < L; ++i) {
        for (int state = 0; state < num_nodes; ++state) {
            for (int mask = 0; mask < (1 << N); ++mask) {
                if (dp[i][state][mask] == 0)
                    continue;

                for (int c = 0; c < ALPHABET_SIZE; ++c) {
                    int next_state = get_next_state(state, c);
                    int next_mask = mask | trie[next_state].output_mask;

                    dp[i + 1][next_state][next_mask] = (dp[i + 1][next_state][next_mask] + dp[i][state][mask]) % MOD;
                }
            }
        }
    }

    long long ans = 0;
    int final_mask = (1 << N) - 1;
    for (int state = 0; state < num_nodes; ++state) {
        ans = (ans + dp[L][state][final_mask]) % MOD;
    }

    cout << ans << endl;

    return 0;
}