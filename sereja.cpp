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
class info
{
public:
    int open, close, full;
    info()
    {
        open = 0;
        close = 0;
        full = 0;
    }
    info(int open, int close, int full)
    {
        this->open = open;
        this->close = close;
        this->full = full;
    }
};
info merge(info a, info b)
{
    info ans(0,0,0);
    ans.full = a.full+b.full+min(a.open, b.close);
    ans.open = a.open + b.open - min(a.open, b.close);
    ans.close = a.close + b.close - min(a.open, b.close);
    return ans;
}
class SGTree
{
    public:
    vector<info> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, string &arr)
    {
        if (low == high)
        {
            seg[ind] = info(arr[low] == '(', arr[low] == ')', 0);
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    info query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (r < low || high < l)
            return info();

        // complete overlap
        if (l <= low && r >= high)
            return seg[ind];

        // partial overlap
        int mid = (low + high) >> 1;
        info left = query(2 * ind + 1, low, mid, l, r);
        info right = query(2 * ind + 2, mid + 1, high, l, r);
        return merge(left, right);
    }
};
int main()
{
  string s;
  cin>>s;
  int n=s.size();
  SGTree sg(n);
  sg.build(0,0,n-1,s);
  int q;
  cin>>q;
  while(q--)
  {
    int l,r;
    cin>>l>>r;
    l--,r--;
    info ans=sg.query(0,0,n-1,l,r);
    cout<<ans.full*2<<endl;
  }
}
