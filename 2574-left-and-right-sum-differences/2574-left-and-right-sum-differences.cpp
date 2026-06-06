class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int size = nums.size();
        vector<int> result(size);
        // Har index ke left side ka sum store karo
        int leftSum = 0;
        for (int i = 0; i < size; i++) {
            result[i] = leftSum;
            leftSum += nums[i];
        }
        // Right side ka sum calculate karke difference nikaalo
        int rightSum = 0;
        for (int i = size - 1; i >= 0; i--) {
            result[i] = abs(result[i] - rightSum);
            rightSum += nums[i];
        }
        return result;
    }
};