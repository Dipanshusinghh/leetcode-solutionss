class SegmentTree {
private:
    vector<int> tree;
    int n;

    void update(int idx, int val, int node, int left, int right) {
        if (left == right) {
            tree[node] = val;
            return;
        }

        int mid = (left + right) >> 1;

        if (idx <= mid)
            update(idx, val, node << 1, left, mid);
        else
            update(idx, val, node << 1 | 1, mid + 1, right);

        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }

    int query(int ql, int qr, int node, int left, int right) const {
        if (ql <= left && right <= qr)
            return tree[node];

        int mid = (left + right) >> 1;
        int ans = 0;

        if (ql <= mid)
            ans = max(ans, query(ql, qr, node << 1, left, mid));

        if (qr > mid)
            ans = max(ans, query(ql, qr, node << 1 | 1, mid + 1, right));

        return ans;
    }

public:
    SegmentTree(int size) : n(size) {
        tree.assign(4 * (n + 1), 0);
    }

    void update(int idx, int val) {
        update(idx, val, 1, 0, n);
    }

    int query(int l, int r) const {
        return query(l, r, 1, 0, n);
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        constexpr int MAX_POS = 50000;

        SegmentTree seg(MAX_POS);
        set<int> barriers = {0, MAX_POS};

        // Initially one segment [0, MAX_POS]
        seg.update(MAX_POS, MAX_POS);

        vector<bool> answer;

        for (const auto& query : queries) {
            if (query[0] == 1) {
                int pos = query[1];

                auto rightIt = barriers.upper_bound(pos);

                int right = *rightIt;
                int left = *prev(rightIt);

                // New segment lengths
                seg.update(pos, pos - left);
                seg.update(right, right - pos);

                barriers.insert(pos);
            }
            else {
                int x = query[1];
                int requiredSize = query[2];

                auto it = prev(barriers.upper_bound(x));
                int lastBarrier = *it;

                int largestGapBeforeX =
                    seg.query(0, lastBarrier);

                // Partial gap containing x
                largestGapBeforeX =
                    max(largestGapBeforeX, x - lastBarrier);

                answer.push_back(largestGapBeforeX >= requiredSize);
            }
        }

        return answer;
    }
};