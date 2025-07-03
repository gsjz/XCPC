#include<bits/stdc++.h>
using namespace std;
using ll = long long;
class LiChaoTree // get min on [0, 1e9]
{
private:
    class line
    {
    public:
        ll k, b;
        line(ll kk = 0, ll bb = 0) { k = kk, b = bb; }
        ll get(ll x) { return x * k + b; }
    };
    static const int inf = 1e9;
    static vector<pair<int, int> > ch;
    static vector<line> seg; 
    static int tot;

    ll inter(line aa, line bb)
    {
        return (bb.b - aa.b) / (aa.k - bb.k);
    } // we only need the integer part, and (aa.k - bb.k) won't be 0 when we use it
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
};
const int N = 2e5 + 5; 
vector<pair<int, int> > LiChaoTree::ch = vector<pair<int, int> >(N);
vector<LiChaoTree::line> LiChaoTree::seg = vector<line>(N);
int LiChaoTree::tot = 0;

ll B[N], C[N];
void solve()
{
    int n, m;
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin >> B[i];
    sort(B+1, B+n+1);
    LiChaoTree lc;
    for(int i=1; i<=n; i++) lc.add({ - (n+1-i), - B[i] * (n+1-i) }); // use - to solve max
    for(int i=1; i<=m; i++)
    {
        cin >> C[i];
        cout<< -lc.qry(C[i]) << " ";
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    while(T--) solve();
    return 0;
}