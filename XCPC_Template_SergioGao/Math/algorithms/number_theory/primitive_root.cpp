#include<bits/stdc++.h>
using namespace std;
int P, g;
long long modpower(long long x, int idx)
{
	if(idx==0) return 1;
	auto res = modpower(x, idx/2);
	res = res*res%P;
	if(idx&1) res = res*x%P;
	return res;
}
void findg()
{
	g = -1;
	vector<int> d;
	for(int i=1; i*i<= (P-1); i++)
	{
		if((P-1)%i!=0) continue;
		d.push_back(i);
		if(i!=1 && i*i!=(P-1)) d.push_back( (P-1)/i );
	}
	for(int i=2; i<P; i++)
	{
		bool flag = 1;
		for(auto j: d)
		{
			if(modpower(i, j)==1) 
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			g = i;
			return;
		}
	}
	return;
}
int main()
{
    return 0;
}