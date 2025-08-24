#include<bits/stdc++.h>  
using namespace std;  
template<class T> class mcmf
{
private:
    const T INF = numeric_limits<T>::max();
    struct _edge
    {
        int to, cap;
        T cost;
    };
    int n;
    vector<_edge> e;
    vector<vector<int> > g;
    int src, sink;
    vector<T> h;
    vector<T> dis;
    vector<pair<int, int> > prev;
    bool Dij()
    {
        dis = vector<T>(n, INF);
        dis[src] = 0;
        priority_queue<pair<T, int> > q;
        q.push({-dis[src], src});
        while(!q.empty())
        {
            auto frt = q.top();
            q.pop();
            if(frt.first != -dis[frt.second]) continue;
            int u = frt.second;
            for(int i=0; i<(int)g[u].size(); i++)
            {
                auto edge = e[g[u][i]];
                if(edge.cap > 0 && dis[edge.to] > dis[u] + h[u] + edge.cost - h[edge.to])
                {
                    dis[edge.to] = dis[u] + h[u] + edge.cost - h[edge.to];
                    prev[edge.to] = {u, g[u][i]};
                    q.push({-dis[edge.to], edge.to});
                }
            }
        }
        return dis[sink] < INF;
    }
    void spfa()
    {
        queue<int> q;
        vector<int> vis(n, 0);
        h[src] = 0;
        vis[src] = 1;
        q.push(src);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for(int i=0; i<(int)g[u].size(); i++)
            {
                auto edge = e[g[u][i]];
                if( edge.cap > 0 && h[edge.to] > h[u] + edge.cost)
                {
                    h[edge.to] = h[u] + edge.cost;
                    if( !vis[edge.to] )
                    {
                        vis[edge.to] = 1;
                        q.push(edge.to);
                    }
                }
            }
        }
        return;
    }
public:
    mcmf(int _n, int _src, int _sink)
    {
        n = _n;
        src = _src;
        sink = _sink;
        g = vector<vector<int> >(n);
        return;
    }
    void addEdge(int u, int v, int f, T c)
    {
        g[u].push_back( e.size() );
        e.push_back({v, f, c});
        g[v].push_back( e.size() );
        e.push_back({u, 0, -c});
        return;
    }
    pair<int, T> get()
    {
        prev = vector<pair<int, int> >(n);
        int maxf = 0;
        T minc = 0;
        h = vector<T>(n, INF);
        spfa();
        while( Dij() )
        {
            int flow = numeric_limits<int>::max();
            for(int i=0; i<n; i++) if(dis[i] < INF) h[i] += dis[i];
            for(int v = sink; v != src; v = prev[v].first )
            {
                flow = min(flow, e[prev[v].second].cap);
            }
            for(int v = sink; v != src; v = prev[v].first )
            {
                e[prev[v].second].cap -= flow;
                e[prev[v].second^1].cap += flow;
            }
            maxf += flow;
            minc += h[sink] * flow;
        }
        return {maxf, minc};
    }
};
void solve()
{
    int n, m, s, t;
    cin>>n>>m>>s>>t;
    s--; t--;
    auto _graph = mcmf<int>(n, s, t);
    while(m--)
    {
        int u, v, w, c;
        cin>>u>>v>>w>>c;
        u--; 
        v--;
        _graph.addEdge(u, v, w, c);
    }
    auto ans = _graph.get();
    cout<<ans.first << " " << ans.second<<"\n";
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