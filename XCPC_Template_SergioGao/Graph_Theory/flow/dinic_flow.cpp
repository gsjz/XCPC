#include<bits/stdc++.h>
using namespace std; 
template<class T> class Dinic
{
private:
    struct _Edge
    {
        int to;
        T cap;
    };
    int n;
    vector<_Edge> pool;
    vector<vector<int> > g;
    vector<int> cur, h;
    bool bfs(int s, int t)
    {
        for(auto &i : h) i = -1;
        h[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u = q.front(); q.pop();
            for(int i=0; i<(int)g[u].size(); i++)
            {
                auto _to = pool[g[u][i]].to;
                auto _cap = pool[g[u][i]].cap;
                if( _cap == 0 || h[_to] !=-1 ) continue;
                h[_to] = h[u] + 1;
                if(_to == t) return true;
                q.push(_to);
            }
        }
        
        return false;
    }
    T dfs(int u, int t, T f)
    {
        if(u==t) return f;
        auto r = f;
        for(auto &i = cur[u]; i<(int)g[u].size(); i++)
        {
            auto _to = pool[g[u][i]].to;
            auto _cap = pool[g[u][i]].cap;
            if(h[_to] != h[u] + 1) continue;
            auto a = dfs(_to, t, min(r, _cap));
            pool[g[u][i]] .cap -= a;
            pool[g[u][i]^1] .cap += a;
            r -= a;
            if(r==0) break;
        }
        return f-r;
    }
public:
    Dinic(int _n)
    {
        n = _n;
        cur.resize(n);
        h.resize(n);
        g.resize(n);
    }
    void addEdge(int u, int v, T c = numeric_limits<T>::max())
    {
        g[u].push_back(pool.size());
        pool.push_back({v, c});
        
        g[v].push_back(pool.size());
        pool.push_back({u, 0});
        
        return;
    }
    T flow(int s, int t)
    {
        T ans = 0;
        while(bfs(s, t))
        {
            for(auto &i : cur) i = 0;
            ans += dfs(s, t, numeric_limits<T>::max());
        }
        return ans;
    }
};
void solve()
{
    int n, m, k;
    cin>>n>>m>>k;
    vector<int> p(m), invid(m);
    vector<pair<int, int> > pp(m);
    for(int i=0; i<m; i++) cin>>p[i], pp[i] = {p[i], i};
    sort(pp.begin(), pp.end());
    sort(p.begin(), p.end());
    for(int i=0; i<m; i++) invid[pp[i].second] = i;
    vector<int> s[n];
    for(int i=0; i<n; i++)
    {
        s[i] = vector<int>(m);
        for(int j=0; j<m; j++)
        {
            cin>>s[i][invid[j]];
        }
    }
    Dinic<long long> d(n*m + 1 + 1);
    for(int i=0; i<n; i++)
    {
        d.addEdge(0, i*m+0+1, s[i][0]);
        for(int j=0; j<m-1; j++)
        {
            // i*m+j+1 [i,j]
            d.addEdge(i*m+j+1, i*m+ j+1 +1, s[i][j+1]);
        }
        d.addEdge(i*m+(m-1)+1, n*m+1);
    }
    for(int i=1; i<=k; i++)
    {
        int x, y, dis;
        cin>>x>>y>>dis;
        x--;
        y--;
        if(x==y) continue;
        for(int j=0, r=0; j<m; j++)
        {
            while(r<m && p[r] - p[j] <= dis) r++;
            if(r>=m) break;
            d.addEdge(x*m+ (r-1) +1, y*m+ j +1); 
            d.addEdge(y*m+ (r-1) +1, x*m+ j +1); 
        }
    }
    cout<<d.flow(0, n*m+1)<<"\n";
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        solve();
    }
	return 0;
}