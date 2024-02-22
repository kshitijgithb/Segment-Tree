#include <bits/stdc++.h>
using namespace std;
class SGTree
{
public:
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1, 0);
    }
    int query(int ind, int low, int high, int l, int r)
    {
        if (r < low || high < l)
            return 0;
        if (l <= low && r >= high)
            return seg[ind];
        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }
    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] += val;
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
        seg[ind] = (seg[2 * ind + 1] + seg[2 * ind + 2]);
        return;
    }
};
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    set<pair<int, int>> v;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        v.insert({arr[i], i});
    }
      sort(v.begin(), v.end());
    unordered_map<int, int> mp;
    int cnt = 0;
    for (auto it : v)
    {
        mp[it.second] = cnt;
        cnt++;
    }
    SGTree st(n);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int ind = mp[i];
        ans += st.query(0, 0, n - 1, ind, n - 1);
        st.update(0, 0, n - 1, ind, 1);
        //  cout<<st.seg[0]<<endl;
    }
    cout << ans << endl;
}