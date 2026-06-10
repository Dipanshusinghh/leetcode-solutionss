class Solution {
    vector<vector<int>> mxTable, mnTable;
    int getMax(int left, int right) {
        int len = right - left + 1;
        int p = 31 - __builtin_clz(len);
        return max(
            mxTable[left][p],
            mxTable[right - (1 << p) + 1][p]
        );
    }
    int getMin(int left, int right) {
        int len = right - left + 1;
        int p = 31 - __builtin_clz(len);
        return min(
            mnTable[left][p],
            mnTable[right - (1 << p) + 1][p]
        );
    }
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        int levels = 32 - __builtin_clz(n);
        mxTable.assign(n, vector<int>(levels));
        mnTable.assign(n, vector<int>(levels));
        for (int i = 0; i < n; i++) {
            mxTable[i][0] = nums[i];
            mnTable[i][0] = nums[i];
        }
        for (int j = 1; j < levels; j++) {
            int segment = 1 << j;
            for (int i = 0; i + segment <= n; i++) {
                mxTable[i][j] = max(
                    mxTable[i][j - 1],
                    mxTable[i + (segment >> 1)][j - 1]
                );
                mnTable[i][j] = min(
                    mnTable[i][j - 1],
                    mnTable[i + (segment >> 1)][j - 1]
                );
            }
        }
        priority_queue<tuple<int, int, int>> pq;
        for (int start = 0; start < n; start++) {
            int diff = getMax(start, n - 1) - getMin(start, n - 1);
            pq.push({diff, start, n - 1});
        }
        long long answer = 0;
        while (k-- && !pq.empty()) {
            auto [value, left, right] = pq.top();
            pq.pop();
            answer += value;
            if (left < right) {
                int newDiff = getMax(left, right - 1)
                            - getMin(left, right - 1);
                pq.push({newDiff, left, right - 1});
            }
        }
        return answer;
    }
};