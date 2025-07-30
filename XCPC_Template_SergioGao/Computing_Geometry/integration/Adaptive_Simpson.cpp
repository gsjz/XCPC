#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
const double EPS = 1e-7;

double a, b, c, d;
double f(double x)
{
    return (c*x+d) / (a*x+b);
}
double simpson(double l, double r)
{
    double mid = (l+r)/2;
    return (r-l) * (f(l) + 4 * f(mid) + f(r)) /6;
}
double asr(double l, double r, double ans, double eps, int step)
{
    double mid = (l+r)/2;
    double fl = simpson(l, mid), fr = simpson(mid, r);
    if( abs(fl + fr - ans) <= 15 * eps && step < 0 )
    {
        return fl + fr + (fl + fr - ans) / 15;
    }
    return asr(l, mid, fl, eps/2, step-1) + asr(mid, r, fr, eps/2, step-1) ;
}
double calc(double l, double r)
{
    return asr(l, r, simpson(l, r), EPS, 12);
}

void solve()
{
    int L, R;
    cin>>a>>b>>c>>d>>L>>R;
    cout<<fixed<<setprecision(6)<<calc(L, R)<<"\n";
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