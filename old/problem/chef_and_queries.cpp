#include <stdio.h>
#include <bitset>
using namespace std;

const unsigned int MAX_N = 1u << 31;
const unsigned long long MASK = (1ull << 32) - 1;

int main() {
    unsigned int q;
    unsigned long long s, a, b;
    scanf("%u %llu %llu %llu", &q, &s, &a, &b);
    
    bitset<MAX_N> present;
    unsigned long long sum = 0;
    
    for (unsigned int i = 0; i < q; i++) {
        unsigned int num_to_edit = s >> 1;
        bool is_add = s & 1;
        
        // editing sum here itself is significantly more efficient than
        // iterating over the entire bitset later to calculate the sum
        if (num_to_edit < MAX_N) {
            if (is_add) {
                if (!present[num_to_edit]) {
                    present[num_to_edit] = 1;
                    sum += num_to_edit; 
                }
            } else {
                if (present[num_to_edit]) {
                    present[num_to_edit] = 0;
                    sum -= num_to_edit;
                }
            }
        }
        
        s = (a * s + b) & MASK;
    }
    
    printf("%llu\n", sum);
    return 0;
}