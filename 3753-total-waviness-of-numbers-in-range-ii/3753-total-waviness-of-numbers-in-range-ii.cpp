class Solution {
public:
    struct Node {
        long long cnt;
        long long sum;
    };
    string s;
    Node dp[20][2][11][11];
    bool vis[20][2][11][11];
    Node dfs(int pos, int tight, int prev2, int prev1) {
        if (pos == (int)s.size())
            return {1, 0};
        if (vis[pos][tight][prev2][prev1])
            return dp[pos][tight][prev2][prev1];
        vis[pos][tight][prev2][prev1] = true;
        Node ans = {0, 0};
        int lim = tight ? (s[pos] - '0') : 9;
        for (int d = 0; d <= lim; d++) {
            int ntight = tight && (d == lim);
            int nprev2 = prev2;
            int nprev1 = prev1;
            long long add = 0;
            if (prev1 == 10) {
                if (d != 0) {
                    nprev1 = d;
                }
            } else if (prev2 == 10) {
                nprev2 = prev1;
                nprev1 = d;
            } else {
                if ((prev1 > prev2 && prev1 > d) ||
                    (prev1 < prev2 && prev1 < d))
                    add = 1;
                nprev2 = prev1;
                nprev1 = d;
            }
            Node child = dfs(pos + 1, ntight, nprev2, nprev1);
            ans.cnt += child.cnt;
            ans.sum += child.sum + add * child.cnt;
        }
        return dp[pos][tight][prev2][prev1] = ans;
    }
    long long solve(long long x) {
        if (x <= 0) return 0;
        s = to_string(x);
        memset(vis, 0, sizeof(vis));
        return dfs(0, 1, 10, 10).sum;
    }
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};