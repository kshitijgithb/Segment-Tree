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
#define display(v)  for(auto it : v) cout << it <<" "; cout<<endl;
class SGTree
{
    public:
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, int arr[],int orr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr,!orr);
        build(2 * ind + 2, mid + 1, high, arr,!orr);
        if(orr==1)
        seg[ind] = (seg[2 * ind + 1]|seg[2 * ind + 2]);
        else
        seg[ind] = (seg[2 * ind + 1]^seg[2 * ind + 2]);
    }
    void update(int ind, int low, int high, int i, int val,int orr)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
        {
            update(2 * ind + 1, low, mid, i, val,!orr);
        }
        else
        {
            update(2 * ind + 2, mid + 1, high, i, val,!orr);
        }
        if (orr == 1)
            seg[ind] = (seg[2 * ind + 1] | seg[2 * ind + 2]);
        else
            seg[ind] = (seg[2 * ind + 1] ^ seg[2 * ind + 2]);
    }
};
int main()
{
  int n,m;
  cin>>n>>m;
  int el=1<<n;
  int arr[el];
  for(int i=0;i<el;i++)
  {
    cin>>arr[i];
  }
  SGTree sg(el);
 if(n&1) sg.build(0,0,el-1,arr,1);
 else sg.build(0,0,el-1,arr,0);
 while(m--)
 {
    int i,val;
    cin>>i>>val;
    i--;
    if(n&1)
    sg.update(0,0,el-1,i,val,1);
    else
    sg.update(0, 0, el- 1, i, val, 0);
    arr[i]=val;
    cout<<sg.seg[0]<<endl;
 }
}
