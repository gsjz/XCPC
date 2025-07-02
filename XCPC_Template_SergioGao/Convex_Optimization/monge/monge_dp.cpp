#include<bits/stdc++.h>  
using namespace std; 
const int N = 1e6 + 5;
int n, a[N], ans[N];
int ceilsq[N];
double f(int i, int j)
{
    return a[j] -a[i] + -sqrt(j-i);
}
void work()
{
    deque<pair<int, pair<int, int> > > q;
    for(int i=1; i<=n; i++)
    {
        if(!q.empty() && q.front().second.second < i ) q.pop_front();
        if(!q.empty() ) q.front().second.first = i;
        while( !q.empty() && 
            f(i, q.back().second.first) <= f(q.back().first, q.back().second.first) )
            q.pop_back();
        if(q.empty()) q.push_back({i, {i, n}});
        else if( f(i, n) < f(q.back().first, n)  )
        {
            int l = q.back().second.first, r = n, ans = n;
            while(l<=r)
            {
                int mid = (l+r)/2;
                if( f(i, mid) < f(q.back().first, mid) )
                {
                    ans = mid;
                    r = mid-1;
                }
                else l = mid+1;
            }
            q.back().second.second = ans-1;
            q.push_back({i, {ans, n}});
        }
        ans[i] = min(ans[i], (int)floor(f( q.front().first, i)) );
    }
    return;
}
void solve()
{
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i], ans[i] = 0;
    work();
    reverse(a+1, a+n+1);
    reverse(ans+1, ans+n+1);
    work();
    reverse(ans+1, ans+n+1);
    reverse(a+1, a+n+1);
    for(int i=1; i<=n; i++) cout<< (-ans[i]) <<"\n";
    return;
}
int main()
{  
    ios::sync_with_stdio(0);  
    cin.tie(0); 
    cout.tie(0);  
    int now = 0;
    for(int i=0; i<N; i++)
    {
        ceilsq[i] = now;
        if( now*now == i) now++;
    }
    int T = 1;  
    // cin>>T;  
    while(T--)
    {   
        solve();
    }
    return 0;  
} 