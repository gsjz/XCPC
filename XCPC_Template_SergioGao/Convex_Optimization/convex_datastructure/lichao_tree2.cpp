#include<bits/stdc++.h>
using namespace std;

using ll = long long;
class LiChaoTree // get min on [0, 1e9]
{
private:
    static const int inf = 1e9, M = 2e5;
    class line
    {
    public:
        ll k, b;
        line(ll kk = 0, ll bb = 0) { k = kk, b = bb; }
        ll get(ll x) { return x * k + b; }
    };
    ll inter(line aa, line bb)
    {
        return (bb.b - aa.b) / (aa.k - bb.k);
    } // we only need the integer part, and (aa.k - bb.k) won't be 0 when we use it
    vector<pair<int, int> > ch;
    vector<line> seg; 
    // only 1 new node for 1 add operation, so the memory is N instead of N log V
    int tot = 0;  // avoid using .size() then .push_back(), because here we are using & for a vector object
    // when .push_back(), the still using & for the object may be invalid
    void _add(int &id, int L, int R, line now)
    {
        if(!id) return id = ++tot, seg[id] = now, void();
        int mid = (L+R) >> 1;
        ll La = seg[id].get(L), Ra = seg[id].get(R), Lb = now.get(L), Rb = now.get(R);
        if(La <= Lb && Ra <= Rb) return;
        if(La >= Lb && Ra >= Rb) return seg[id] = now, void();
        ll it = inter(seg[id], now);
        if(La <= Lb)
        {
            if(it<=mid) _add(ch[id].first, L, mid, seg[id]), seg[id] = now;
            else _add(ch[id].second, mid + 1, R, now);
        }
        else
        {
            if(it <= mid) _add(ch[id].first, L, mid, now);
            else _add(ch[id].second, mid + 1, R, seg[id]), seg[id] = now;
        }
    }
    ll _qry(int id, int L, int R, int x)
    {
        if(!id) return (ll)inf*inf;
        int mid = (L+R) >> 1;
        if(x <= mid) return min(seg[id].get(x), _qry(ch[id].first, L, mid, x));
        else return min(seg[id].get(x), _qry(ch[id].second, mid + 1, R, x));
    }
public:
    int rt = 0;
    void add(line now) { return _add(rt, 0, inf, now), void(); }
    ll qry(int x) { return _qry(rt, 0, inf, x); }
    LiChaoTree(int _M = M) { seg = vector<line>(_M+5); ch = vector<pair<int, int> >(_M+5); }
};
const int N = 1e6 + 5;
int n;
long long a[N], dp[N], best_k_for_fixed_j[N];
void solve()
{
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    LiChaoTree lc_for_k(n), lc_for_dp(n);
    for(int i=1; i<=n; i++)
    {
        // for(int k=0; k<i; k++)
        // {
        //     if(k==0) best_k_for_fixed_j[i] = - a[i] * k - k + dp[k];
        //     else best_k_for_fixed_j[i] = min(best_k_for_fixed_j[i], - a[i] * k - k + dp[k]);
        // }
        lc_for_k.add({-(i-1), -(i-1) + dp[i-1]});
        best_k_for_fixed_j[i] = lc_for_k.qry(a[i]);
        // dp[i] = dp[i-1] + a[i];
        // for(int j = 1; j<=i; j++) dp[i] = min(dp[i], (i-j) + a[j]*i + (i-1) + best_k_for_fixed_j[j] );
        lc_for_dp.add({ 1+a[i]+1, -i-1+best_k_for_fixed_j[i] });
        dp[i] = lc_for_dp.qry(i);
        cout<<dp[i]<<" ";
    }
    cout<<"\n";
    // cout<<dp[n]<<"\n";
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    cin>>T;
    while(T--) solve();
    return 0;
}
/*

*/