#include <bits/stdc++.h>
using namespace std;
void update(int l, int r, int ind, int s, int e, vector<int> &stree, vector<int> &lazy)
{
    if (l > r)
        return;
    if (lazy[ind] != 0)
    {
        stree[ind] = (r - l + 1) - stree[ind];
        if (l != r)
        {
            lazy[2 * ind + 1] = (lazy[2 * ind + 1] + 1) % 2;
            lazy[2 * ind + 2] = (lazy[2 * ind + 2] + 1) % 2;
        }
        lazy[ind] = 0;
    }
    if ((e < l) || (r < s))
        return;
    if ((s <= l) && (r <= e))
    {
        stree[ind] = (r - l + 1) - stree[ind];
        if (l != r)
        {
            lazy[2 * ind + 1] = (lazy[2 * ind + 1] + 1) % 2;
            lazy[2 * ind + 2] = (lazy[2 * ind + 2] + 1) % 2;
        }
        return;
    }
    int m = (l + r) / 2;
    update(l, m, 2 * ind + 1, s, e, stree, lazy);
    update(m + 1, r, 2 * ind + 2, s, e, stree, lazy);
    stree[ind] = (stree[2 * ind + 1] + stree[2 * ind + 2]);
}
int query(int l, int r, int ind, int s, int e, vector<int> &stree, vector<int> &lazy)
{
    if (l > r)
        return (0);
    if (lazy[ind] != 0)
    {
        stree[ind] = (r - l + 1) - stree[ind];
        if (l != r)
        {
            lazy[2 * ind + 1] = (lazy[2 * ind + 1] + 1) % 2;
            lazy[2 * ind + 2] = (lazy[2 * ind + 2] + 1) % 2;
        }
        lazy[ind] = 0;
    }
    if ((e < l) || (r < s))
        return (0);
    if ((s <= l) && (r <= e))
        return (stree[ind]);
    int m = (l + r) / 2;
    int res = 0;
    res = res + query(l, m, 2 * ind + 1, s, e, stree, lazy);
    res = res + query(m + 1, r, 2 * ind + 2, s, e, stree, lazy);
    stree[ind] = (stree[2 * ind + 1] + stree[2 * ind + 2]);
    return (res);
}
int main()
{
    int n, q, i, type, a, b;
    cin >> n >> q;
    vector<int> stree(4 * n + 4, 0);
    vector<int> lazy(4 * n + 4, 0);
    for (i = 0; i < q; i++)
    {
        cin >> type >> a >> b;
        if (type == 0)
            update(0, n - 1, 0, a, b, stree, lazy);
        else
            cout << query(0, n - 1, 0, a, b, stree, lazy) << endl;
    }
    return 0;
}