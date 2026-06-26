class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        // Frequency of balance values.
        // Balance range can be [-n, n], so we use an offset of n.
        vector<int> balanceFreq(2 * n + 1, 0);
        int offset = n;
        int balance = 0;
        balanceFreq[offset] = 1;  // Initial balance = 0
        long long validSubarraysEndingHere = 0;
        long long totalSubarrays = 0;
        for (int num : nums) {
            if (num == target) {
                // Target contributes +1 to balance
                validSubarraysEndingHere += balanceFreq[offset + balance];
                balance++;
                balanceFreq[offset + balance]++;
            } else {
                // Non-target contributes -1 to balance
                balance--;
                validSubarraysEndingHere -= balanceFreq[offset + balance];
                balanceFreq[offset + balance]++;
            }
            totalSubarrays += validSubarraysEndingHere;
        }
      return totalSubarrays;
    }
};