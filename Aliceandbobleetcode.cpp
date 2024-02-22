#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define lli long long int
#define dv vector<ll>
#define no() cout << "NO" << endl
#define yes() cout << "YES" << endl
#define all(v) v.begin(), v.end()
#define f(i, n) for (lli i = 0; i < n; i++)
#define f1(i, n) for (lli i = 1; i <= n; i++)
#define fast                           \
    ios_base ::sync_with_stdio(false); \
    cin.tie(NULL);
#define display(v)         \
    for (auto it : v)      \
        cout << it << " "; \
    cout << endl;
class SGTree
{
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1, 0);
    }
    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    int query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (r < low || high < l)
            return 0;

        // complete overlap
        if (l <= low && r >= high)
            return seg[ind];

        // partial overlap
        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return max(left, right);
    }
};
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
    {
        int n = heights.size(), m = queries.size();
        SGTree sgt(n);
        sgt.build(0, 0, n - 1, heights);
        vector<int> ans;
        for (int i = 0; i < m; i++)
        {
            int a = queries[i][0];
            int b = queries[i][1];
            if (a > b)
                swap(a, b);
            if (a == b || heights[a] < heights[b])
            {
                ans.push_back(b);
                continue;
            }
            int mn = max(heights[a], heights[b]) + 1;
            int lo = b, hi = n - 1, res = -1;
            while (lo <= hi)
            {
                int mid = (lo + hi) / 2;
                if (sgt.query(0, 0, n - 1, lo, mid) >= mn)
                {
                    res = mid;
                    hi = mid - 1;
                }
                else
                    lo = mid + 1;
            }
            if (res == -1)
                ans.push_back(-1);
            else
                ans.push_back(res);
        }
        return ans;
    }
int main()
{
  vector<int>heights={6,4,8,5,2,7};
  vector<vector<int>>queries={{0,1},{0,3},{2,4}};
  vector<int> ans = leftmostBuildingQueries(heights,queries);
}