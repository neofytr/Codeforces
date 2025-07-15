#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

// Maximum possible value in the arrays (4000)
// Calculated as 4 * 10 * 10 * 10 = 4000
const size_t MAX_TOPIC = 4 * 10 * 10 * 10;

int main()
{
    // Temporary bitset for storing intermediate XOR results
    bitset<MAX_TOPIC + 1> temp;
    
    // Input variables
    size_t n;  // Length of first array
    size_t m;  // Length of second array
    size_t q;  // Number of queries
    
    // Query range variables
    size_t l_one, r_one;  // Range boundaries for first array
    size_t l_two, r_two;  // Range boundaries for second array
    size_t val;           // Input value
    
    // Read input array lengths and number of queries
    scanf("%zu %zu %zu", &n, &m, &q);
    
    // Create prefix arrays of bitsets
    // Each position stores XOR state of all previous elements
    vector<bitset<MAX_TOPIC + 1>> prefix_a(n + 1);  // For first array
    vector<bitset<MAX_TOPIC + 1>> prefix_b(m + 1);  // For second array
    
    // Process first array
    // Build prefix XOR array using bitsets
    for (size_t counter = 1; counter <= n; counter++)
    {
        scanf("%zu", &val);
        // Copy previous state
        prefix_a[counter] = prefix_a[counter - 1];
        // Toggle bit at position 'val'
        prefix_a[counter][val] = prefix_a[counter][val] ^ 1;
    }
    
    // Process second array
    // Build prefix XOR array using bitsets
    for (size_t counter = 1; counter <= m; counter++)
    {
        scanf("%zu", &val);
        // Copy previous state
        prefix_b[counter] = prefix_b[counter - 1];
        // Toggle bit at position 'val'
        prefix_b[counter][val] = prefix_b[counter][val] ^ 1;
    }
    
    // Process queries
    for (size_t counter = 0; counter < q; counter++)
    {
        // Read query ranges
        scanf("%zu %zu %zu %zu", &l_one, &r_one, &l_two, &r_two);
        
        // Compute XOR of range [l_one, r_one] from first array
        // XOR of range = prefix_XOR[right] ^ prefix_XOR[left-1]
        temp = prefix_a[l_one - 1] ^ prefix_a[r_one];
        
        // Combine with XOR of range [l_two, r_two] from second array
        temp ^= prefix_b[l_two - 1] ^ prefix_b[r_two];
        
        // Count number of set bits in result
        // This gives count of values appearing odd number of times
        printf("%zu\n", temp.count());
        
        // Reset temporary bitset for next query
        temp.reset();
    }
    
    return EXIT_SUCCESS;
}