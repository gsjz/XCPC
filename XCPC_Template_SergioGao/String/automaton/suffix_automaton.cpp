#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int SIZ = 5e5 + 5;

class SAM
{
private:
    ll distinct_count_linktree()
    {
        ll ans = 0;
        for(int i=2; i<=tot; i++)
        {
            ans += tr[i].len - tr[tr[i].fa].len;
        }
        return ans;
    }
    ll distinct_count_dag()
    {
        vector<int> dg( tot + 1 );
        vector<ll> dp( tot + 1 );
        vector<vector<int> > e(tot + 1);
        for(int i=1; i<=tot; i++)
        {
            for(int j=0; j<26; j++)
            {                
                if(tr[i].son[j])
                {
                    dg[i]++;
                    e[tr[i].son[j]].push_back(i);
                }
            }
        }

        queue<int> q;
        for(int i=1; i<=tot; i++)
        {
            if(dg[i] == 0)
            {
                q.push(i);
            }
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(auto v : e[u])
            {
                dp[v] += dp[u]+1;
                if((--dg[v])==0)
                {
                    q.push(v);
                }
            }
        }
 
        return dp[1];
    }

public:
    struct Node
    {
        int son[26];
        int len, fa;
        Node()
        {
            len = fa = 0;
            memset(son, 0, sizeof son);
        }
    } tr[SIZ*2];

    int tot, lst;
    void add(int c)
    {
        int p = lst;
        int np = lst = ++tot;
        tr[np].len = tr[p].len + 1;
        mx_len = max(mx_len, tr[np].len);
        occ[np] = 1;

        while(p && tr[p].son[c] == 0)
        {
            tr[p].son[c] = np;
            p = tr[p].fa;
        }
        if(p==0) tr[np].fa = 1;
        else
        {
            int q = tr[p].son[c];
            if(tr[q].len == tr[p].len + 1) tr[np].fa = q;
            else
            {
                int nq = ++tot;
                tr[nq] = tr[q];
                tr[nq].len = tr[p].len + 1;

                mx_len = max(mx_len, tr[nq].len);
                occ[nq] = 0;

                tr[q].fa = tr[np].fa = nq;
                while(p && tr[p].son[c] == q)
                {
                    tr[p].son[c] = nq;
                    p = tr[p].fa;
                }
            }
        }
    }
    
    int mx_len;
    int occ[SIZ * 2]; // size of endpos
    int ord[SIZ * 2];
    void build_endpos()
    {
        vector<int> bucket(mx_len+1, 0);
        for(int i=1; i<=tot; i++) bucket[tr[i].len] ++;
        for(int i=1; i<=mx_len; i++) bucket[i] += bucket[i-1];

        for(int i=1; i<=tot; i++) ord[ bucket[tr[i].len] -- ] = i;

        for(int i=tot; i>=2; i--)
        {
            int v = ord[i];
            occ[tr[v].fa] += occ[v];
        }
    }
    
    void work()
    {
        build_endpos();
        
        /*
        todo
        */
    }

    SAM()
    {
        tot = lst = 1;
        mx_len = 0;
        memset(occ, 0, sizeof occ);
    }
};

int n;
void solve()
{
    string s;
    cin>>s;
    n = s.size();
    SAM sam;
    for(int i=1; i<=n; i++)
    {
        sam.add( s[i-1] - 'a' );
    }
    sam.work();
    
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    // freopen("2.in", "r", stdin);
    int T=1;
    // cin>>T;
    while(T--) solve();
    return 0;
}
/*
*/