#include<bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;

int n, a[N], b, k_1, k_2;

long long dp(long long lbd1, long long lbd2)
{
    long long res = 0;
    for(int i=1; i<=n; i++)
    {
        long long nw = res + a[i];
        nw = min(nw, res + (a[i]+1)/2 - lbd1);
        nw = min(nw, res + max(a[i]-b, 0) - lbd2);
        nw = min(nw, res + min( (max(a[i]-b, 0)+1)/2, max((a[i]+1)/2-b, 0) ) - lbd1 - lbd2);
        res = nw;
    }
    return res + lbd1 * k_1 + lbd2 * k_2;
}

long long check(long long lbd1)
{
    long long l = -2e9, r = 0, ans = -1e18;
    while(l<=r)
    {
        long long mid = (l+r)/2;
        long long res = dp(lbd1, mid), _res = dp(lbd1, mid+1);
        ans = max(ans, max(res, _res));
        if(res <= _res) l = mid+2;
        else r = mid-1;
    }
    return ans;
}

void solve()
{
    cin>>n>>b>>k_1>>k_2;
    for(int i=1; i<=n; i++) cin>>a[i];
    
    long long l = -2e9, r = 0, ans = -1e18;
    while(l<=r)
    {
        long long mid = (l+r)/2;
        long long res = check(mid), _res = check(mid+1);
        ans = max(ans, max(res, _res));
        if(res <= _res) l = mid+2;
        else r = mid-1;
    }
    cout<<ans<<"\n";

    return;
}
/*


*/
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