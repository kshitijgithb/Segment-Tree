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
const int N=5*1e5+10;
int bit[N];
void update(int i,int x)
{
   for(;i<N;i+=(i&(-i)))
   {
      bit[i]+=x;
   }
}
int query(int i)
{
    int ans=0;
    for(;i>0;i-=(i&(-i)))
    {
        ans+=bit[i];
    }
    return ans;
}
int main()
{
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = " " + s;
    for (int i = 1; i <=n - 1; i++)
    {
        if (s[i] != s[i + 1])
        {
            update(i,1);
        }
        cout<<bit[i]<<endl;
    }
       cout <<query(n-1) << endl;
    while (q--)
    {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1)
        {
            if (l - 1 >= 1)
            {
                if(query(l-1)-query(l-2))
                update(l-1,-1);
                else update(l - 1, 1);
            }
            if (r <= n - 1)
            {
                if(query(r)-query(r-1))
                update(r,-1);
                else update(r,1);
            }
        }
        else
        {
            // cout<<sg.query(0,0,n-2,l,r-1)<<endl;
            if (query(r-1)-query(l) == r - l)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
}
