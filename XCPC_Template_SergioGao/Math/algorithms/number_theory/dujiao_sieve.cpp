#include<bits/stdc++.h>
using namespace std;
const int M = 2e7+5;
bool vis[M];
int mu[M], premu[M];
vector<int> prime;
map<long long, long long> S0;
long long sum(long long n)
{
    if(n<M) return premu[n];
    if(S0.count(n)) return S0[n];
    long long res = 1;
    for(long long t=2, r; t<=n; t = r+1)
    {
        r = min(n/(n/t), n);
        res -= sum(n/t)*(r-t+1);
    }
    S0[n] = res;
    return res;
}
void sieve()
{
    premu[1] = mu[1] = 1;
    for(int j=2; j<M; j++)
    {
        if(!vis[j]) 
        {
            prime.push_back(j);
            mu[j] = -1;
        }
        premu[j] = premu[j-1] + mu[j];
        for(auto p : prime)
        {
            if(1ll*p*j<M) 
            {
                vis[p*j] = 1;
                if(j%p == 0) 
                {
                    mu[p*j] = 0;
                    break;
                }
                else mu[p*j] = -mu[j];
            }
            else break;
        }
    }
    return;
}
int main()
{
    return 0;
}