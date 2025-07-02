#include<bits/stdc++.h>
using namespace std;
class FindPrimitiveRoot
{
private:
    int P;
    long long power_mod_P(long long x, int idx)
    {
        long long res = 1;
        for(long long now = x; idx>0; now = now*now%P, idx>>=1)
        {
            if(idx & 1) res = res*now%P;
        }
        return res;
    }
public:
    FindPrimitiveRoot(int _P)
    {
        P = _P;
        return;
    }
    int work()
    {
        if(P==2) return 1;
        vector<int> d;
        for(int i=1; i*i<=(P-1); i++)
        {
            if( (P-1)%i !=0 ) continue;
            d.push_back(i);
            if(i!=1 && i*i!=(P-1) ) d.push_back( (P-1)/i );
        } // the possible choices to be period must be the divisor of (P-1)
        for(int i=2; i<P; i++)
        {
            bool flag = 1;
            for(auto j : d)
            {
                if(power_mod_P(i, j) == 1)
                {
                    flag = 0;
                    break;
                } // P-1 isn't the least period
            }
            if(flag) return i;
        } // for prime, the least root is small, so just check from 2
        return -1; // for legal case, it's not gonna happen
    }
};
int main()
{
    return 0;
}