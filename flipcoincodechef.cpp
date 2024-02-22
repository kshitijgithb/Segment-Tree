#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class ST
{
    vector<int> st, lazy;

public:
    ST(int n)
    {
        st.resize(4 * n);
        lazy.resize(4 * n, 0);
    }

public:
    void build(int ind, int low, int high)
    {
        if (low == high)
        {
            st[ind] = 0;
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid);
        build(2 * ind + 2, mid + 1, high);
        st[ind] = st[2 * ind + 1] + st[2 * ind + 2];
    }
    void update(int ind, int low, int high, int l, int r)
    {
        // update previous remaining updates and propagates downwards
        if (lazy[ind] != 0)
        {
            st[ind] += (high - low + 1) - st[ind];
            // propagate the lazy update downwards
            // for remaining nodes to get updated
            if (low != high)
            {
                lazy[2 * ind + 1] = !lazy[2 * ind + 1];
                lazy[2 * ind + 2] = !lazy[2 * ind + 2];
            }
            lazy[ind] = 0;
        }

        // no overlap
        if (high < l || r < low)
            return;

        // complete overlap
        if (low >= l && high <= r)
        {
            st[ind] = (high - low + 1) - st[ind];
            if (low != high)
            {
                lazy[2 * ind + 1] = 1;
                lazy[2 * ind + 2] = 1;
            }
            return;
        }
        int mid = (low + high) >> 1;
        update(2 * ind + 1, low, mid, l, r);
        update(2 * ind + 2, mid + 1, high, l, r);
        st[ind] = st[2 * ind + 1] + st[2 * ind + 2];
    }
    int query(int ind, int low, int high, int l, int r)
    {
        // update if updates are remaining
        if (lazy[ind] != 0)
        {
            st[ind] += (high - low + 1) - st[ind];
            // propagate the lazy update downwards
            // for remaining nodes to get updated
            if (low != high)
            {
                lazy[2 * ind + 1] = !lazy[2 * ind + 1];
                lazy[2 * ind + 2] = !lazy[2 * ind + 2];
            }
            lazy[ind] = 0;
        }
        if (high < l || r < low)
            return 0;
        if (low >= l && high <= r)
            return st[ind];
        int mid = (low + high) >> 1;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return left + right;
    }
};
int main()
{
    // your code goes here
    int n, m;
    cin >> n >> m;
    ST st(n);
    st.build(0, 0, n - 1);
    while (m--)
    {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 0)
        {
            st.update(0, 0, n - 1, l, r);
        }
        else
        {
            cout << st.query(0, 0, n - 1, l, r) << endl;
        }
    }
    return 0;
}
