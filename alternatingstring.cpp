#include<bits/stdc++.h>
using namespace std;
#define ll long long
 #define pb          push_back
#define lli        long long int
#define dv          vector <ll> 
#define no()        cout << "NO" << endl
#define yes()       cout << "YES" <<endl
#define all(v)      v.begin(), v.end()
#define f(i, n)     for( lli i = 0; i < n; i ++ )
#define f1(i, n)    for( lli i = 1; i <= n; i ++ )
#define fast        ios_base :: sync_with_stdio( false ); cin.tie( NULL );
#define display(v)  for(auto it : v) cout << it <<" "; cout<<endl
vector<int>seg;
class SGTree
{
public:
    SGTree(int n)
    {
        seg.resize(4 * n,0);
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
        return (left+right);
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
        seg[ind] = (seg[2 * ind + 1]+seg[2 * ind + 2]);
        return;
    }
};
int main()
{
  int n,q;
  cin>>n>>q;
  string s;
  cin>>s;
  SGTree sg(n);
  for(int i=0;i<n-1;i++)
  {
    if(s[i]!=s[i+1])
    {
        sg.update(0,0,n-2,i,1);
    }
  }
//   cout << sg.query(0, 0, n - 2, 0, n-2) << endl;
  while(q--)
  {
    int type,l,r;
    cin>>type>>l>>r;
    l--,r--;
    if(type==1)
    {
       if(l-1>=0)
       {
           int val = sg.query(0,0,n-2,l - 1, l - 1);
           sg.update(0,0,n-2,l - 1, val ^ 1);
       }
       if(r<=n-2)
       {
           int val = sg.query(0, 0, n - 2, r, r);
           sg.update(0, 0, n - 2, r, val ^ 1);
       }
    }
    else
    {
        // cout<<sg.query(0,0,n-2,l,r-1)<<endl;
       if(sg.query(0,0,n-2,l,r-1)==r-l)
       {
        cout<<"Yes"<<endl;
       }
       else
       {
        cout<<"No"<<endl;
       }
    }
  }
}
