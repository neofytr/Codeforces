class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = (int)arr.size();
        if (n == 1)
            return 0;
        vector<bool> pref(n, false), suf(n, false);
        pref[0] = true, suf[n - 1] = true;
        for (int r = 1; r < n; r++) 
            if (arr[r] >= arr[r - 1] && pref[r - 1])
                pref[r] = true;

        for (int r = n - 2; r >= 0; r--)
            if (arr[r + 1] >= arr[r] && suf[r + 1])
                suf[r] = true;

        if (pref[n - 1]) 
            return 0; // we have to remove atleast one if this is not true, this is what
                        // the rest of the code does
        int l = 0; // Since l <= r always, we atleast remove one element (i = l = r), so, we should ensure beforehand if no element removed would work or not
        int mini = INT_MAX;
        for (int r = 0; r < n; r++) {
            while (l <= r) {
                // if the array remaining after removing [l, r] is non-decreasing, do l++
                if (!l && r == n - 1) // not possible
                    continue;
                
                if (!l) {
                    if (suf[r + 1])
                        l++;
                    else 
                        break;
                    continue;
                }

                if (r == n - 1) {
                    if (pref[l - 1])
                        l++;
                    else 
                        break;
                    continue;
                }

                if (suf[r + 1] && pref[l - 1] && arr[l - 1] <= arr[r + 1])
                    l++;
                else 
                    break;    
            }

            if (l >= 1) {
                mini = min(mini, r - l + 2);
            }
        }
        return mini;
    }
};