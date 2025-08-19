#include<bits/stdc++.h>  
using namespace std;  

using ll = long long;

const int MOD = 998244353, G = 3;

ll power(ll x, ll y)
{
	ll res = 1;
	for( ; y>0; y>>=1, x=x*x%MOD) if(y&1) res = res*x%MOD;
	return res;
}
ll inv(ll x)
{
	return power(x, MOD-2);
}

class NTT
{
private:
	static void ntt(vector<int> &a, bool invert)
	{
		int len = a.size();
		for(int now = 0, i = 1; i<len-1; i++)
		{
			int hbit = len/2;
			while( (now & hbit) )
			{
				now ^= hbit;
				hbit>>=1;
			}
			now^=hbit;
			if(now > i) swap(a[now], a[i]);
		}
		for(int l = 2; l<=len; l<<=1)
		{
			int wl = power(G, (MOD-1)/l);
			if(invert) wl = power(wl, MOD-2);
			for(int i=0; i<len; i+=l)
			{
				for(int k=0, now = 1; k<l/2; k++, now = 1ll*now*wl%MOD)
				{
					int u = a[i+k], v = 1ll*a[i+k+l/2]*now%MOD;
					a[i+k] = (u+v)%MOD;
					a[i+k+l/2] = (u-v+MOD)%MOD;
				}
			}
		}

		if(invert)
		{
			int ivn = power(len, MOD-2);
			for(int i=0; i<len; i++) a[i] = 1ll*ivn*a[i]%MOD;
		}

		return;
	}

public:
	static vector<int> multiply(vector<int> vec1, vector<int> vec2)
	{
		vector<int> res;
		int len = 1;
		while(len < (int)(vec1.size() + vec2.size()-1) ) len<<=1;
		vec1.resize(len, 0);
		vec2.resize(len, 0);
		ntt(vec1, 0);
		ntt(vec2, 0);
		for(int i=0; i<len; i++)
		{
			res.push_back(1ll*vec1[i]*vec2[i]%MOD);
		}
		ntt(res, 1);
		return res;
	}
};

class Conv
{
private:
	void divide_solve(int l, int r)
	{
		if(l==r)
		{
			func(f[l], l);
			return;
		}
		int mid = (l+r)/2;
		divide_solve(l, mid);
		vector<int> tf(mid-l+1), tg(r-l+1);
		for(int i=l; i<=mid; i++) tf[i-l] = f[i];
		for(int i=1; i<=r-l; i++) tg[i] = g[i];
		auto res = NTT::multiply(tf, tg);
		for(int i=mid+1; i<=r; i++)
		{
			f[i] = ( f[i] + res[i-l] ) %MOD;
		}
		divide_solve(mid+1, r);
		return;
	}
public:	
	vector<int> f, g;
	function<void(int &, int)> func;
	void self_convolution()
	{
		int len = 1;
		while(len < (int)g.size()) len<<=1;
		g.resize(len);
		f = vector<int>(len, 0);
		f[0] = 1;
		divide_solve(0, len-1);
		return;
	}
};

class Poly
{
public:
	static vector<int> exp(vector<int> G)
	{ // guarantee G[0] = 0;
		int len = G.size();
		for(int i=1; i<len; i++) G[i] = 1ll * G[i] * i %MOD; 
		Conv T;
		T.func = [&](int &x, int y)
		{
			if(y!=0) x = 1ll * x * inv(y) %MOD;
			return;
		};
		T.g = G; 
		T.self_convolution();
		return T.f;
	}
	static vector<int> poly_inv(vector<int> G)
	{ // guarantee G[0] = 1
		Conv T;
		T.func = [&](int &x, int y)
		{
			if(y!=0) x = ( MOD - x ) %MOD;
			return;
		};
		T.g = G;
		T.self_convolution();
		return T.f;
	}
	static vector<int> ln(vector<int> G)
	{ // guarantee G[0] = 1
		vector<int> G_inv = poly_inv(G);
		int len = G.size();
		vector<int> G_p(len);
		for(int i=1; i<len; i++) G_p[i-1] = 1ll * G[i] * i %MOD;
		auto res = NTT::multiply(G_p, G_inv);
		vector<int> F(len);
		F[0] = 0;
		for(int i=1; i<len; i++) F[i] = 1ll * res[i-1] * inv(i) %MOD;
		return F;
	}
};

void init()
{
    return;
}

void solve()
{
	int n;
	cin>>n;
	vector<int> f(n);
	for(int i=0; i<n; i++) cin>>f[i];
	auto res = Poly::ln(f);
	for(int i=0; i<n; i++) cout<<res[i]<<" ";
	cout<<"\n";

	return;
}
/*

*/
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	// freopen("poly.in", "r", stdin);

    int T = 1;
    // cin>>T;
    while(T--) solve();
    return 0;
}
/*


*/