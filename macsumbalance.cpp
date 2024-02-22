class Solution
{
public:
    class SGTree
    {
    public:
        vector<int> sg;
        SGTree(int n)
        {
            sg.resize(4 * n + 1);
        }
        int query(int ind, int low, int high, int l, int r)
        {
            if (r < low || high < l)
                return INT_MAX;
            if (l <= low && r >= high)
                return seg[ind];
            int mid = (low + high) >> 1;
            int left = query(2 * ind + 1, low, mid, l, r);
            int right = query(2 * ind + 2, mid + 1, high, l, r);
            return max(left, right);
        }
        void update(int ind, int low, int high, int i, int val)
        {
            if (low == high)
            {
                seg[ind] = val;
                return;
            }
            int mid = (low + high) >> 1;
            if (i <= mid)
            {
                update(2 * ind + 1, low, mid, i, val);
            }
            else
            {
                update(2 * ind + 2, mid + 1, high, i, val);
            }
            seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
            return;
        }
    };
    long long maxBalancedSubsequenceSum(vector<int> &nums)
    {
        int n = nums.size();
    }
};