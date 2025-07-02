#include<bits/stdc++.h>
using namespace std;

class LiChaoTree
{
private:
    const double eps = 1e-9;
    int cmp(double x, double y)
    {
        if(x - y > eps) return 1;
        if(y - x > eps) return -1;
        return 0;
    }
    int RANGE;
    struct Line
    {
        double k, b;
    };
    vector<Line> line;
    vector<int> lazytag;
    double calc(int id, int x)
    {
        return line[id].b + line[id].k * x;
    }
    void upd(int root, int cl, int cr, int u)
    {
        int &v = lazytag[root];
        if(v == -1)
        {
            v = u;
            return;
        }
        int mid = (cl + cr) >> 1;
        int bmid = cmp(calc(u, mid), calc(v, mid));
        if( bmid == 1 || (!bmid && u < v) ) swap(u, v);
        int bl = cmp(calc(u, cl), calc(v, cl));
        if(bl == 1 || (bl==0 && u < v)) upd(root<<1, cl, mid, u);
        int br = cmp(calc(u, cr), calc(v, cr));
        if(br == 1 || (br==0 && u < v)) upd(root<<1|1, mid+1, cr, u);
        return;
    }
    void update(int root, int cl, int cr, int l, int r, int u)
    {
        if(l <= cl && cr <= r)
        {
            upd(root, cl, cr, u);
            return;
        }
        int mid = (cl + cr)>>1;
        if( l <= mid) update(root<<1, cl, mid, l, r, u);
        if( mid+1 <= r) update(root<<1|1, mid+1, cr, l, r, u);
        return;
    }
    using pdi = pair<double, int>;
    pdi pmax(pdi x, pdi y)
    {
        if( cmp(x.first, y.first) == 1 ) return x;
        if( cmp(x.first, y.first) == -1 ) return y;
        return x.second < y.second ? x : y;
    }
public:
    LiChaoTree(int _RANGE)
    {
        RANGE = _RANGE;
        lazytag = vector<int>(RANGE * 4 + 5, -1);
        return;
    }
    pdi query(int root, int l, int r, int x)
    {
        if(r < x || x < l) return {0, 0}; // {-inf, id}
        int mid = (l+r)>>1;
        pdi res = {0, 0};
        if(lazytag[root] != -1) res = {calc(lazytag[root], x), lazytag[root]};
        if( l==r ) return res;
        return pmax(res, pmax(query(root<<1, l, mid, x), query(root<<1|1, mid+1, r, x)) ); 
    }
    void add(int x_0, int y_0, int x_1, int y_1)
    {
        Line tmp;
        if(x_0 == x_1) tmp.k = 0, tmp.b = max(y_0, y_1); // only serve this problem
        else tmp.k = 1.0 * (y_1 - y_0) / (x_1 - x_0), tmp.b = y_0 - tmp.k * x_0;
        int id = line.size();
        line.push_back(tmp);
        update(1, 1, RANGE, x_0, x_1, id);
        return;
    }
};
// only serve the problem https://www.luogu.com.cn/problem/P4097
const int MOD1 = 39989; // also serve as the range of x
const int MOD2 = 1000'000'000;
void solve()
{
    LiChaoTree lichao(MOD1);

    int q;
    cin>>q;
    lichao.add(1, 0, MOD1, 0); // only serve this problem
    for(int lastans = 0; q--; )
    {
        int op;
        cin>>op;
        if(op==0)
        {
            int x;
            cin>>x;
            x = (x + lastans -1 + MOD1) % MOD1 + 1;
            cout<< (lastans = lichao.query(1, 1, MOD1, x).second) << "\n";
        }
        else if(op==1)
        {
            int x_0, y_0, x_1, y_1;
            cin>>x_0>>y_0>>x_1>>y_1;
            x_0 = (x_0 + lastans -1 + MOD1) % MOD1 + 1;
            y_0 = (y_0 + lastans -1 + MOD2) % MOD2 + 1;
            x_1 = (x_1 + lastans -1 + MOD1) % MOD1 + 1;
            y_1 = (y_1 + lastans -1 + MOD2) % MOD2 + 1;
            if(x_0 > x_1) swap(x_0, x_1), swap(y_0, y_1);
            lichao.add(x_0, y_0, x_1, y_1);
        }
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}