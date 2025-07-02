#include<bits/stdc++.h>  
using namespace std; 
class TarjanSCC
{
private:
    int n;
    vector<vector<int> > e;
    vector<int> dfn, low;
    int dfncnt;
    stack<int> st;
    vector<bool> instack;
    void dfs(int u)
    {
        if(dfn[u]) return;
        low[u] = dfn[u] = ++dfncnt;
        st.push(u);
        instack[u] = 1;
        for(auto v: e[u])
        {
            if(!dfn[v])
            {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if(instack[v])
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u])
        {
            ++sc;
            while(!st.empty() && st.top()!=u)
            {
                scc[st.top()] = sc;

                instack[st.top()] = 0;
                st.pop();
            } 
            assert(!st.empty() && st.top() == u);
            scc[st.top()] = sc;
            instack[st.top()] = 0;
            st.pop();
        }
        return;
    }
    int sc;
public:
    vector<int> scc;
    TarjanSCC(int _n)
    {
        n = _n;
        e = vector<vector<int> >(n);
        dfn = vector<int>(n);
        low = vector<int>(n);
        st = stack<int>();
        instack = vector<bool>(n);
        scc = vector<int>(n);
        dfncnt = sc = 0;
    }
    void addEdge(int u, int v)
    {
        assert(u<n && v<n);
        e[u].push_back(v);
        return;
    } // point id should strictly less than n
    void get()
    {
        for(int i=0; i<n; i++) dfs(i);
        return;
    }
};
void solve()
{
    int n, m;
    cin>>n>>m;
    TarjanSCC _graph(n+1);
    for(int i=1; i<=m; i++)
    {
        int u, v;
        cin>>u>>v;
        _graph.addEdge(u, v);
    }
    _graph.get();
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