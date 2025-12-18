#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int kjsfdhd;
    cin >> kjsfdhd;
    
    while (kjsfdhd--) {
        int oiwquey;
        cin >> oiwquey;
        string mnbvcxz;
        cin >> mnbvcxz;
        
        string pqowie = mnbvcxz + mnbvcxz;
        int lkhjfg = 0;
        int asdfgh = 0;
        
        for (char zcxvm : pqowie) {
            if (zcxvm == '0') {
                asdfgh++;
            } else {
                if (asdfgh > lkhjfg) {
                    lkhjfg = asdfgh;
                }
                asdfgh = 0;
            }
        }
        
        if (asdfgh > lkhjfg) {
            lkhjfg = asdfgh;
        }
        
        cout << lkhjfg << "\n";
    }
    
    return 0;
}