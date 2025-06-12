#include<bits/stdc++.h>  
using namespace std;  
const int N = 1e5 + 5;
int fa[N];
int father(int x)
{
    if(fa[x] == x) return x;
    return fa[x] = father(fa[x]);
}
void merge(int x, int y)
{
    x = father(x);
    y = father(y);
    fa[x] = y;
}
vector< pair<pair<int, int>, pair<int, int> > > e;
int V, E, need, val;
bool check(int d)
{
    for(int i=1; i<=V; i++) fa[i] = i;
    vector< pair<pair<int, int>, pair<int, int> > > tmpe = e;
    for(int i=1; i<=E; i++) if(tmpe[i].first.second == 0) tmpe[i].first.first += d;
    sort(tmpe.begin()+1, tmpe.end());
    int cnt = 0;
    val = 0;
    for(int i=1; i<=E; i++)
    {
        int s = tmpe[i].second.first,
            t = tmpe[i].second.second,
            c = tmpe[i].first.first,
            col = tmpe[i].first.second;
        if(father(s) == father(t)) continue;
        if(col==0) cnt++;
        val += c;
        merge(s, t);
    }
    return cnt >= need;
}
void solve()
{
    cin>>V>>E>>need;
    e = vector< pair<pair<int, int>, pair<int, int> > >(E+1);
    for(int i=1; i<=E; i++)
    {
        cin>>e[i].second.first>>e[i].second.second>>e[i].first.first>>e[i].first.second;
        e[i].second.first++;
        e[i].second.second++;
    }
    int l = -100, r = 100, ans = 666;
    while(l<=r)
    {
        int mid = (l+r)/2;
        if(check(mid))
        {
            ans = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    check(ans);
    cout<< val - need*ans <<"\n";
    return;
}
int main()
{  
    ios::sync_with_stdio(0);  
    cin.tie(0); 
    cout.tie(0);  
    int T = 1;  
    // cin>>T;  
    while(T--)
    {   
        solve();
    }
    return 0;  
} 