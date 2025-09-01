#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 1e5 + 5;

int n, k, a[N];

struct VAL
{
    int lnow, rnow;
    int cnt[N];
    ll ans;
    VAL()
    {
        lnow = 1, rnow = 0;
        ans = 0;
        memset(cnt, 0, sizeof 0);
    }
    ll work(int l, int r)
    {
        while(l < lnow)
        {
            lnow--;
            ans += cnt[a[lnow]];
            cnt[a[lnow]]++;
        }
        while(l > lnow)
        {
            cnt[a[lnow]]--;
            ans -= cnt[a[lnow]];
            lnow++;
        }
        while(rnow < r)
        {
            rnow++;
            ans += cnt[a[rnow]];
            cnt[a[rnow]]++;
        }
        while(rnow > r)
        {
            cnt[a[rnow]]--;
            ans -= cnt[a[rnow]];
            rnow--;
        }
        return ans;
    }
} val;

ll dp[N], nwdp[N];
int cnt[N];
void divide_solve(int l, int r, int pl, int pr)
{
    if(l>r) return;
    int mid = (l+r)/2;

    int pmid = pl;
    ll tmpmid = val.work(pl, mid);
    for(int i=pl; i<=min(mid, pr); i++)
    {
        if( dp[i-1] + val.work(i, mid) < dp[pmid-1] + tmpmid)
        {
            pmid = i;
            tmpmid = val.work(i, mid);
        }
    }
    nwdp[mid] = dp[pmid-1] + tmpmid;

    divide_solve(l, mid-1, pl, pmid);
    divide_solve(mid+1, r, pmid, pr);
    return;
}
void solve()
{
    cin >> n >> k;
    for(int i=1; i<=n; i++) cin >> a[i];

    for(int i=1; i<=n; i++)
    {
        dp[i] = dp[i-1] + cnt[a[i]];
        cnt[a[i]] ++;
    }
    // for(int i=1; i<=n; i++) cout << dp[i] << " ";
    // cout << "\n";


    k--;
    while(k--)
    {
        divide_solve(1, n, 1, n);
        for(int i=1; i<=n; i++) dp[i] = nwdp[i];
    }
    
    cout << dp[n] << "\n";

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    // freopen("1.in", "r", stdin);

    int T=1;
    // cin>>T;
    while(T--) solve();
    
    return 0;
}