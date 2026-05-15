class Solution {
public:
    int findMin(vector<int>& nums) {
        int sz = nums.size(), mid = sz/2;
        if(nums[sz-1] > nums[0])
            return nums[0];
        for(int i = mid, j = mid; i > 0 && j < sz; --i, ++j)
        {
            if(nums[i-1] > nums[i])
                return nums[i];
            if(nums[j+1] < nums[j])
                return nums[j+1];
        }
        return nums[0];
    }
};