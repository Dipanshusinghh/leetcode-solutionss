class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<int> pre(n + 1, 0);
        vector<char> dp(n, 0);
        dp[0] = 1;
        pre[1] = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == '0') {
                int l = max(0, i - maxJump);
                int r = i - minJump;
                if (r >= 0 && pre[r + 1] - pre[l] > 0)
                    dp[i] = 1;
            }
            pre[i + 1] = pre[i] + dp[i];
        }
        return dp[n - 1];
    }
};