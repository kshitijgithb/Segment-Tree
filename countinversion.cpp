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
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] +seg[2 * ind + 2];
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
        return left+right;
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
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
        return;
    }
};
int main()
{
    int t;
    cin>>t;
    while(t--){
  int n;
  cin>>n;
  int arr[n];
  int mx=-1;
  for(int i=0;i<n;i++)
  {
    cin>>arr[i];
    mx=max(mx,arr[i]);
  }
  int freq[mx+1]={0};
  for(int i=0;i<n;i++)
  {
    freq[arr[i]]++;
  }
  SGTree st(mx+1);
  st.build(0,0,mx,freq);
  int cnt=0;
  for(int i=0;i<n;i++)
  {
    freq[arr[i]]--;
    st.update(0,0,mx,arr[i],-1);
    cnt+=st.query(0,0,mx,1,arr[i]-1);
  }
  cout<<cnt<<endl;
    }
  }