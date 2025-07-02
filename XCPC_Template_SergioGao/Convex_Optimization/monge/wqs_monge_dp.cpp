#include<bits/stdc++.h>  
using namespace std; 
const int N = 2e5 + 5;
int n, m;
int a[N];
long double pre[N];
int cnt[N];
long double dp[N];
long double w(int i, int j, long double lamb)
{
    return dp[i-1] + sqrtl( ( pre[j] - pre[i-1] )*(j-i+1) ) + lamb;
}
bool check(long double lamb)
{
    deque<pair<int, pair<int, int> > > q;
    dp[0] = 0;
    cnt[0] = 0;
    for(int i=1; i<=n; i++)
    {
        if(!q.empty() && q.front().second.second < i) q.pop_front();
        if(!q.empty() && q.front().second.first < i) q.front().second.first = i;
        while(!q.empty() && 
            w(i, q.back().second.first, lamb)    
            <= w(q.back().first, q.back().second.first, lamb) ) q.pop_back();
        if(q.empty()) q.push_back({i, {i, n}});
        else if( w(i, n, lamb) < w(q.back().first, n, lamb) )
        {
            int l = q.back().second.first, r = n, ans = n;
            while(l<=r)
            {
                int mid = (l+r)/2;
                if( w(i, mid, lamb) < w(q.back().first, mid, lamb) )
                {
                    ans = mid;
                    r = mid-1;
                }
                else l = mid+1;
            }
            q.back().second.second = ans-1;
            q.push_back({i, {ans, n}});
        }
        dp[i] = w(q.front().first, i, lamb);
        cnt[i] = cnt[q.front().first-1] +1;
    }
    return cnt[n] <= m;
}
void solve()
{
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin>>a[i];
    sort(a+1, a+n+1);
    for(int i=1; i<=n; i++) pre[i] = pre[i-1] + a[i];
 
    long double l = 0, r = 1e14;
    for(int itr = 0; itr < 200; itr++)
    {
        long double mid = (l+r)/2;
        if( check(mid) )
        {
            r = mid;
        }
        else l = mid;
    }
    check(r);
    cout<<dp[n]-m*r<<"\n";
    return;
}
int main()
{  
    ios::sync_with_stdio(0);  
    cin.tie(0); 
    cout.tie(0);     
    cout<<fixed<<setprecision(15);
    int T = 1;  
    // cin>>T;  
    while(T--)
    {   
        solve();
    }
    return 0;  
} 