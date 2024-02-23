#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = 998244353;

const int N = (5 * 1e5) + 10;
ll t[N];

void update(ll i, ll x)
{
    for (; i < N; i += (i & -i))
        t[i] += x;
}

ll query(ll i)
{
    ll ans = 0;
    for (; i > 0; i -= (i & -i))
        ans += t[i];
    return ans;
}

int main()
{
    ll n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = " " + s;
    for (int i = 2; i <= n; i++)
    {
        if (s[i] == s[i - 1])
            update(i - 1, 1);
    }
    while (q--)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
        {

            if (l > 1)
            {
                if (query(l - 1) - query(l - 2))
                    update(l - 1, -1);
                else
                    update(l - 1, 1);
            }
            if (r < n)
            {
                if (query(r) - query(r - 1))
                    update(r, -1);
                else
                    update(r, 1);
            }
        }
        else
        {
            if (query(r - 1) - query(l - 1))
                cout << "No\n";
            else
                cout << "Yes\n";
        }
    }
}
