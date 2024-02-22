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
class ST{
    vector<int>st,lazy;
    public:
    ST(int n)
    {
        st.resize(4*n);
        lazy.resize(4*n);
    }
    public:
    void build(int ind,int low,int high,int arr[])
    {
        if(low==high)
        {
            st[ind]=arr[low];
            return;
        }
        int mid=(low+high)>>1;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        st[ind]=st[2*ind+1]+st[2*ind+2];
    }
    void update(int ind,int low,int high,int l,int r,int val)
    {
        //update previous remaining updates and propagates downwards
        if(lazy[ind]!=0)
        {
            st[ind]+=(high-low+1)*lazy[ind];
            //propagate the lazy update downwards
            //for remaining nodes to get updated
            if(low!=high)
            {
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            lazy[ind]=0;
        }

            //no overlap
            if(high<l||r<low)return;

            //complete overlap
            if(low>=l&&high<=r)
            {
                st[ind]+=(high-low+1)*val;
                if(low!=high)
                {
                    lazy[2*ind+1]+=val;
                    lazy[2*ind+2]+=val;
                }
                return;
            }
            int mid=(low+high)>>1;
            update(2*ind+1,low,mid,l,r,val);
            update(2*ind+2,mid+1,high,l,r,val);
            st[ind]=st[2*ind+1]+st[2*ind+2];
        }
    int query(int ind,int low,int high,int l,int r)
    {
        //update if updates are remaining
            if (lazy[ind] != 0)
            {
                st[ind] += (high - low + 1) * lazy[ind];
                // propagate the lazy update downwards
                // for remaining nodes to get updated
                if (low != high)
                {
                    lazy[2 * ind + 1] += lazy[ind];
                    lazy[2 * ind + 2] += lazy[ind];
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
   int n;
   cin>>n;
   int arr[n];
   for(int i=0;i<n;i++)
   {
    cin>>arr[i];
   }
   ST st(n);
   st.build(0,0,n-1,arr);
   int q;
   cin>>q;
   while(q--)
   {
    int type;
    cin>>type;
    if(type==1)
    {
        int l,r;
        cin>>l>>r;
        cout<<st.query(0,0,n-1,l,r)<<endl;
    }
    else{
        int l,r,val;
        cin>>l>>r>>val;
        st.update(0,0,n-1,l,r,val);
    }
   }
}
