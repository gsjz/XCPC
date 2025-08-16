#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 5, SIZE = 2e5 + 5;

class AC
{
public:
    struct Node
    {
        int son[26];
        int ans, fail, dg, idx;
        Node()
        {
            memset(son, 0, sizeof(son));
            ans = fail = idx = 0;
        }
    } tr[SIZE];
    
    int tot, ans[N], pidx;
    AC()
    {
        tot = 0; pidx = 0;
    }
    void insert(string s, int &idx)
    {
        int u = 0;
        int len = s.size();
        for(int i=0; i<len; i++)
        {
            int &son = tr[u].son[s[i] - 'a'];
            if(!son) son = ++tot;
            u = son;
        }
        if(!tr[u].idx) tr[u].idx = ++pidx;
        idx = tr[u].idx;
    }
    void build()
    {
        queue<int> q;
        for(int i=0; i<26; i++)
        {
            if(tr[0].son[i]) q.push(tr[0].son[i]);
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int i=0; i<26; i++)
            {
                if(tr[u].son[i])
                {
                    tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                    tr[tr[tr[u].fail].son[i]].dg++;
                    q.push(tr[u].son[i]);
                }
                else
                {
                    tr[u].son[i] = tr[tr[u].fail].son[i];
                }
            }
        }
    }
    void query(string t)
    {
        int u = 0;
        int len = t.size();
        for(int i=0; i<len; i++)
        {
            u = tr[u].son[t[i] - 'a'];
            tr[u].ans++;
        }
    }
    void topu()
    {
        queue<int> q;
        for(int i=0; i<=tot; i++)
        {
            if(tr[i].dg == 0) q.push(i);
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            ans[tr[u].idx] = tr[u].ans;
            int v = tr[u].fail;
            tr[v].ans += tr[u].ans;
            if(!--tr[v].dg) q.push(v);
        }
    }
};

int n;
int idx[N];

void solve()
{
    AC acm;
    cin>>n;
    string s;
    for(int i=1; i<=n; i++)
    {
        cin>>s;
        acm.insert(s, idx[i]);
        acm.ans[i] = 0;
    }
    acm.build();
    cin>>s;
    acm.query(s);
    acm.topu();
    for(int i=1; i<=n; i++) cout<<acm.ans[idx[i]]<<"\n";

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T=1;
    // cin>>T;
    while(T--) solve();
    
    return 0;
}