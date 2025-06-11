#include<bits/stdc++.h>
using namespace std;

const int MOD = 998244353, G = 3;
class NTT
{
private:
	static long long power(long long x, int idx)
	{
		if(idx==0) return 1;
		auto res = power(x, idx/2);
		res = res*res%MOD;
		if(idx&1) res = res*x%MOD;
		return res;
	}
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

int main()
{
    return 0;
}